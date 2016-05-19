#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int (*f)(int);  

bool init_library(char *libname,char *fname){
 	void *hdl = dlopen(libname,RTLD_LAZY);
 	if (NULL==hdl)
 		return false;
 	f=(int (*)(int))dlsym(hdl,fname);
 	if (NULL==f)
 		return false;
 	return true;
 }

int main(int argc,char *argv[]) {
 	if (init_library(argv[1],argv[2])){
 		int value=atoi(argv[3]);
		printf("%d\n",f(value));
	}
 	else
 		printf("error");
 	return 0;
 }
