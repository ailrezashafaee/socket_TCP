#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 	
int main(int argc, char *argv[])
{
    int mySocket;
	mySocket = socket(AF_INET , SOCK_STREAM , 0);
    struct sockaddr_in server;
    printf()
    if (mySocket == -1)
	{
		puts("There is a problem in socket creation"); 
	}
    if(argc != 3)
    {
        puts("please use the format :name <ip address> <port>");
    }
    server.sin_family = AF_INET;
	if(inet_pton(AF_INET , argv[1] ,&serv_addr.sin_addr)<=0)
    {
        puts("we sucked");
    }

	server.sin_port = htons(atoi(argv[2]));
   
    if( bind(mySocket,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
    listen(mySocket , 10);
    puts("socket is listening to connetctions of client...");
    // listening to clients : 
    int conncnf = 0;
    int count = 0;
    while(count != 10)
    {
        conncnf = accept(mySocket , (struct sockaddr*) NULL , NULL);
        puts("client conneted to socket");
        close(conncnf);
        
    }
}