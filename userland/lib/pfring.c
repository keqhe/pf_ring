/*
 *
 * (C) 2005-10 - Luca Deri <deri@ntop.org>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lessed General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#define __USE_XOPEN2K
#include <sys/types.h>
#include <pthread.h>

#include "pfring.h"

#ifdef ENABLE_DNA_SUPPORT
#include "pfring_e1000_dna.h"
#endif

#define USE_ADAPTIVE_WAIT

#define MAX_NUM_LOOPS    1000000000
#define YIELD_MULTIPLIER      10000

// #define RING_DEBUG

/* ******************************* */

unsigned long long rdtsc() {
  unsigned long long a;
  asm volatile("rdtsc":"=A" (a));
  return(a);
}

/* ******************************* */

int pfring_set_direction(pfring *ring, packet_direction direction) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ? setsockopt(ring->fd, 0, SO_SET_PACKET_DIRECTION,
			      &direction, sizeof(direction)): -1);
#endif
}

/* ******************************* */

/*
  Device reflection is used only when pfring_notify() is called
  with reflect_packet parameter set to 1. This function allows
  developers to implement in userland a "filtering application"
  that can instrument pf_ring to forward through those packets
  that have passed the checks.
*/
int pfring_set_reflection_device(pfring *ring, char *dev_name) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ? setsockopt(ring->fd, 0, SO_SET_REFLECTION_DEVICE,
			   dev_name, strlen(dev_name)): -1);
#endif
}

/* ******************************* */

int pfring_set_master_id(pfring *ring, u_int32_t master_id) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ? setsockopt(ring->fd, 0, SO_SET_MASTER_RING,
			   &master_id, sizeof(master_id)): -1);
#endif
}

/* ******************************* */

int pfring_set_master(pfring *ring, pfring *master) {
  return(pfring_set_master_id(ring, pfring_get_ring_id(master)));
}

/* ******************************* */

int pfring_set_cluster(pfring *ring, u_int clusterId, cluster_type the_type) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  struct add_to_cluster cluster;

  cluster.clusterId = clusterId, cluster.the_type = the_type;

  return(ring ? setsockopt(ring->fd, 0, SO_ADD_TO_CLUSTER,
			   &cluster, sizeof(cluster)): -1);
#endif
}

/* ******************************* */

int pfring_set_channel_id(pfring *ring, int32_t channel_id) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ? setsockopt(ring->fd, 0, SO_SET_CHANNEL_ID,
			   &channel_id, sizeof(channel_id)): -1);
#endif
}

/* ******************************* */

int pfring_set_application_name(pfring *ring, char *name) {
#if !defined(SO_SET_APPL_NAME)
  return(-1);
#else

#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ? setsockopt(ring->fd, 0, SO_SET_APPL_NAME,
			   name, strlen(name)): -1);
#endif
#endif
}

/* ******************************* */

int pfring_remove_from_cluster(pfring *ring) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ? setsockopt(ring->fd, 0, SO_REMOVE_FROM_CLUSTER,
			      NULL, 0) : -1);
#endif
}

/* ******************************* */

int pfring_purge_idle_hash_rules(pfring *ring, u_int16_t inactivity_sec) {
#ifdef USE_PCAP
  return(-1);
#else
#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) return(-1);
#endif
  return(ring ?
	 setsockopt(ring->fd, 0, SO_PURGE_IDLE_HASH_RULES,
		    &inactivity_sec, sizeof(inactivity_sec)) : -1);
#endif
}

/* ******************************* */

#ifndef USE_PCAP
static int set_if_promisc(const char *device, int set_promisc) {
  int sock_fd, ret = 0;
  struct ifreq ifr;

  if(device == NULL) return(-3);

  sock_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if(sock_fd <= 0) return(-1);

  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_name, device, sizeof(ifr.ifr_name));
  if(ioctl(sock_fd, SIOCGIFFLAGS, &ifr) == -1) {
    close(sock_fd);
    return(-2);
  }

  ret = ifr.ifr_flags & IFF_PROMISC;
  if(set_promisc) {
    if(ret == 0) ifr.ifr_flags |= IFF_PROMISC;
  } else {
    /* Remove promisc */
    if(ret != 0) ifr.ifr_flags &= ~IFF_PROMISC;
  }

  if(ioctl(sock_fd, SIOCSIFFLAGS, &ifr) == -1)
    return(-1);

  close(sock_fd);
  return(ret);
}
#endif

/* **************************************************** */

