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
	{ 0xfe769456, "unregister_netdevice_notifier" },
	{ 0x2bc09a00, "pf_ring_add_module_dependency" },
	{ 0x63ecad53, "register_netdevice_notifier" },
	{ 0x28318305, "snprintf" },
	{ 0x27e1a049, "printk" },
	{ 0x37a0cba, "kfree" },
	{ 0x42a09cec, "try_module_get" },
	{ 0x7966d735, "module_put" },
	{ 0xe55dd87c, "kmem_cache_alloc_trace" },
	{ 0x561a2460, "kmalloc_caches" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=pf_ring";


MODULE_INFO(srcversion, "469AC281345BC69AC85B21E");
