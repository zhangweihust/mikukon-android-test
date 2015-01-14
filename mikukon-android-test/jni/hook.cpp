#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <asm/ptrace.h>
#include <asm/user.h>
#include <asm/ptrace.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h> 

#include <string>
#include "substrate.h"

#include <android/log.h>
#include "my_constant.h"
//#include <cutils/log.h>

#define MY_TAG "hook.c"


//#define LIB_SUBSTRACE_PATH "/system/lib/libsubstrate.so"
//#define LIB_GHOST_PATH "/data/local/tmp/mtplugin/libghost.so"
//#define LIB_HOOK_PATH "/data/local/tmp/mtplugin/libhook.so"
//
//#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, MY_TAG, __VA_ARGS__)
//#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, MY_TAG, __VA_ARGS__)
//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, MY_TAG, __VA_ARGS__)

//void *(*md5_digest)(std::string  const&);

void log_z(const char* str){
	FILE * pFileTXT = fopen ("aTextFile.txt","w+");
    if(pFileTXT){
		fprintf (pFileTXT, "line:%s\n", str);
	    fclose (pFileTXT);
	}
}


void *(*old_md5_digest)(std::string  const&);


void *new_md5_digest(std::string  const& arg){
	//LOGI(MY_TAG, "new_md5_digest - OUT");
	//log_z(arg.c_str());
    old_md5_digest(arg);
	char c[100];
	strcpy(c, arg.c_str());
	LOGI(MY_TAG, "new_md5_digest:%s", c);
	return NULL;
}


void *(*old_MD5Update)(void *, unsigned char *, unsigned int);

void *new_MD5Update(void * arg1, unsigned char * arg2, unsigned int arg3){

	LOGI(MY_TAG, "new_MD5Update:%s, %d", arg2, arg3);
	old_MD5Update(arg1, arg2, arg3);

	return NULL;

}

extern "C" 
{

void  DoHook() {
	LOGI(MY_TAG,  "DoHook() - my_pid:%ld", getpid());

	//typedef void *(*p_md5_digest_t)(std::string  const&);
	//p_md5_digest_t p_md5_digest;

	typedef void *(*p_MD5Update_t)(void *, unsigned char *, unsigned int);
	p_MD5Update_t p_MD5Update;

	//p_md5_digest = (p_md5_digest_t) dlsym(RTLD_DEFAULT, "_Z10md5_digestRKSs"); 
	p_MD5Update = (p_MD5Update_t) dlsym(RTLD_DEFAULT, "_Z9MD5UpdateP11tag_MD5_CTXPhj"); 
	if(p_MD5Update){
        //void MSHookFunction(void*, void*, void**)
        //MSHookFunction(p_md5_digest, 
		//		&new_md5_digest, 
		//		&old_md5_digest);
	    //LOGI(MY_TAG,  "MSHookFunction - p_md5_digest: 0x%x, new_md5_digest: 0x%x, old_md5_digest: 0x%x", p_md5_digest,  &new_md5_digest, old_md5_digest);
        MSHookFunction(p_MD5Update, 
				&new_MD5Update, 
				&old_MD5Update);
	    LOGI(MY_TAG,  "MSHookFunction - p_MD5Update: 0x%x, new_MD5Update: 0x%x, old_MD5Update: 0x%x", p_MD5Update, &new_MD5Update, old_MD5Update);
	
	}else{
	    LOGI(MY_TAG,  "MSHookFunction fail - dlsym return null");
	}



}

}

/*
extern "C" 
{

void *(*test)(const char* arg);



void *new_test(const char* arg){
	LOGI(MY_TAG, "hack this success! zhw");
    return test(arg);
}


void  DoHook() {
	LOGI(MY_TAG,  "DoHook() - my_pid:%ld", getpid());

	void *(*ptest)(const char*);
	ptest = (void *(*)(const char*)) dlsym(RTLD_DEFAULT, "test"); 
	if(ptest){
        //void MSHookFunction(void*, void*, void**)
        MSHookFunction(ptest, 
				&new_test, 
				&test);
	    LOGI(MY_TAG,  "MSHookFunction - ptest: 0x%x, new_test: 0x%x, test: 0x%x", ptest,  &new_test, test);
	
	}else{
	    LOGI(MY_TAG,  "MSHookFunction fail");
	}



}

}
*/