int pfring_bind(pfring *ring, char *device_name) {
  struct sockaddr sa;
  char *at;
  int32_t channel_id = -1;
  int rc = 0;

  if((device_name == NULL) || (strcmp(device_name, "none") == 0))
    return(-1);

  at = strchr(device_name, '@');
  if(at != NULL) {
    char *tok, *pos = NULL;

    at[0] = '\0';

    /* Syntax
       ethX@1,5       channel 1 and 5
       ethX@1-5       channel 1,2...5
       ethX@1-3,5-7   channel 1,2,3,5,6,7
    */

    tok = strtok_r(&at[1], ",", &pos);
    channel_id = 0;

    while(tok != NULL) {
      char *dash = strchr(tok, '-');
      int32_t min_val, max_val, i;

      if(dash) {
	dash[0] = '\0';
	min_val = atoi(tok);
	max_val = atoi(&dash[1]);

      } else
	min_val = max_val = atoi(tok);

      for(i = min_val; i <= max_val; i++)
	channel_id |= 1 << i;

      tok = strtok_r(NULL, ",", &pos);
    }
  }

  sa.sa_family = PF_RING;
  snprintf(sa.sa_data, sizeof(sa.sa_data), "%s", device_name);

  rc = bind(ring->fd, (struct sockaddr *)&sa, sizeof(sa));

  if(rc == 0) {
    if(channel_id != -1) {
      int rc = pfring_set_channel_id(ring, channel_id);

      if(rc != 0)
	printf("pfring_set_channel_id() failed: %d\n", rc);
    }
  }

  return(rc);
}

/* **************************************************** */

pfring* pfring_open(char *device_name, u_int8_t promisc,
		    u_int32_t caplen, u_int8_t _reentrant) {
#ifdef USE_PCAP
  char ebuf[256];

  pcap_t *pcapPtr = pcap_open_live(device_name,
				   caplen,
				   1 /* promiscuous mode */,
				   1000 /* ms */,
				   ebuf);

  return((pfring*)pcapPtr);
#else
  int err = 0;
  pfring *ring = (pfring*)malloc(sizeof(pfring));

  if(ring == NULL)
    return(NULL);
  else
    memset(ring, 0, sizeof(pfring));

  ring->reentrant = _reentrant;
  ring->fd = socket(PF_RING, SOCK_RAW, htons(ETH_P_ALL));

#ifdef RING_DEBUG
  printf("Open RING [fd=%d]\n", ring->fd);
#endif

  if(ring->fd > 0) {
    int rc;
    u_int memSlotsLen;

    if(caplen > MAX_CAPLEN) caplen = MAX_CAPLEN;
    setsockopt(ring->fd, 0, SO_RING_BUCKET_LEN, &caplen, sizeof(caplen));

    /* printf("channel_id=%d\n", channel_id); */

    if((device_name == NULL) || (strcmp(device_name, "none") == 0)) {
      /* No binding yet */
      rc = 0;
    } else
      rc = pfring_bind(ring, device_name);

    if(rc == 0) {
      ring->buffer = (char *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE,
				  MAP_SHARED, ring->fd, 0);

      if(ring->buffer == MAP_FAILED) {
	printf("mmap() failed");
	free(ring);
	return(NULL);
      }

      ring->slots_info = (FlowSlotInfo *)ring->buffer;
      if(ring->slots_info->version != RING_FLOWSLOT_VERSION) {
	printf("Wrong RING version: "
	       "kernel is %i, libpfring was compiled with %i\n",
	       ring->slots_info->version, RING_FLOWSLOT_VERSION);
	free(ring);
	return(NULL);
      }
      memSlotsLen = ring->slots_info->tot_mem;
      munmap(ring->buffer, PAGE_SIZE);

      ring->buffer = (char *)mmap(NULL, memSlotsLen,
				 PROT_READ|PROT_WRITE,
				 MAP_SHARED, ring->fd, 0);

      if(ring->buffer == MAP_FAILED) {
	printf("mmap() failed");
	free(ring);
	return(NULL);
      }

      ring->slots_info   = (FlowSlotInfo *)ring->buffer;
      ring->slots = (char *)(ring->buffer+sizeof(FlowSlotInfo));

      /* Safety check */
      if(ring->slots_info->remove_idx >= ring->slots_info->tot_slots)
	ring->slots_info->remove_idx = 0;

      ring->page_id = PAGE_SIZE, ring->slot_id = 0, ring->pkts_per_page = 0;

      /* Set defaults */
      ring->device_name = strdup(device_name);

#ifdef RING_DEBUG
      printf("RING (%s): tot_slots=%d/slot_len=%d/"
	     "insertIdx=%d/remove_idx=%d/dropped=%d\n",
	     device_name,
	     ring->slots_info->tot_slots,
	     ring->slots_info->slot_len,
	     ring->slots_info->insert_idx,
	     ring->slots_info->remove_idx,
	     ring->slots_info->tot_lost);
#endif

      if(promisc) {
	if(set_if_promisc(device_name, 1) == 0)
	  ring->clear_promisc = 1;
      }

    } else {
      close(ring->fd);
      err = -1;
    }
  } else {
    err = -1;
    free(ring);
  }

  if(err == 0) {
    if(ring->reentrant)
      pthread_spin_init(&ring->spinlock, PTHREAD_PROCESS_PRIVATE);

    return(ring);
  } else
    return(NULL);
#endif
}

