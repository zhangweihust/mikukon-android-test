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

#include <android/log.h>

extern "C" 
{

int test(const char* s) {
	pid_t my_pid = getpid();
	__android_log_print(ANDROID_LOG_VERBOSE, "injectso", "s:%s, my_pid:%ld", s, my_pid);
	return 0;
}

jstring Java_com_example_inject_Demo_stringFromJNI( JNIEnv* env, jobject thiz )
{
    test("normal call test");
    //return (*env)->NewStringUTF(env, "test call done success");
	return env->NewStringUTF((char *)"Hello from JNI !");//c++ format
}

}


