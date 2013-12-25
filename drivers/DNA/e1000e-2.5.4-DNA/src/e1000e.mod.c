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
	{ 0x3ce4ca6f, "disable_irq" },
	{ 0x56ee09bd, "netdev_info" },
	{ 0x561a2460, "kmalloc_caches" },
	{ 0x3fff650, "pci_bus_read_config_byte" },
	{ 0xd2b09ce5, "__kmalloc" },
	{ 0xf154f2a3, "ethtool_op_get_ts_info" },
	{ 0xf9a482f9, "msleep" },
	{ 0xc4dc87, "timecounter_init" },
	{ 0x29388c31, "__pm_runtime_idle" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0xadaabe1b, "pv_lock_ops" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x91eb9b4, "round_jiffies" },
	{ 0x754d539c, "strlen" },
	{ 0xde83ac61, "skb_pad" },
	{ 0x4a957d0f, "dev_set_drvdata" },
	{ 0xeacf74f0, "dma_set_mask" },
	{ 0x7707035f, "node_data" },
	{ 0xddc0bbd4, "napi_complete" },
	{ 0x6165becd, "pci_disable_device" },
	{ 0x5fbd5aa8, "pci_disable_msix" },
	{ 0x4ea25709, "dql_reset" },
	{ 0xd3c9801c, "netif_carrier_on" },
	{ 0xacd991bf, "pm_qos_add_request" },
	{ 0xe6caccdd, "pm_qos_remove_request" },
	{ 0x29aaae17, "schedule_work" },
	{ 0xc0a3d105, "find_next_bit" },
	{ 0xb81425e, "netif_carrier_off" },
	{ 0x88bfa7e, "cancel_work_sync" },
	{ 0xa9e16354, "x86_dma_fallback_dev" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x593a99b, "init_timer_key" },
	{ 0xccfcbff4, "mutex_unlock" },
	{ 0xc7a59bf1, "__pm_runtime_resume" },
	{ 0x999e8297, "vfree" },
	{ 0xe3224113, "pci_bus_write_config_word" },
	{ 0x2447533c, "ktime_get_real" },
	{ 0x3608b5be, "pci_disable_link_state_locked" },
	{ 0x70a39872, "__alloc_pages_nodemask" },
	{ 0xc499ae1e, "kstrdup" },
	{ 0x7d11c268, "jiffies" },
	{ 0xb44e3f0e, "skb_trim" },
	{ 0x744a8aa0, "__netdev_alloc_skb" },
	{ 0x27c33efe, "csum_ipv6_magic" },
	{ 0xea2dc390, "__pskb_pull_tail" },
	{ 0xf432dd3d, "__init_waitqueue_head" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x35b6b772, "param_ops_charp" },
	{ 0x42ec6987, "pci_set_master" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0xfb578fc5, "memset" },
	{ 0x17f5f87a, "pci_enable_pcie_error_reporting" },
	{ 0x37af5f2e, "pci_enable_msix" },
	{ 0x5deb373, "pci_restore_state" },
	{ 0x6614a5c6, "dev_err" },
	{ 0x8f64aa4, "_raw_spin_unlock_irqrestore" },
	{ 0x27e1a049, "printk" },
	{ 0x1183448, "ethtool_op_get_link" },
	{ 0x20c55ae0, "sscanf" },
	{ 0x449ad0a7, "memcmp" },
	{ 0xa00aca2a, "dql_completed" },
	{ 0x4751b037, "free_netdev" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x9166fada, "strncpy" },
	{ 0x3d306481, "register_netdev" },
	{ 0x5792f848, "strlcpy" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x10f5a16b, "__pci_enable_wake" },
	{ 0x93483dfd, "mutex_lock" },
	{ 0x802d0e93, "crc32_le" },
	{ 0x6a0eb5e9, "dev_close" },
	{ 0x8834396c, "mod_timer" },
	{ 0x20d82916, "netif_napi_add" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0x31ca7186, "device_wakeup_enable" },
	{ 0xefdcc764, "dev_kfree_skb_any" },
	{ 0xbecc2727, "pci_clear_master" },
	{ 0x6b4ac06, "dev_open" },
	{ 0xe523ad75, "synchronize_irq" },
	{ 0xe99a87e5, "pci_find_capability" },
	{ 0xeeb30cdc, "dev_notice" },
	{ 0x622acc35, "dev_kfree_skb_irq" },
	{ 0x167c5967, "print_hex_dump" },
	{ 0x7966d735, "module_put" },
	{ 0x92702b69, "pci_select_bars" },
	{ 0xc0bf6ead, "timecounter_cyc2time" },
	{ 0xd804e077, "netif_device_attach" },
	{ 0xeff8897c, "napi_gro_receive" },
	{ 0xcd92004c, "_dev_info" },
	{ 0xb2a4f2c8, "kmem_cache_alloc_node_trace" },
	{ 0x618911fc, "numa_node" },
	{ 0xbecc76fc, "netif_device_detach" },
	{ 0x63dbcae0, "__alloc_skb" },
	{ 0x42c8de35, "ioremap_nocache" },
	{ 0x12a38747, "usleep_range" },
	{ 0x58adf1b8, "pci_bus_read_config_word" },
	{ 0xdaad3595, "__napi_schedule" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x42586612, "pci_cleanup_aer_uncorrect_error_status" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4c5a315a, "pm_schedule_suspend" },
	{ 0x8cbca550, "eth_type_trans" },
	{ 0xccdb5481, "pskb_expand_head" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x2439206e, "netdev_err" },
	{ 0xf23bc51e, "pci_unregister_driver" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0x61fb248a, "node_states" },
	{ 0xd52bf1ce, "_raw_spin_lock" },
	{ 0x9327f5ce, "_raw_spin_lock_irqsave" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0x4302d0eb, "free_pages" },
	{ 0xcf21d241, "__wake_up" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0x3dc33c71, "netdev_warn" },
	{ 0x32d9b988, "eth_validate_addr" },
	{ 0x315b6f17, "pci_disable_pcie_error_reporting" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0x365426d1, "___pskb_trim" },
	{ 0x4845c423, "param_array_ops" },
	{ 0x2c1e20cf, "pci_disable_msi" },
	{ 0x33d75f66, "dma_supported" },
	{ 0xedc03953, "iounmap" },
	{ 0xc9ab8834, "pci_prepare_to_sleep" },
	{ 0x76873239, "pci_dev_run_wake" },
	{ 0x1dba4242, "__pci_register_driver" },
	{ 0x25eb73b5, "pm_qos_update_request" },
	{ 0x7e0aa9c9, "put_page" },
	{ 0xb352177e, "find_first_bit" },
	{ 0x19ab25c7, "dev_warn" },
	{ 0xc0ab59c0, "unregister_netdev" },
	{ 0x9e0c711d, "vzalloc_node" },
	{ 0x28318305, "snprintf" },
	{ 0xbbc59100, "pci_enable_msi_block" },
	{ 0x6ac9f255, "__netif_schedule" },
	{ 0xbc8fe0c7, "consume_skb" },
	{ 0xd130b205, "pci_enable_device_mem" },
	{ 0xfaed2648, "skb_tstamp_tx" },
	{ 0xd59b8000, "skb_put" },
	{ 0x69b8705d, "pci_release_selected_regions" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0x6d044c26, "param_ops_uint" },
	{ 0x46571a1a, "dev_get_drvdata" },
	{ 0xfba2197a, "pcie_capability_write_word" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xd4608d6f, "dma_ops" },
	{ 0xd188c2f3, "pci_request_selected_regions_exclusive" },
	{ 0x42a09cec, "try_module_get" },
	{ 0x445565df, "pcie_capability_read_word" },
	{ 0x24c0ce5c, "device_set_wakeup_enable" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x783d7a9c, "pci_save_state" },
	{ 0xadbfbae2, "alloc_etherdev_mqs" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v00008086d0000105Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000105Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010A4sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010BCsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010A5sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001060sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010D9sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010DAsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010D5sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010B9sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000107Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000107Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000107Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000108Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000108Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000109Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010D3sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F6sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000150Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001096sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010BAsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001098sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010BBsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000104Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C5sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C4sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000104Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000104Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000104Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001049sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001501sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C0sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C2sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010C3sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010BDsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000294Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010E5sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010BFsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F5sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010CBsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010CCsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010CDsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010CEsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010DEsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010DFsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001525sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010EAsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010EBsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010EFsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000010F0sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001502sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001503sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000153Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000153Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000155Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001559sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015A0sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015A1sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015A2sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015A3sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "E48694FE24634F8982A3ECB");