/* **************************************************** */

u_int8_t pfring_open_multichannel(char *device_name, u_int8_t promisc,
				  u_int32_t caplen, u_int8_t _reentrant,
				  pfring* ring[MAX_NUM_RX_CHANNELS]) {
  u_int8_t num_channels, i, num = 0;
  char *at;
  char base_device_name[32];

  snprintf(base_device_name, sizeof(base_device_name), "%s", device_name);
  at = strchr(base_device_name, '@');
  if(at != NULL)
    at[0] = '\0';

  /* Count how many RX channel the specified device supports */
  ring[0] = pfring_open(base_device_name, promisc, caplen, _reentrant);

  if(ring[0] == NULL)
    return(0);
  else
    num_channels = pfring_get_num_rx_channels(ring[0]);

  pfring_close(ring[0]);

  /* Now do the real job */
  for(i=0; i<num_channels; i++) {
    char dev[32];

    snprintf(dev, sizeof(dev), "%s@%d", base_device_name, i);
    ring[i] = pfring_open(dev, promisc, caplen, _reentrant);

    if(ring[i] == NULL)
      return(num);
    else
      num++;
  }

  return(num);
}

/* **************************************************** */

void pfring_close(pfring *ring) {
#ifdef USE_PCAP
  pcap_t *pcapPtr = (pcap_t*)ring;
  pcap_close(pcapPtr);
#else
  if(!ring) return;

#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) {
    if(ring->dna_dev.packet_memory != 0)
      munmap((void*)ring->dna_dev.packet_memory,
	     ring->dna_dev.packet_memory_tot_len);

    if(ring->dna_dev.descr_packet_memory != NULL)
      munmap(ring->dna_dev.descr_packet_memory,
	     ring->dna_dev.descr_packet_memory_tot_len);

    if(ring->dna_dev.phys_card_memory != NULL)
      munmap(ring->dna_dev.phys_card_memory,
	     ring->dna_dev.phys_card_memory_len);
  } else
#endif
    {
    if(ring->buffer != NULL) {
      munmap(ring->buffer, ring->slots_info->tot_mem);
    }
  }

  if(ring->clear_promisc)
    set_if_promisc(ring->device_name, 0);

  free(ring->device_name);
  close(ring->fd);

  if(ring->reentrant)
    pthread_spin_destroy(&ring->spinlock);

  free(ring);
#endif
}

/* **************************************************** */

int pfring_toggle_filtering_policy(pfring *ring,
				   u_int8_t rules_default_accept_policy) {
#ifdef USE_PCAP
  return(-1);
#else
  return(ring ? setsockopt(ring->fd, 0, SO_TOGGLE_FILTER_POLICY,
			   &rules_default_accept_policy,
			   sizeof(rules_default_accept_policy)): -1);
#endif
}

/* **************************************************** */

int pfring_version(pfring *ring, u_int32_t *version) {
#ifdef USE_PCAP
  return(-1);
#else
  if(ring == NULL)
    return(-1);
  else {
    socklen_t len = sizeof(u_int32_t);
    return(getsockopt(ring->fd, 0, SO_GET_RING_VERSION, version, &len));
  }
#endif
}

/* **************************************************** */

u_int8_t pfring_get_num_rx_channels(pfring *ring) {
#ifdef USE_PCAP
  return(1);
#else
  if(ring == NULL)
    return(1);
  else {
    socklen_t len = sizeof(u_int32_t);
    u_int8_t num_rx_channels;
    int rc = getsockopt(ring->fd, 0, SO_GET_NUM_RX_CHANNELS, &num_rx_channels, &len);

    return((rc == 0) ? num_rx_channels : 1);
  }
#endif
}

/* **************************************************** */

u_int16_t pfring_get_ring_id(pfring *ring) {
#ifdef USE_PCAP
  return(1);
#else
  if(ring == NULL)
    return(1);
  else {
    u_int8_t id;
    socklen_t len = sizeof(id);

    int rc = getsockopt(ring->fd, 0, SO_GET_RING_ID, &id, &len);

    return((rc == 0) ? id : 1);
  }
#endif
}

/* **************************************************** */

int pfring_get_filtering_rule_stats(pfring *ring, u_int16_t rule_id,
				    char* stats, u_int *stats_len) {
#ifdef USE_PCAP
  return(-1);
#else
  if((ring == NULL) || (*stats_len < sizeof(u_int16_t)))
    return(-1);
#ifdef ENABLE_DNA_SUPPORT
  else if(ring->dna_mapped_device) return(-1);
#endif
  else {
    memcpy(stats, &rule_id, sizeof(u_int16_t));
    return(getsockopt(ring->fd, 0,
		      SO_GET_FILTERING_RULE_STATS,
		      stats, stats_len));
  }
#endif
}

