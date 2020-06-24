#define _GNU_SOURCE


#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

const char* magicPattern = "hit";

int strcmp(const char* str1, const char* str2){
    int ret = 0;

    //function pointer to string compare
    int (*orig_strcmp)(const char* str1, const char* str2)= NULL;

    //function here dlsym returns the address of next occurence of strcmp(the original one)
    orig_strcmp = (int(*)(const char* str1, const char* str2)) dlsym(RTLD_NEXT,"strcmp");

    if (!orig_strcmp){
        printf("failed to locate stringcmp");
        return ret;
    }

    if (!orig_strcmp(magicPattern,str2) || !orig_strcmp(magicPattern, str1))
    {
        return ret;
    }
    
    ret = orig_strcmp(str1,str2);
    return ret;
}