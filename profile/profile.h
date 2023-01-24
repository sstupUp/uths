#include <linux/time.h>
#include <linux/string.h>

#define BILLION 1000000000
#define MILLION 1000000
#define ARR_SIZE 20
#define NAME_LEN 20

// Usage
// Profile(uths, function_id, return_variable, function_name, args)
// 
// uths: 0 == function call for parent | 1 == function call for original | 2 == generic function call
// function_id: same value for same function
// return_variable: variable for return value | use Profile_void() if there is no return value
// function_name: function to call
// args: arguments for the function

// Output
//

#define Profile(ID, ret, function, ...)\
	if(!atomic_read(&module_flag)){\
		ret = function(__VA_ARGS__);}\
	else {\
		local_time[0].tv_sec = 0; local_time[0].tv_nsec = 0;\
		local_time[1].tv_sec = 0; local_time[1].tv_nsec = 0;\
		int len2 = strlen(__func__);\
		func_len = strlen(#function);\
		getrawmonotonic(&local_time[0]);\
		ret = function(__VA_ARGS__);\
		getrawmonotonic(&local_time[1]);\
		if(profile_arr[ID].id == -1) {\
			strncpy(profile_arr[ID].callee, #function, func_len+1);\
			strncpy(profile_arr[ID].caller, __func__, len2+1);\
			profile_arr[ID].id = ID;\
		}\
		calclock(local_time, &profile_arr[ID].tot_time, &profile_arr[ID].tot_count);\
	}


#define Profile_void(uths, function, ...)\
	if (uths == 0)\
		uths_flag = 0;\
	else if (uths == 1)\
		uths_flag = 1;\
	if (!module_flag)\
		function(__VA_ARGS__);\
	else {\
		local_time[0].tv_sec = 0; local_time[0].tv_nsec = 0;\
		local_time[1].tv_sec = 0; local_time[1].tv_nsec = 0;\
		if(profile_arr[function_ID][uths_flag].id == -1) {\
			func_len = strlen(#function);\
			strncpy(profile_arr[function_ID][uths_flag].callee, #function, func_len + 1);\
			strncpy(profile_arr[function_ID][uths_flag].caller, __func__, func_len + 1);\
			profile_arr[function_ID][uths_flag].id = function_ID;\
		}\
		getrawmonotonic(&local_time[0]);\
		function(__VA_ARGS__);\
		getrawmonotonic(&local_time[1]);\
		calclock(local_time, &(profile_arr[function_ID][uths_flag].tot_time), &(profile_arr[function_ID][uths_flag].tot_count));\
	function_ID++;\
	}

extern atomic_t module_flag;
extern int func_len;
extern struct timespec local_time[2];
extern unsigned int uths_flag;
extern unsigned int function_ID;
extern long long temp_time, temp_count;

typedef struct time_stamp {
	int id;
	char caller[NAME_LEN];
	char callee[NAME_LEN];
	unsigned long long tot_time;
	unsigned long long tot_count;
} TIME_STAMP;

extern TIME_STAMP profile_arr[ARR_SIZE];

extern inline void calclock(struct timespec *, unsigned long long *, unsigned long long *);