/* **************************************************** */

int pfring_get_hash_filtering_rule_stats(pfring *ring,
					 hash_filtering_rule* rule,
					 char* stats, u_int *stats_len) {
#ifdef USE_PCAP
  return(-1);
#else
  if(ring == NULL)
    return(-1);
#ifdef ENABLE_DNA_SUPPORT
  else if(ring->dna_mapped_device) return(-1);
#endif
  else {
    char buffer[2048];
    int rc;
    u_int len;

    memcpy(buffer, rule, sizeof(hash_filtering_rule));
    len = sizeof(buffer);
    rc = getsockopt(ring->fd, 0,
		    SO_GET_HASH_FILTERING_RULE_STATS,
		    buffer, &len);
    if(rc < 0)
      return(rc);
    else {
      *stats_len = min(*stats_len, rc);
      memcpy(stats, buffer, *stats_len);
      return(0);
    }
  }
#endif
}

/* **************************************************** */

int pfring_add_filtering_rule(pfring *ring, filtering_rule* rule_to_add) {
#ifdef USE_PCAP
  return(-1);
#else
  int rc;

  if((!rule_to_add) || (!ring)) return(-1);
#ifdef ENABLE_DNA_SUPPORT
  else if(ring->dna_mapped_device) return(-1);
#endif

  /* Sanitize entry */
  if(rule_to_add->core_fields.port_low > rule_to_add->core_fields.port_high)
    rule_to_add->core_fields.port_low = rule_to_add->core_fields.port_high;
  if(rule_to_add->core_fields.host_low > rule_to_add->core_fields.host_high)
    rule_to_add->core_fields.host_low = rule_to_add->core_fields.host_high;

  if(rule_to_add->balance_id > rule_to_add->balance_pool)
    rule_to_add->balance_id = 0;

  rc = setsockopt(ring->fd, 0, SO_ADD_FILTERING_RULE,
		  rule_to_add, sizeof(filtering_rule));

  return(rc);
#endif
}

/* **************************************************** */

int pfring_enable_ring(pfring *ring) {
#ifdef USE_PCAP
  return(-1);
#else
  char dummy;

  if(!ring) return(-1);
#ifdef ENABLE_DNA_SUPPORT
  else if(ring->dna_mapped_device) return(-1);
#endif
  return(setsockopt(ring->fd, 0, SO_ACTIVATE_RING, &dummy, sizeof(dummy)));
#endif
}

/* **************************************************** */

int pfring_remove_filtering_rule(pfring *ring, u_int16_t rule_id) {
#ifdef USE_PCAP
  return(-1);
#else
  int rc;

#ifdef ENABLE_DNA_SUPPORT
  if((ring == NULL) || ring->dna_mapped_device) return(-1);
#endif
  rc = ring ? setsockopt(ring->fd, 0, SO_REMOVE_FILTERING_RULE,
			 &rule_id, sizeof(rule_id)): -1;

  return(rc);
#endif
}

/* **************************************************** */

int pfring_handle_hash_filtering_rule(pfring *ring,
				      hash_filtering_rule* rule_to_add,
				      u_char add_rule) {
#ifdef USE_PCAP
  return(-1);
#else
  int rc;

#ifdef ENABLE_DNA_SUPPORT
  if((ring == NULL) || ring->dna_mapped_device) return(-1);
#endif

  if((!rule_to_add) || (!ring)) return(-1);

  rc = setsockopt(ring->fd, 0, add_rule ? SO_ADD_FILTERING_RULE : SO_REMOVE_FILTERING_RULE,
		  rule_to_add, sizeof(hash_filtering_rule));

  return(rc);
#endif
}

/* **************************************************** */

int pfring_set_sampling_rate(pfring *ring, u_int32_t rate /* 1 = no sampling */) {
#ifdef USE_PCAP
  return(-1);
#else
  int rc;

#ifdef ENABLE_DNA_SUPPORT
  if((ring == NULL) || ring->dna_mapped_device) return(-1);
#endif

  rc = ring ? setsockopt(ring->fd, 0, SO_SET_SAMPLING_RATE,
			 &rate, sizeof(rate)): -1;

  return(rc);
#endif
}

/* ******************************* */

int pfring_stats(pfring *ring, pfring_stat *stats) {
#ifdef USE_PCAP
  return(-1);
#else

#ifdef ENABLE_DNA_SUPPORT
  if((ring == NULL) || ring->dna_mapped_device) {
    stats->recv = ring->tot_dna_read_pkts, stats->drop = 0;
    return(0);
  }
#endif

  if(ring && stats) {
    stats->recv = ring->slots_info->tot_read;
    stats->drop = ring->slots_info->tot_lost;
    return(0);
  } else
    return(-1);
#endif
}

/* **************************************************** */

