#define _GNU_SOURCE

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include<dlfcn.h>
#include<sys/mman.h>

void justDoit(const char* myshellcode){
    int mprotectstatus = -1; //default to failure

    void * payloadBase = NULL; //page where our payload is stored
    size_t pageSize = 0;

    unsigned char * payload = NULL;
    void (*execShellcode)(void) = NULL;

    payload = (unsigned char*) malloc(sizeof(myshellcode)*sizeof(char));

    if(!payload){
        return;
        //if not enough memory to host our shell code
    }

    pageSize = sysconf(_SC_PAGE_SIZE);
    payloadBase = (void*)((uintptr_t)payload & );
}