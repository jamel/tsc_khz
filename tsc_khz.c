// SPDX-License-Identifier: GPL-2.0-only

#include <linux/module.h>
#include <linux/device/bus.h>
#include <linux/cpu.h>
#include <linux/sysfs.h>
#include <asm/tsc.h>

#ifdef pr_fmt
	#undef pr_fmt
#endif

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* sysfs file to export tsc_khz */
static ssize_t tsc_khz_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", tsc_khz);
}

static DEVICE_ATTR_RO(tsc_khz);

static int __init init_tsc_khz(void)
{
	struct device *dev = bus_get_dev_root(&cpu_subsys);
	int ret = -ENODEV;

	if (dev) {
		ret = sysfs_create_file(&dev->kobj, &dev_attr_tsc_khz.attr);
		put_device(dev);
	}

	pr_info("tsc_khz exported in sysfs, ret=%d", ret);

	return ret;
}

static void __exit cleanup_tsc_khz(void)
{
	struct device *dev = bus_get_dev_root(&cpu_subsys);

	if (dev) {
		sysfs_remove_file(&dev->kobj, &dev_attr_tsc_khz.attr);
		put_device(dev);
	}

	pr_info("tsc_khz unexported from sysfs");
}

module_init(init_tsc_khz);
module_exit(cleanup_tsc_khz);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Redha Gouicem, <redha.gouicem@gmail.com>");
MODULE_DESCRIPTION("export tsc clock frequency to sysfs");
