// To Compile: make
// To load the module: insmod profile.ko
// To remove the module: rmmod profile.ko

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "profile.h"

static int __init start_profile(void) 
{
	int i = 0;
	atomic_set(&module_flag, 1);
	function_ID = 0;
	printk(KERN_DEBUG "[PROFILE] Load Profiler module!\n");

	// init profile_arr
	for(i = 0; i < ARR_SIZE; i++)
	{
		profile_arr[i].id = -1;
		profile_arr[i].caller[0] = '\0';
		profile_arr[i].callee[0] = '\0';
		profile_arr[i].tot_time = 0;
		profile_arr[i].tot_count = 0;
	}

	return 0;
}

static void __exit end_profile(void)
{
	int i = 0, j = 0;
	TIME_STAMP* tmp;
	atomic_set(&module_flag, 0);

	printk(KERN_DEBUG "[PROFILE] --------------------------------- print profile ---------------------------------\n");
	printk(KERN_DEBUG "[PROFILE] [id][%20s][%20s]:    total_time,    total_count\n", "caller", "callee");

	tmp = &(profile_arr[i]);
	while(tmp->id > -1) {
		printk(KERN_DEBUG "[PROFILE] [%2d][%20s][%20s]: %12lld ns, %9lld\n", tmp->id, tmp->caller, tmp->callee, tmp->tot_time, tmp->tot_count);
		tmp->caller[0] = '\0';
		tmp->callee[0] = '\0';
		tmp->id = -1;
 		tmp->tot_time = 0;
		tmp->tot_count = 0;		
		tmp = &(profile_arr[++i]);
	}

	printk(KERN_DEBUG "[PROFILE] ---------------------------------------------------------------------------------\n");
	printk(KERN_DEBUG "[PROFILE] Unload Profiler module!\n");
}

module_init(start_profile);
module_exit(end_profile);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("An Byoung Chul <anbc0716o@gmail.com>");
MODULE_DESCRIPTION("Profiler Wrapper");
MODULE_VERSION("0.1.0");
