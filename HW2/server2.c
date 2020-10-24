#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pwd.h>

#define PORT 8080 //when running listen to port 8080

int main(int argc, char const *argv[])
{
	int new_socket = atoi(argv[1]); 
	int valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[102] = {0}; // size holding 102 arbit
    char *hello = "Hello from server";
	

	char socket_str[100];
	char filepath[100];

	pid_t childpid;
	char x='X';
	char *ptr;
	ptr=&x;

	int tempuid = 0;
	uid_t uid;

	printf("Child process  created addr2: %p\n", ptr);
	printf("childpid = %d\n", childpid);


	printf("Initial uid = %d\n", getuid());
			
	//nobody user
	tempuid = setuid(65534);
	printf("tempuid = %d\n" "uid = %d\n", tempuid, getuid());


	//read from client into buffer, max of 1024 bytes --> bigger than size of buffer (102)
			//no need to change it
			valread = read( new_socket , buffer, 1024);
			printf("%s\n",buffer );

			//send = write 
			send(new_socket , hello , strlen(hello) , 0 );

			//send message 
			printf("Hello message sent\n");

			//close(server_fd);

		return 0;
}
