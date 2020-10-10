// Server side C/C++ program to demonstrate Socket programming
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
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[102] = {0}; // size holding 102 arbit
    char *hello = "Hello from server";


	pid_t childpid;
	char x='X';
	char *ptr;
	ptr=&x;

	int tempuid = 0;
	uid_t uid;

    printf("execve=0x%p\n", execve);


		//create socket that is AF_INET network - socket, system hand back file descriptor = number, endpoint for socket to accept incoming connections
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	
	//listen on network 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

	//listen on port 8080
    address.sin_port = htons( PORT );


		//associate socket to desired port
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

		//accept from new file descripter (socket) -- read and write to it from file
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }



		/*if(getuid())
		{
			errx(1, "need root access");
			
		}

		if((pw = getpwnam(NOBODY_USER)) == NULL)
		{

			errx(1, "nobody user %s", NOBODY_USER);
		}*/
//FORK HERE!
	
		if ((childpid = fork()) == 0)
		{
			
			printf("Forked\n");
			printf("Child process  created addr: %p\n", ptr);
			printf("childpid = %d\n", childpid);
		
			printf("Initial uid = %d\n", getuid());
			
			//nobody user
			tempuid = setuid(65534);
			printf("tempuid = %d\n" "uid = %d\n", tempuid, getuid());
			
		close(server_fd);

		}
	
		else
		{
		sleep(5);
		printf("\n Parent process addr: %p", ptr);
		printf("\n parentpid = %d\n", childpid);
		}


//read from client into buffer, max of 1024 bytes --> bigger than size of buffer (102)
	//no need to change it
   		 valread = read( new_socket , buffer, 1024);
   		 printf("%s\n",buffer );

	//send = write 
    		send(new_socket , hello , strlen(hello) , 0 );

	//send message 
   		 printf("Hello message sent\n");

    return 0;
}
