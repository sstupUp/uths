#include <linux/time.h>
#include <linux/string.h>

#define BILLION 1000000000
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
// the functions for parent file will be stored in profile_arr[][0]
// the functions for original file will be stored in profile_arr[][1]

#define Profile(uths, ID, ret, function, ...)\
	if (uths == 0)\
		uths_flag = 0;\
	else if (uths == 1)\
		uths_flag = 1;\
	if (!module_flag)\
		ret = function(__VA_ARGS__);\
	else {\
		local_time[0].tv_sec = 0; local_time[0].tv_nsec = 0;\
		local_time[1].tv_sec = 0; local_time[1].tv_nsec = 0;\
		if(profile_arr[ID][uths_flag].id == 0) {\
			func_len = strlen(#function);\
			strncpy(profile_arr[ID][uths_flag].name, #function, func_len + 1);\
			profile_arr[ID][uths_flag].id = ID;\
		}\
		getrawmonotonic(&local_time[0]);\
		ret = function(__VA_ARGS__);\
		getrawmonotonic(&local_time[1]);\
		calclock(local_time, &(profile_arr[ID][uths_flag].tot_time), &(profile_arr[ID][uths_flag].tot_count));\
	}

#define Profile_void(uths, ID, function, ...)\
	if (uths == 0)\
		uths_flag = 0;\
	else if (uths == 1)\
		uths_flag = 1;\
	if (!module_flag)\
		function(__VA_ARGS__);\
	else {\
		local_time[0].tv_sec = 0; local_time[0].tv_nsec = 0;\
		local_time[1].tv_sec = 0; local_time[1].tv_nsec = 0;\
		if(profile_arr[ID][uths_flag].id == 0) {\
			func_len = strlen(#function);\
			strncpy(profile_arr[ID][uths_flag].name, #function, func_len + 1);\
			profile_arr[ID][uths_flag].id = ID;\
		}\
		getrawmonotonic(&local_time[0]);\
		function(__VA_ARGS__);\
		getrawmonotonic(&local_time[1]);\
		calclock(local_time, &(profile_arr[ID][uths_flag].tot_time), &(profile_arr[ID][uths_flag].tot_count));\
	}

extern int module_flag;
extern int func_len;
extern struct timespec local_time[2];
extern unsigned int uths_flag;

typedef struct time_stamp {
	unsigned int id;
	char name[NAME_LEN];
	unsigned long long tot_time;
	unsigned long long tot_count;
} TIME_STAMP;

extern TIME_STAMP profile_arr[ARR_SIZE][2];

extern inline void calclock(struct timespec *, unsigned long long *, unsigned long long *);

