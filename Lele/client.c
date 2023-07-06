#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



#define BUFFER_SIZE 1024

void handle_error(char* msg)
{
    perror(msg);
    exit(1);
}

typedef struct{
    char op[10];
    char user[20];
    char pass[40];
}Message;



int main(int argc, char* argv[]){

    int n, sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    Message msg;


    if( argc < 3 )
    {
        handle_error("argc()");
    }
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        handle_error("error to socket()");

    }

    memset(&server_addr , 0 , sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[2]));

    if((connect(sockfd,(struct sockaddr*)&server_addr, len)) < 0)
     handle_error("connect()");

    while(1)
    {
        printf("Puts LOG REG DEL");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strlen(buffer)-1]= 0;

        if(strcasecmp(buffer, "REG") == 0 || strcasecmp(buffer, "LOG") == 0 || strcasecmp(buffer, "DEL")== 0)
        {
            strcpy(msg.op , buffer);
            buffer[strlen(buffer)-1]= 0;


            printf("Puts a user...");
            fgets(buffer, BUFFER_SIZE , stdin);
            buffer[strlen(buffer)-1] = 0;
            strcpy(msg.user, buffer);

            printf("Puts a pass...");
            fgets(buffer, BUFFER_SIZE , stdin);
            buffer[strlen(buffer)-1] = 0;
            strcpy(msg.pass, buffer);

            if((send(sockfd, &msg, sizeof(Message), 0)) < 0)
             handle_error("Error send()");

            if((n = recv(sockfd, buffer, BUFFER_SIZE, 0)) < 0)
             handle_error("Error to socket...");
            buffer[n]= 0; 

        }
        if(strcasecmp(buffer, "EXIT") == 0)
        {
            printf("Goodbye\n");
            break;
        }
    } 
    return 0;

}