//#ifdef USE_PCAP
struct eth_hdr {
  unsigned char   h_dest[ETH_ALEN];       /* destination eth addr */
  unsigned char   h_source[ETH_ALEN];     /* source ether addr    */
  u_int16_t       h_proto;                /* packet type ID field */
};

#define __LITTLE_ENDIAN_BITFIELD /* FIX */
struct iphdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
	u_int8_t	ihl:4,
		version:4;
#elif defined (__BIG_ENDIAN_BITFIELD)
	u_int8_t	version:4,
  		ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
	u_int8_t	tos;
	u_int16_t	tot_len;
	u_int16_t	id;
	u_int16_t	frag_off;
	u_int8_t	ttl;
	u_int8_t	protocol;
	u_int16_t	check;
	u_int32_t	saddr;
	u_int32_t	daddr;
	/*The options start here. */
};

struct tcphdr {
	u_int16_t	source;
	u_int16_t	dest;
	u_int32_t	seq;
	u_int32_t	ack_seq;
#if defined(__LITTLE_ENDIAN_BITFIELD)
	__u16	res1:4,
		doff:4,
		fin:1,
		syn:1,
		rst:1,
		psh:1,
		ack:1,
		urg:1,
		ece:1,
		cwr:1;
#elif defined(__BIG_ENDIAN_BITFIELD)
	__u16	doff:4,
		res1:4,
		cwr:1,
		ece:1,
		urg:1,
		ack:1,
		psh:1,
		rst:1,
		syn:1,
		fin:1;
#else
#error	"Adjust your <asm/byteorder.h> defines"
#endif
	u_int16_t	window;
	u_int16_t	check;
	u_int16_t	urg_ptr;
};

struct udphdr {
	u_int16_t	source;
	u_int16_t	dest;
	u_int16_t	len;
	u_int16_t	check;
};

#define TH_FIN_MULTIPLIER	0x01
#define TH_SYN_MULTIPLIER	0x02
#define TH_RST_MULTIPLIER	0x04
#define TH_PUSH_MULTIPLIER	0x08
#define TH_ACK_MULTIPLIER	0x10
#define TH_URG_MULTIPLIER	0x20

#if defined(USE_PCAP) || defined(ENABLE_DNA_SUPPORT)
static int parse_pkt(char *pkt, struct pfring_pkthdr *hdr)
{
  struct iphdr *ip;
  struct eth_hdr *eh = (struct eth_hdr*)pkt;
  u_int16_t displ;

  memset(&hdr->parsed_pkt, 0, sizeof(struct pkt_parsing_info));

  hdr->parsed_header_len = 0;
  hdr->parsed_pkt.eth_type = ntohs(eh->h_proto);
  hdr->parsed_pkt.pkt_detail.offset.eth_offset = 0;

  if(hdr->parsed_pkt.eth_type == 0x8100 /* 802.1q (VLAN) */)
    {
      hdr->parsed_pkt.pkt_detail.offset.vlan_offset = hdr->parsed_pkt.pkt_detail.offset.eth_offset + sizeof(struct eth_hdr);
      hdr->parsed_pkt.vlan_id = (pkt[hdr->parsed_pkt.pkt_detail.offset.eth_offset + 14] & 15) * 256
	+ pkt[hdr->parsed_pkt.pkt_detail.offset.eth_offset + 15];
      hdr->parsed_pkt.eth_type = (pkt[hdr->parsed_pkt.pkt_detail.offset.eth_offset + 16]) * 256
	+ pkt[hdr->parsed_pkt.pkt_detail.offset.eth_offset + 17];
      displ = 4;
    }
  else
    {
      displ = 0;
      hdr->parsed_pkt.vlan_id = 0; /* Any VLAN */
    }

  if(hdr->parsed_pkt.eth_type == 0x0800 /* IP */) {
    hdr->parsed_pkt.pkt_detail.offset.l3_offset = hdr->parsed_pkt.pkt_detail.offset.eth_offset+displ+sizeof(struct eth_hdr);
    ip = (struct iphdr*)(pkt+hdr->parsed_pkt.pkt_detail.offset.l3_offset);

    hdr->parsed_pkt.ipv4_src = ntohl(ip->saddr), hdr->parsed_pkt.ipv4_dst = ntohl(ip->daddr), hdr->parsed_pkt.l3_proto = ip->protocol;
    hdr->parsed_pkt.ipv4_tos = ip->tos;

    if((ip->protocol == IPPROTO_TCP) || (ip->protocol == IPPROTO_UDP))
      {
	u_int16_t ip_len = ip->ihl*4;

	hdr->parsed_pkt.pkt_detail.offset.l4_offset = hdr->parsed_pkt.pkt_detail.offset.l3_offset+ip_len;

	if(ip->protocol == IPPROTO_TCP)
	  {
	    struct tcphdr *tcp = (struct tcphdr*)(pkt+hdr->parsed_pkt.pkt_detail.offset.l4_offset);
	    hdr->parsed_pkt.l4_src_port = ntohs(tcp->source), hdr->parsed_pkt.l4_dst_port = ntohs(tcp->dest);
	    hdr->parsed_pkt.pkt_detail.offset.payload_offset = hdr->parsed_pkt.pkt_detail.offset.l4_offset+(tcp->doff * 4);
	    hdr->parsed_pkt.tcp_flags = (tcp->fin * TH_FIN_MULTIPLIER) + (tcp->syn * TH_SYN_MULTIPLIER) + (tcp->rst * TH_RST_MULTIPLIER) +
	      (tcp->psh * TH_PUSH_MULTIPLIER) + (tcp->ack * TH_ACK_MULTIPLIER) + (tcp->urg * TH_URG_MULTIPLIER);
	  } else if(ip->protocol == IPPROTO_UDP)
	    {
	      struct udphdr *udp = (struct udphdr*)(pkt+hdr->parsed_pkt.pkt_detail.offset.l4_offset);
	      hdr->parsed_pkt.l4_src_port = ntohs(udp->source), hdr->parsed_pkt.l4_dst_port = ntohs(udp->dest);
	      hdr->parsed_pkt.pkt_detail.offset.payload_offset = hdr->parsed_pkt.pkt_detail.offset.l4_offset+sizeof(struct udphdr);
	    } else
	      hdr->parsed_pkt.pkt_detail.offset.payload_offset = hdr->parsed_pkt.pkt_detail.offset.l4_offset;
      } else
	hdr->parsed_pkt.l4_src_port = hdr->parsed_pkt.l4_dst_port = 0;

    return(1); /* IP */
  } /* TODO: handle IPv6 */

  return(0); /* No IP */
}

