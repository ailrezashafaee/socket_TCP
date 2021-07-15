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
    #include<pthread.h> 
    #define SIZE 10000
    char* substr(const char *src, int m, int n)
        {
        int len = n - m;
    
        char *dest = (char*)malloc(sizeof(char) * (len + 1));
        for (int i = m; i < n && (*(src + i) != '\0'); i++)
        {
            *dest = *(src + i);
            dest++;
        }
        *dest = '\0';
        return dest - len;
    }
    float calculator(char *expression)
    {
        char *first="" , *sec = "";
        float n1 , n2;
        int i =0;
        while((expression[i] != '+') && (expression[i] != '-') && (expression[i] != '/') && (expression[i] != '*'))
        {
            i++;
        }
        printf("%d%d\n\n", i ,(int) strlen(expression));
        first = substr(expression , 0 , i);
        puts(first);
        n1 = atoi(first);
        sec = substr(expression , i+1 ,(int) strlen(expression));
        puts(sec);
        n2 = atoi(sec);
        switch (expression[i])
        {
        case '+':
            return n1 + n2;
        case '-':
            return n1 - n2;
        case '*' :
            return n1 * n2;
        case '/':   
            return n1/n2;
        }
    }
    void *connectionHandler(void *parlSocket)
    {
        puts("thread is running");
        char buffer[SIZE] = "", reply[SIZE];
        int readcnf = 0;
        int socket = *(int*)parlSocket;
        readcnf = recv(socket , buffer , sizeof(buffer) , 0);
            if(readcnf ==0)
            {
                printf("Client disconected\n");        
            }else if(readcnf < 0)
            {
                printf("fail");
                perror("rvec failed in server program");  
            }else{
                gcvt(calculator(buffer), SIZE,reply);
                write(socket , reply , strlen(reply));   
            }
        free(parlSocket);
        return 0;
    }
    int main(int argc, char *argv[])
    {
        int mySocket , *parlSocket;
        
        mySocket = socket(AF_INET , SOCK_STREAM , 0);
        struct sockaddr_in server;
        if(argc != 5)
        {
            printf("please use the format :Name -h <listenaddress> -p <portnumber>");
            return 1;
        }
        if (mySocket == -1)
        {
            printf("There is a problem in socket creation"); 
            return 1;
        }
        server.sin_family = AF_INET;
        if(inet_pton(AF_INET , argv[2] ,&server.sin_addr)<=0)
        {
            printf("inten pton failed!");
            return 1;
        }
        server.sin_port = htons(atoi(argv[4]));

        if( bind(mySocket,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
            perror("bind failed. Error");
            return 1;
        }
        listen(mySocket , 10);
        puts("socket is listening to connetctions of client...");
        
        int conncnf = 0;
        int readcnf = 0;
        int numberOfClients = 0;
        char reply[SIZE];
        while(1)
        {
            conncnf = accept(mySocket , (struct sockaddr*) NULL , NULL);
            pthread_t thread;
            parlSocket = malloc(1);
            *parlSocket = conncnf;
            puts("client conneted to socket");
            numberOfClients++;
            printf("number of clients :%d\n" , numberOfClients);
            if(pthread_create(&thread , NULL ,connectionHandler , (void*) parlSocket) < 0)
            {
                perror("Thread creation failed in server program");
                return 1;
            }
            pthread_join(thread, NULL);
            
            close(conncnf);
        }
    }