#
# Makefile for the PF_RING API example programs
#
# Try to make both programs written on top of the
# PF_RING library and programs originally written
# on top of PCAP library and linked now to use
# the version with PF_RING aware functionalities.
#



#
# PF_RING
#
PFRINGDIR  = ../lib
LIBPFRING  = ${PFRINGDIR}/libpfring.a

#
# DNA Support
DNA_DEFINE = #-DENABLE_DNA_SUPPORT

#
# PF_RING aware libpcap
#
O_FLAG     = -O2 -DHAVE_PF_RING
EXTRA_LIBS =
PCAPDIR    = ../libpcap-1.1.1-ring
LIBPCAP    = ${PCAPDIR}/libpcap.a  ${EXTRA_LIBS}

#
# Search directories
#
PFRING_KERNEL=../../kernel
INCLUDE    = -I${PFRING_KERNEL} -I${PFRING_KERNEL}/plugins -I${PFRINGDIR} -I${PCAPDIR}

#
# C compiler and flags
#
#
# CROSS_COMPILE=arm-mv5sft-linux-gnueabi-
#
CC         = ${CROSS_COMPILE}gcc #--platform=native
CFLAGS     = -march=corei7-avx -mtune=corei7-avx  ${O_FLAG} -Wall ${INCLUDE} ${DNA_DEFINE} -D HAVE_ZERO -D ENABLE_BPF -O2 # -g
# LDFLAGS  =

#
# User and System libraries
#
LIBS       = ${LIBPCAP} ${LIBPFRING}  -lpthread  ${LIBPCAP}   -lrt

# How to make an object file
%.o: %.c pfutils.c
#	@echo "=*= making object $@ =*="
	${CC} ${CFLAGS} -c $< -o $@

#
# Main targets
#
PFPROGS   = pfcount my_pfcount pfcount_multichannel preflect pfbounce pfmap \
	    pfbridge alldevs dummy_plugin_pfcount pcap2nspcap pfcount_dummy_plugin pffilter_test \
	    pfcount_aggregator pfcount_bundle pfcount_82599 pfsystest pfsend pflatency \
	    pfdump

ifneq (-D HAVE_ZERO,)
	PFPROGS += pfdnabounce pfdnacluster_master pfdnacluster_multithread pfdnacluster_mt_rss_frwd
endif

PCAPPROGS = pcount pfwrite
TARGETS   = ${PFPROGS} ${PCAPPROGS}

RCOBJS    = ringc.o interval.o
RSOBJS    = rings.o interval.o
RMOBJS    = ringm.o interval.o
RPOBJS    = pcaps.o interval.o

all: ${TARGETS}

ringc: ${RCOBJS} ${LIBPFRING}
	${CC} ${CFLAGS} ${RCOBJS} ${LIBS} -o $@

rings: ${RSOBJS} ${LIBPFRING}
	${CC} ${CFLAGS} ${RSOBJS} ${LIBS} -o $@

ringm: ${RMOBJS} ${LIBPFRING}
	${CC} ${CFLAGS} ${RMOBJS} ${LIBS} -o $@

pcaps: ${RPOBJS}
	${CC} ${CFLAGS} ${RPOBJS} ${LIBS} -o $@

pfcount: pfcount.o ${LIBPFRING}
	${CC} ${CFLAGS} pfcount.o ${LIBS} -o $@

my_pfcount: my_pfcount.o ${LIBPFRING}
	${CC} ${CFLAGS} my_pfcount.o ${LIBS} -o $@

dummy_plugin_pfcount: dummy_plugin_pfcount.o ${LIBPFRING}
	${CC} ${CFLAGS} dummy_plugin_pfcount.o ${LIBS} -o $@

pffilter_test: pffilter_test.o ${LIBPFRING}
	${CC} ${CFLAGS} pffilter_test.o ${LIBS} -o $@

pcap2nspcap: pcap2nspcap.o ${LIBPFRING}
	${CC} ${CFLAGS} pcap2nspcap.o ${LIBS} -o $@

pfcount_multichannel: pfcount_multichannel.o ${LIBPFRING}
	${CC} ${CFLAGS} pfcount_multichannel.o ${LIBS} -o $@

pfcount_82599: pfcount_82599.o ${LIBPFRING}
	${CC} ${CFLAGS} pfcount_82599.o ${LIBS} -o $@

pfcount_bundle: pfcount_bundle.o ${LIBPFRING}
	${CC} ${CFLAGS} pfcount_bundle.o ${LIBS} -o $@

pfcount_dummy_plugin: pfcount_dummy_plugin.o ${LIBPFRING}
	${CC} ${CFLAGS} pfcount_dummy_plugin.o ${LIBS} -o $@

pfcount_aggregator: pfcount_aggregator.o ${LIBPFRING}
	${CC} ${CFLAGS} pfcount_aggregator.o ${LIBS} -o $@

preflect: preflect.o ${LIBPFRING}
	${CC} ${CFLAGS} preflect.o ${LIBS} -o $@

pfbounce: pfbounce.o ${LIBPFRING}
	${CC} ${CFLAGS} pfbounce.o ${LIBS} -o $@

pfdnabounce: pfdnabounce.o ${LIBPFRING}
	${CC} ${CFLAGS} pfdnabounce.o ${LIBS} -o $@

pfsend: pfsend.o ${LIBPFRING}
	${CC} ${CFLAGS} pfsend.o ${LIBS} -o $@

pflatency: pflatency.o ${LIBPFRING}
	${CC} ${CFLAGS} pflatency.o ${LIBS} -o $@

pftwin: pftwin.o ${LIBPFRING}
	${CC} ${CFLAGS} pftwin.o ${LIBS} -o $@

ptwin: ptwin.o ${LIBPFRING}
	${CC} ${CFLAGS} ptwin.o ${LIBS} -o $@

pfmap: pfmap.o ${LIBPFRING}
	${CC} ${CFLAGS} pfmap.o ${LIBS} -o $@

pfbridge: pfbridge.o ${LIBPFRING}
	${CC} ${CFLAGS} pfbridge.o ${LIBS} -o $@

pcount: pcount.o ${LIBPFRING}
	${CC} ${CFLAGS} pcount.o ${LIBS} -o $@

alldevs: alldevs.o ${LIBPFRING}
	${CC} ${CFLAGS} alldevs.o ${LIBS} -o $@

pfwrite: pfwrite.o ${LIBPFRING}
	${CC} ${CFLAGS} pfwrite.o ${LIBS} -o $@

pfsystest: pfsystest.o ${LIBPFRING}
	${CC} ${CFLAGS} pfsystest.o ${LIBS} -o $@

pfdnacluster_master: pfdnacluster_master.o ${LIBPFRING}
	${CC} ${CFLAGS} pfdnacluster_master.o ${LIBS} -o $@

pfdnacluster_multithread: pfdnacluster_multithread.o ${LIBPFRING}
	${CC} ${CFLAGS} pfdnacluster_multithread.o ${LIBS} -o $@

pfdnacluster_mt_rss_frwd: pfdnacluster_mt_rss_frwd.o ${LIBPFRING}
	${CC} ${CFLAGS} pfdnacluster_mt_rss_frwd.o ${LIBS} -o $@

pfdump: pfdump.o ${LIBPFRING}
	${CC} ${CFLAGS} pfdump.o ${LIBS} -o $@

clean:
	@rm -f ${TARGETS} *.o *~