#endif

/* **************************************************** */

int pfring_notify(pfring *ring, u_int8_t reflect_packet) {
  if(ring->reentrant) {
    /*
      We do not support late packet consumers in multithreaded
      applications as threads can steal each other's packets
    */

    return(-1);
  }

  if(ring->last_slot_to_update) {
    ring->last_slot_to_update->slot_state = reflect_packet ? 2 : 0; /* Empty slot */
    ring->last_slot_to_update = NULL;
  }
  
  return(0);
}

/* **************************************************** */

int pfring_read(pfring *ring, char* buffer, u_int buffer_len,
		struct pfring_pkthdr *hdr,
		u_int8_t wait_for_incoming_packet,
		u_int8_t consume_packet_immediately) {
#ifdef USE_PCAP
  pcap_t *pcapPtr = (pcap_t*)ring;
  const u_char *packet;

  packet = pcap_next(pcapPtr, (struct pcap_pkthdr*)hdr);
  if(hdr->caplen > 0) {
    if(buffer && (buffer_len > 0)) {
      memcpy(buffer, packet, min(hdr->caplen, buffer_len));
      parse_pkt(buffer, hdr);
    }
    return(1);
  } else
    return(0);
#else

  if(ring == NULL) return(-1);

  if(ring->reentrant) {
    /*
      We do not support late packet consumers in multithreaded
      applications as threads can steal each other's packets
    */
    consume_packet_immediately = 1;
  }

#ifdef ENABLE_DNA_SUPPORT
  if(ring->dna_mapped_device) {
    char *pkt;

    if(wait_for_incoming_packet) {
      if(ring->reentrant) pthread_spin_lock(&ring->spinlock);

      switch(ring->dna_dev.device_model) {
      case intel_e1000:
	e1000_there_is_a_packet_to_read(ring, wait_for_incoming_packet);
	break;
      default:
	return(0);
      }

      if(ring->reentrant) pthread_spin_unlock(&ring->spinlock);
    }

    switch(ring->dna_dev.device_model) {
    case intel_e1000:
      pkt = get_next_e1000_packet(ring, buffer, buffer_len, hdr);
      break;
    case intel_igb:
      pkt = NULL, hdr->len = 0;
      break;
    case intel_ixgbe:
      pkt = NULL, hdr->len = 0;
      break;
    }

    if(pkt && (hdr->len > 0)) {
      if(1)
	hdr->parsed_header_len = 0;
      else
	parse_pkt(buffer, hdr);
      return(1);
    } else
      return(0);
  } else
#endif /* ENABLE_DNA_SUPPORT */
    {
      FlowSlot *slot;
      u_int32_t queuedPkts;
#ifdef USE_ADAPTIVE_WAIT
      u_int32_t num_loops = 0;
#endif

      if((ring == NULL) || (ring->buffer == NULL)) return(-1);

      /*
	Check if the kernel needs to be notified that the previous
	packet has been finally consumed
      */
      if(ring->last_slot_to_update) 
	pfring_notify(ring, REFLECT_PACKET_DEVICE_NONE);

    do_pfring_recv:
      if(ring->reentrant)
	pthread_spin_lock(&ring->spinlock);

      slot = (FlowSlot*)&ring->slots[ring->slots_info->remove_idx*ring->slots_info->slot_len];

      if(ring->slots_info->tot_insert >= ring->slots_info->tot_read)
	queuedPkts = ring->slots_info->tot_insert - ring->slots_info->tot_read;
      else
	queuedPkts = ring->slots_info->tot_slots + ring->slots_info->tot_insert - ring->slots_info->tot_read;

      if(queuedPkts && (slot->slot_state == 1 /* There's a packet to read */)) {
	char *bucket = (char*)&slot->bucket;
	struct pfring_pkthdr *_hdr = (struct pfring_pkthdr*)bucket;
	int bktLen = _hdr->caplen+_hdr->parsed_header_len;

	if(bktLen > buffer_len) bktLen = buffer_len-1;

	if(buffer && (bktLen > 0)) {
	  memcpy(buffer, &bucket[sizeof(struct pfring_pkthdr)], bktLen);
	  bucket[bktLen] = '\0';
	}

	if(ring->slots_info->remove_idx >= (ring->slots_info->tot_slots-1)) {
	  ring->slots_info->remove_idx = 0;
	  ring->page_id = PAGE_SIZE, ring->slot_id = 0, ring->pkts_per_page = 0;
	} else {
	  ring->slots_info->remove_idx++;
	  ring->pkts_per_page++, ring->slot_id += ring->slots_info->slot_len;
	}

	if(hdr) memcpy(hdr, _hdr, sizeof(struct pfring_pkthdr));

	ring->slots_info->tot_read++;

	if(consume_packet_immediately) {
	  ring->last_slot_to_update = NULL, slot->slot_state = 0; /* Empty slot */
	} else {
	  /* We do not notify pf_ring that the packet has been read
	     hence this slot will not be available for storing a new packet
	     until we notify pf_ring
	  */
	  ring->last_slot_to_update = slot;
	}      

	if(ring->reentrant) pthread_spin_unlock(&ring->spinlock);
	return(1);
      } else if(wait_for_incoming_packet) {
	struct pollfd pfd;
	int rc;

	if(ring->reentrant) pthread_spin_unlock(&ring->spinlock);

#ifdef USE_ADAPTIVE_WAIT
	/*
	  Spin in userland for a while and if no packet arrives then
	  it's time to poll the kernel. I have to do this as a call to
	  poll() is too costly hence I do call poll() if and only if
	  I have no chance to avoid it.
	*/
	if(num_loops < MAX_NUM_LOOPS) {
	  num_loops++;
	  if(num_loops % YIELD_MULTIPLIER) {
	    sched_yield();
	  }
	}
#endif

	/* Sleep when nothing is happening */
	pfd.fd      = ring->fd;
	pfd.events  = POLLIN|POLLERR;
	pfd.revents = 0;

#ifdef RING_DEBUG
	printf("==>> poll [remove_idx=%u][insert_idx=%u][loss=%d][queuedPkts=%u]"
	       "[slot_state=%d][tot_insert=%u][tot_read=%u]\n",
	       ring->slots_info->remove_idx,
	       ring->slots_info->insert_idx,
	       ring->slots_info->tot_lost,
	       queuedPkts, slot->slot_state,
	       ring->slots_info->tot_insert,
	       ring->slots_info->tot_read);
#endif

	errno = 0;

	rc = poll(&pfd, 1, -1);

	ring->num_poll_calls++;

	if(rc == -1)
	  return(-1);
	else
	  goto do_pfring_recv;
      }

      return(-1); /* Not reached */
    }
#endif
}

