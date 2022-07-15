#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "profile.h"

static int __init start_profile(void) 
{
	module_flag = 1;

	printk(KERN_DEBUG "[PROFILE] Load Profiler module!\n");
	
	return 0;
}

static void __exit end_profile(void)
{
	int i = 1;
	TIME_STAMP* tmp;
	module_flag = 0;

	printk(KERN_DEBUG "[PROFILE] ------------------ print profile ------------------ \n");

	tmp = &(profile_arr[i][0]);
	printk(KERN_DEBUG "arr0 for parent: \n");
	while(tmp->id != 0) {
		printk(KERN_DEBUG "[PROFILE] [%2d] %-20s: total time = %lld, total count = %lld\n", tmp->id, tmp->name, tmp->tot_time, tmp->tot_count);
		tmp->name[0] = '\0';
		tmp->id = 0;
 		tmp->tot_time = 0;
		tmp->tot_count = 0;		
		tmp = &(profile_arr[++i][0]);
	}
	i = 1;
	tmp = &(profile_arr[i][1]);
	printk(KERN_DEBUG "arr1 for original: \n");
	while(tmp->id != 0) {
		printk(KERN_DEBUG "[PROFILE] [%2d] %-20s: total time = %lld, total count = %lld\n", tmp->id, tmp->name, tmp->tot_time, tmp->tot_count);
		tmp->name[0] = '\0';
		tmp->id = 0;
 		tmp->tot_time = 0;
		tmp->tot_count = 0;		
		tmp = &(profile_arr[++i][1]);
	}

	tmp = &(profile_arr[5][1]);
	printk(KERN_DEBUG "[PROFILE] [%2d] %-20s: total time = %lld, total count = %lld\n", tmp->id, tmp->name, tmp->tot_time, tmp->tot_count);
	tmp = &(profile_arr[6][1]);
	printk(KERN_DEBUG "[PROFILE] [%2d] %-20s: total time = %lld, total count = %lld\n", tmp->id, tmp->name, tmp->tot_time, tmp->tot_count);
	
	printk(KERN_DEBUG "[PROFILE] Unload Profiler module!\n");
}

module_init(start_profile);
module_exit(end_profile);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("An Byoung Chul <studentsancho@gmail.com>");
MODULE_DESCRIPTION("Profiler Wrapper");
MODULE_VERSION("0.1.0");
