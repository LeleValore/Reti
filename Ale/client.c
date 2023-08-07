#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void handle_error(char* msg)
{
    perror(msg);
    exit(1);
}

int main(int argc , char** argv)
{
    int n, sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFF_SIZE];
    char responce[BUFF_SIZE];

    if(argc < 3)
     handle_error("Error argc");
    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle_error("Error socket()");

    memset(&server_addr, 0 , len);
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[2]));


    sendto(sockfd, "REG", 3 , 0 , (struct sockaddr*)&server_addr, len);

    puts("Invia messaggio:\n");
    for(;;)
    {  
        fgets(buffer, BUFF_SIZE , stdin);
        sendto(sockfd , buffer , strlen(buffer) + 1, 0 , (struct sockaddr*)&server_addr, len);

        if(strncmp(buffer,"RISORSA", 7) == 0){
         recvfrom(sockfd, responce, BUFF_SIZE , 0 , (struct sockaddr*)&server_addr, &len);
         printf("Messaggio:%s", responce);
        }

         
    }
    close(sockfd);
    return 0;
}