/* **************************************************** */

int pfring_recv(pfring *ring, char* buffer, u_int buffer_len,
		struct pfring_pkthdr *hdr,
		u_int8_t wait_for_incoming_packet) {

  return(pfring_read(ring, buffer, buffer_len,
		     hdr, wait_for_incoming_packet, 1));
}

/* ******************************* */

int pfring_get_selectable_fd(pfring *ring) {
#ifdef USE_PCAP
  return(pcap_get_selectable_fd((pcap_t*)ring));
#else
  if((ring == NULL)
#ifdef ENABLE_DNA_SUPPORT
     || ring->dna_mapped_device
#endif
     ) return(-1);
  return(ring->fd);
#endif
}

/* ******************************* */

#ifdef ENABLE_DNA_SUPPORT
static int pfring_map_dna_device(pfring *ring,
				 dna_device_operation operation,
				 char *device_name,
				 int32_t channel_id) {
#ifdef USE_PCAP
  return(-1);
#else
  dna_device_mapping mapping;

  mapping.operation = operation;
  snprintf(mapping.device_name, sizeof(mapping.device_name),
	   "%s", device_name);
  mapping.channel_id = channel_id;

  return(ring ? setsockopt(ring->fd, 0, SO_MAP_DNA_DEVICE,
			   &mapping, sizeof(mapping)): -1);
#endif
}
#endif

