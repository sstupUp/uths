// To Compile: make
// To load the module: insmod iosplit.ko
// To remove the module: rmmod iosplit.ko

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

extern int ssd1, ssd2;

static int __init start_split(void) 
{
	printk("[IO RATIO] Load IO split module!\n");

	ssd1 = 1;
	ssd2 = 1;

	printk("[IO RATIO] Setting ssd1 = %d, ssd2 = %d\n", ssd1, ssd2);

	return 0;
}

static void __exit end_split(void)
{
	printk(KERN_DEBUG "[IO RATIO] Unload IO split module!\n");
}

module_init(start_split);
module_exit(end_split);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("An Byoung Chul <anbc0716o@gmail.com>");
MODULE_DESCRIPTION("IO split module");
MODULE_VERSION("0.1.0");
