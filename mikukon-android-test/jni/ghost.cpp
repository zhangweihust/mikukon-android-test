#include <sys/types.h>
#include <unistd.h>

#include <android/log.h>

#include "substrate.h"
#include "my_constant.h"

#define MY_TAG "ghost.c"

//#define __arm__ 1
//#define __ANDROID__ 1
//#define __cplusplus 1

//#define LIB_SUBSTRACE_PATH "/system/lib/libsubstrate.so"
//#define LIB_GHOST_PATH "/data/local/tmp/mtplugin/libghost.so"
//#define LIB_HOOK_PATH "/data/local/tmp/mtplugin/libhook.so"
//
//#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, MY_TAG, __VA_ARGS__)
//#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, MY_TAG, __VA_ARGS__)
//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, MY_TAG, __VA_ARGS__)


extern "C" 
{

void  kick(char* arg) {
	//void (*pMSHookFunction)();
	//pMSHookFunction = (void (*)())dlsym(pHandle, "MSHookFunction");
	LOGI(MY_TAG,  "kick(%s) - my_pid:%ld", arg, getpid());

    void *substrace_handle = dlopen(LIB_SUBSTRACE_PATH, RTLD_LAZY);
	
	if(substrace_handle){
       LOGI(MY_TAG, "dlopen %s ok.", LIB_SUBSTRACE_PATH);	
	}else{
       LOGE(MY_TAG, "dlopen %s fail!", LIB_SUBSTRACE_PATH);	
	   return;
	}

    void *hook_handle = dlopen(LIB_HOOK_PATH, RTLD_LAZY);
	
	if(hook_handle){
       LOGI(MY_TAG, "dlopen %s ok.", LIB_HOOK_PATH);	
	}else{
       LOGE(MY_TAG, "dlopen %s fail!", LIB_HOOK_PATH);	
	   return;
	}

	dlerror(); //reset errors
	typedef void (*phook_t)();
	phook_t pDoHook = (phook_t)dlsym(hook_handle, "DoHook");
	
	const char *dlsym_error = dlerror();

	if(!dlsym_error){
        LOGI(MY_TAG, "dlsym DoHook ok");	
	    pDoHook();
	}else{
        LOGE(MY_TAG, "dlsym DoHook fail for:%s", dlsym_error);	
		dlclose(substrace_handle);
		dlclose(hook_handle);
		return;
	}

}

}
