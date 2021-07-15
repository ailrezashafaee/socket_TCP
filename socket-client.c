#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#define SIZE 10000
int isValid(char *expression)
{
    int flag = 0;
    int k;
    for(int i=0 ; i < strlen(expression) ;i++)
    {
        if( (expression[i] == '+') || (expression[i] == '-') || (expression[i] == '*') || (expression[i] == '/') )
        {
            flag =1;
            k = i;
            break;
        }
    }
    for(int i =0  ; i < strlen(expression) ; i++)
    {
        
        if(expression[i] == ' ')
        {
            break;
        }
        if(k!=i)
        {       
            if( expression[i] > '9' || expression[i] < '0')
            {
                break;
            }
        }
    }
    
    return flag;
}
int main(int argc, char *argv[])
{
    int mysocket = 0;
    struct sockaddr_in client;
    if(argc != 6)
    {
        printf("\n Please use the format: %s -h <serveraddress> -p <portnumber> <text>\n",argv[0]);
        return 1;
    } 
    
    char *buffer= argv[5];
    if(!isValid(buffer))
    {
        printf("please enter the expression properly  : <number1>(+,-,*,/)<number2>");
        return 1;
    }
    if((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {       
        puts("There is a problem in socket creation"); 
        return 1;
    } 
    client.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[2], &client.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
    client.sin_port = htons(atoi(argv[4])); 

    if( connect(mysocket, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
    printf("\n Socket connetction failed \n");
    return 1;
    } 
    int readcnf= 0 , sendcnf = 0;
    sendcnf = send(mysocket ,buffer, strlen(buffer) , 0 );
    if(sendcnf < 0)
    {
        perror("send failed in client program"); 
    }
    char server_reply[SIZE];
    readcnf = recv(mysocket , server_reply , SIZE , 0);
    if(readcnf ==0)
        {
            printf("Client disconected");
            return 0;        
    }else if(readcnf < 0)
        {
            perror("rvec failed in client program");  
            return 0;
        }else{
            printf("%s" , server_reply);
        }
    return 0;
}