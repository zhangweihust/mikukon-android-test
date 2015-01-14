/*
 * main.c
 *
 *  Created on: 2012-5-4
 *      Author: amos
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "injectso.h"



void die(int ln, const char* file){
	char temp[256];
	snprintf(temp, sizeof(temp), "failed at %d in %s: %s\n", ln, file,strerror(errno));
	fprintf(stderr, temp);
	exit(-1);
}

int main(int argc, char **argv) {

	if(argc != 4){
        //LOGE(MY_TAG, "usage: %s pid lib_path<libghost> func_name<kick>", argv[1]);
        printf("usage: %s pid lib_path<libghost> func_name<kick>", argv[0]);
		return 0;
	}else{
	    printf("argv[0]:%s, argv[1]:%s, argv[2]:%s, argv[3]:%s", argv[0], argv[1], argv[2], argv[3]);
	}

	int pid = atoi(argv[1]);

	inject_process(pid, argv[2], argv[3], "Hook start !!", strlen("Hook start !!") );
	//inject_process(pid, argv[2], argv[3]);

	return 0;
}
