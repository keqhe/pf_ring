#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x92bb2bf4, "module_layout" },
	{ 0xd7cfb4d8, "device_remove_file" },
	{ 0x56ee09bd, "netdev_info" },
	{ 0x561a2460, "kmalloc_caches" },
	{ 0x3fff650, "pci_bus_read_config_byte" },
	{ 0xd2b09ce5, "__kmalloc" },
	{ 0xf154f2a3, "ethtool_op_get_ts_info" },
	{ 0xf9a482f9, "msleep" },
	{ 0x922c795a, "dcb_ieee_setapp" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0xfd3c27c2, "pci_enable_sriov" },
	{ 0x619cb7dd, "simple_read_from_buffer" },
	{ 0x26cab878, "debugfs_create_dir" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0xadaabe1b, "pv_lock_ops" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x6d33141a, "dcb_ieee_delapp" },
	{ 0x754d539c, "strlen" },
	{ 0xde83ac61, "skb_pad" },
	{ 0x4a957d0f, "dev_set_drvdata" },
	{ 0xbd100793, "cpu_online_mask" },
	{ 0xeacf74f0, "dma_set_mask" },
	{ 0x7707035f, "node_data" },
	{ 0xb9e249f6, "dev_mc_add_excl" },
	{ 0xddc0bbd4, "napi_complete" },
	{ 0x6165becd, "pci_disable_device" },
	{ 0xe0654ed2, "dev_uc_add_excl" },
	{ 0xc7a4fbed, "rtnl_lock" },
	{ 0x5fbd5aa8, "pci_disable_msix" },
	{ 0x2320042c, "hwmon_device_unregister" },
	{ 0x4ea25709, "dql_reset" },
	{ 0xd3c9801c, "netif_carrier_on" },
	{ 0x1637ff0f, "_raw_spin_lock_bh" },
	{ 0x921ece0a, "pci_disable_sriov" },
	{ 0x29aaae17, "schedule_work" },
	{ 0xc0a3d105, "find_next_bit" },
	{ 0xb81425e, "netif_carrier_off" },
	{ 0x88bfa7e, "cancel_work_sync" },
	{ 0x3fec048f, "sg_next" },
	{ 0xa9e16354, "x86_dma_fallback_dev" },
	{ 0x949f7342, "__alloc_percpu" },
	{ 0xee929300, "driver_for_each_device" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x593a99b, "init_timer_key" },
	{ 0x999e8297, "vfree" },
	{ 0xe3224113, "pci_bus_write_config_word" },
	{ 0x37cee78, "debugfs_create_file" },
	{ 0xb5aa7165, "dma_pool_destroy" },
	{ 0x54efb5d6, "cpu_number" },
	{ 0x91715312, "sprintf" },
	{ 0xd988d7b9, "debugfs_remove_recursive" },
	{ 0x70a39872, "__alloc_pages_nodemask" },
	{ 0x55f4494f, "pci_dev_driver" },
	{ 0xba0e05b3, "netif_napi_del" },
	{ 0x7d11c268, "jiffies" },
	{ 0xc9ec4e21, "free_percpu" },
	{ 0x733c3b54, "kasprintf" },
	{ 0x744a8aa0, "__netdev_alloc_skb" },
	{ 0x27c33efe, "csum_ipv6_magic" },
	{ 0xea2dc390, "__pskb_pull_tail" },
	{ 0xf432dd3d, "__init_waitqueue_head" },
	{ 0xfe7c4287, "nr_cpu_ids" },
	{ 0x35b6b772, "param_ops_charp" },
	{ 0x42ec6987, "pci_set_master" },
	{ 0xc2af65b3, "dca3_get_tag" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0xfb578fc5, "memset" },
	{ 0xada8198b, "dcb_getapp" },
	{ 0x895f8d1c, "dcb_setapp" },
	{ 0x17f5f87a, "pci_enable_pcie_error_reporting" },
	{ 0x2e471f01, "dca_register_notify" },
	{ 0x37af5f2e, "pci_enable_msix" },
	{ 0x5deb373, "pci_restore_state" },
	{ 0x8006c614, "dca_unregister_notify" },
	{ 0x6614a5c6, "dev_err" },
	{ 0x3b820a15, "dev_addr_del" },
	{ 0x27e1a049, "printk" },
	{ 0x1183448, "ethtool_op_get_link" },
	{ 0x20c55ae0, "sscanf" },
	{ 0x449ad0a7, "memcmp" },
	{ 0xa00aca2a, "dql_completed" },
	{ 0xcd279169, "nla_find" },
	{ 0x4751b037, "free_netdev" },
	{ 0x9166fada, "strncpy" },
	{ 0xb4354bec, "dev_mc_del" },
	{ 0x3d306481, "register_netdev" },
	{ 0x8b2819fe, "ndo_dflt_fdb_dump" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0xa6fbd9b2, "pci_bus_write_config_dword" },
	{ 0x6a0eb5e9, "dev_close" },
	{ 0x4c1182cb, "bitmap_scnprintf" },
	{ 0x91a1239b, "netif_set_real_num_rx_queues" },
	{ 0x8834396c, "mod_timer" },
	{ 0xde612288, "netif_set_real_num_tx_queues" },
	{ 0x20d82916, "netif_napi_add" },
	{ 0x2a37d074, "dma_pool_free" },
	{ 0x82bbf305, "dcb_ieee_getapp_mask" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0xe9fbf68d, "dca_add_requester" },
	{ 0x35f5d86c, "skb_pull" },
	{ 0xd510c10, "simple_open" },
	{ 0xefdcc764, "dev_kfree_skb_any" },
	{ 0x6b4ac06, "dev_open" },
	{ 0xe523ad75, "synchronize_irq" },
	{ 0xe99a87e5, "pci_find_capability" },
	{ 0x3b8989d8, "device_create_file" },
	{ 0x7966d735, "module_put" },
	{ 0x92702b69, "pci_select_bars" },
	{ 0x3ff62317, "local_bh_disable" },
	{ 0xd804e077, "netif_device_attach" },
	{ 0xeff8897c, "napi_gro_receive" },
	{ 0xcd92004c, "_dev_info" },
	{ 0x40a9b349, "vzalloc" },
	{ 0xe8262499, "dev_addr_add" },
	{ 0xf8e1311a, "pci_disable_link_state" },
	{ 0x618911fc, "numa_node" },
	{ 0xbecc76fc, "netif_device_detach" },
	{ 0x63dbcae0, "__alloc_skb" },
	{ 0x42c8de35, "ioremap_nocache" },
	{ 0x12a38747, "usleep_range" },
	{ 0x58adf1b8, "pci_bus_read_config_word" },
	{ 0xdaad3595, "__napi_schedule" },
	{ 0x2ac3a324, "pci_bus_read_config_dword" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0xba63339c, "_raw_spin_unlock_bh" },
	{ 0x42586612, "pci_cleanup_aer_uncorrect_error_status" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xb9249d16, "cpu_possible_mask" },
	{ 0xba23cf06, "kfree_skb" },
	{ 0x799aca4, "local_bh_enable" },
	{ 0x8cbca550, "eth_type_trans" },
	{ 0x771cf835, "dma_pool_alloc" },
	{ 0xccdb5481, "pskb_expand_head" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x2439206e, "netdev_err" },
	{ 0xa3eb29b9, "netdev_features_change" },
	{ 0xf23bc51e, "pci_unregister_driver" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0xe55dd87c, "kmem_cache_alloc_trace" },
	{ 0x61fb248a, "node_states" },
	{ 0xd52bf1ce, "_raw_spin_lock" },
	{ 0x3928efe9, "__per_cpu_offset" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0x4302d0eb, "free_pages" },
	{ 0xcf21d241, "__wake_up" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0x5a5064a2, "pci_set_power_state" },
	{ 0x3dc33c71, "netdev_warn" },
	{ 0xbb4f4766, "simple_write_to_buffer" },
	{ 0x32d9b988, "eth_validate_addr" },
	{ 0x315b6f17, "pci_disable_pcie_error_reporting" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0x365426d1, "___pskb_trim" },
	{ 0x4845c423, "param_array_ops" },
	{ 0x2c1e20cf, "pci_disable_msi" },
	{ 0x33d75f66, "dma_supported" },
	{ 0x78de06b8, "pci_num_vf" },
	{ 0xedc03953, "iounmap" },
	{ 0xc9ab8834, "pci_prepare_to_sleep" },
	{ 0x1dba4242, "__pci_register_driver" },
	{ 0xa8721b97, "system_state" },
	{ 0x4beb2b9a, "dev_uc_del" },
	{ 0xb352177e, "find_first_bit" },
	{ 0xf8ea3e24, "pci_get_device" },
	{ 0x4cbbd171, "__bitmap_weight" },
	{ 0x19ab25c7, "dev_warn" },
	{ 0xc0ab59c0, "unregister_netdev" },
	{ 0x394bf7e9, "ndo_dflt_bridge_getlink" },
	{ 0x55f5019b, "__kmalloc_node" },
	{ 0x7ca1aef4, "pci_dev_put" },
	{ 0x9e0c711d, "vzalloc_node" },
	{ 0x28318305, "snprintf" },
	{ 0xbbc59100, "pci_enable_msi_block" },
	{ 0x6ac9f255, "__netif_schedule" },
	{ 0xbc8fe0c7, "consume_skb" },
	{ 0xe09bd7d6, "dca_remove_requester" },
	{ 0xd130b205, "pci_enable_device_mem" },
	{ 0xfaed2648, "skb_tstamp_tx" },
	{ 0xd59b8000, "skb_put" },
	{ 0x7fa40c3f, "pci_wake_from_d3" },
	{ 0x69b8705d, "pci_release_selected_regions" },
	{ 0xbe656c3c, "pci_request_selected_regions" },
	{ 0xbb128381, "irq_set_affinity_hint" },
	{ 0x508ac048, "__skb_tx_hash" },
	{ 0x6d044c26, "param_ops_uint" },
	{ 0xbb1e6b55, "dma_pool_create" },
	{ 0xb64abb77, "skb_copy_bits" },
	{ 0x46571a1a, "dev_get_drvdata" },
	{ 0xefcdb4f9, "hwmon_device_register" },
	{ 0x73a9a965, "pci_find_ext_capability" },
	{ 0x6e720ff2, "rtnl_unlock" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xd4608d6f, "dma_ops" },
	{ 0x42a09cec, "try_module_get" },
	{ 0x24c0ce5c, "device_set_wakeup_enable" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x783d7a9c, "pci_save_state" },
	{ 0xadbfbae2, "alloc_etherdev_mqs" },
	{ 0x183aed23, "netdev_crit" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dca";

MODULE_ALIAS("pci:v00008086d000010B6sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C6sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C7sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C8sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000150Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010DDsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010ECsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F1sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010E1sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F4sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010DBsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001508sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F7sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010FCsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001517sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010FBsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001507sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001514sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F9sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000152Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001529sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000151Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F8sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001528sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000154Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000154Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001557sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000154Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001558sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001560sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "08110F2C0BF1ADBA62C9735");