/* ******************************* */

#ifdef ENABLE_DNA_SUPPORT
static int pfring_get_mapped_dna_device(pfring *ring, dna_device *dev) {
#ifdef USE_PCAP
  return(-1);
#else
  socklen_t len = sizeof(dna_device);

  if(dev == NULL)
    return(-1);
  else
    return(getsockopt(ring->fd, 0, SO_GET_MAPPED_DNA_DEVICE, dev, &len));
#endif
}
#endif

/* **************************************************** */

#ifdef ENABLE_DNA_SUPPORT
static void pfring_dump_dna_stats(pfring* ring) {
  switch(ring->dna_dev.device_model) {
  case intel_e1000:
    printf("[Intel 1 Gbit e1000 family]\n");
    pfring_dump_dna_e1000_stats(ring);
    break;
  case intel_igb:
    printf("[Intel 1 Gbit igb family]\n");
    break;
  case intel_ixgbe:
    printf("[Intel 10 Gbit ixgbe family]\n");
    break;
  default:
    printf("[Unknown card model]\n");
  }
}
#endif

/* **************************************************** */

#ifdef ENABLE_DNA_SUPPORT
pfring* pfring_open_dna(char *device_name, u_int8_t _reentrant) {
#ifdef USE_PCAP
  return(NULL);
#else
  int err = 0, channel_id = 0;
  pfring *ring = (pfring*)malloc(sizeof(pfring));

  if(ring == NULL)
    return(NULL);
  else
    memset(ring, 0, sizeof(pfring));

  ring->reentrant = _reentrant;
  ring->fd = socket(PF_RING, SOCK_RAW, htons(ETH_P_ALL));

#ifdef RING_DEBUG
  printf("Open RING [fd=%d]\n", ring->fd);
#endif

  if(ring->fd > 0) {
    int   rc;
    char *at;

    at = strchr(device_name, '@');
    if(at != NULL) {
      at[0] = '\0';

      /* Syntax
	 ethX@1      channel 1
      */

      channel_id = atoi(&at[1]);
    }

    /* printf("channel_id=%d\n", channel_id); */
    rc = pfring_map_dna_device(ring, add_device_mapping,
			       device_name, channel_id);

    if(rc == 0) {
      if((rc = pfring_get_mapped_dna_device(ring, &ring->dna_dev)) < 0) {
	printf("pfring_get_mapped_dna_device() failed [rc=%d]\n", rc);
	free(ring);
	return(NULL);
      } else {
	printf("[num_slots=%d][slot_len=%d][tot_mem_len=%d]\n",
	       ring->dna_dev.packet_memory_num_slots,
	       ring->dna_dev.packet_memory_slot_len,
	       ring->dna_dev.packet_memory_tot_len);
	printf("[memory_num_slots=%d][memory_slot_len=%d]"
	       "[memory_tot_len=%d]\n",
	       ring->dna_dev.descr_packet_memory_num_slots,
	       ring->dna_dev.descr_packet_memory_slot_len,
	       ring->dna_dev.descr_packet_memory_tot_len);
      }

      ring->dna_mapped_device = 1;

      ring->dna_dev.packet_memory =
	(unsigned long)mmap(NULL, ring->dna_dev.packet_memory_tot_len,
			    PROT_READ|PROT_WRITE,
			    MAP_SHARED, ring->fd, 0);

      if(ring->dna_dev.packet_memory == (unsigned long)MAP_FAILED) {
	printf("mmap(1) failed");
	free(ring);
	return(NULL);
      }

      ring->dna_dev.descr_packet_memory =
	(void*)mmap(NULL, ring->dna_dev.descr_packet_memory_tot_len,
		    PROT_READ|PROT_WRITE,
		    MAP_SHARED, ring->fd, 0);

      if(ring->dna_dev.descr_packet_memory == MAP_FAILED) {
	printf("mmap(2) failed");
	free(ring);
	return(NULL);
      }

      ring->dna_dev.phys_card_memory =
	(void*)mmap(NULL, ring->dna_dev.phys_card_memory_len,
		    PROT_READ|PROT_WRITE,
		    MAP_SHARED, ring->fd, 0);

      if(ring->dna_dev.phys_card_memory == MAP_FAILED) {
	printf("mmap(3) failed");
	free(ring);
	return(NULL);
      }

      init_e1000(ring); /* FIX */
      pfring_dump_dna_stats(ring);

      return(ring);
    } else {
      printf("pfring_map_dna_device() failed [rc=%d]: device already in use?\n", rc);
      free(ring);
      return(NULL);
    }
  } else {
    err = -1;
  }

  if(err == 0) {
    if(ring->reentrant)
      pthread_spin_init(&ring->spinlock, PTHREAD_PROCESS_PRIVATE);

    return(ring);
  }

  if(ring) {
    free(ring);
    ring = NULL;
  }

  return(NULL);
#endif
}
#endif

