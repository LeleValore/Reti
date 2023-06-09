#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void handle_error(char* msg)
{
    perror(msg);
    exit(1);
}

int main(int argc , char* argv[])
{
    int sockfd;
    struct sockaddr_in6 client_addr;
    socklen_t len = sizeof(struct sockaddr_in6);
    char buffer[1024];


    if(argc != 3)
    {
        handle_error("[-]More Argometres...");
        
    }

    if(sockfd = socket(AF_INET6 , SOCK_DGRAM , 0 ) < 0 )
    {
        handle_error("[-]Socket not created...");
    }
    printf("[+]Socket Created successfully...");


    memset(&client_addr, 0 , sizeof(client_addr));
    client_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &client_addr);
    client_addr.sin6_port = htons(atoi(argv[1]));

    while(fgets(buffer, 1024, stdin))
    {
        printf("[+]Put a request...");
        if(sendto(sockfd, buffer, strlen(buffer),0, (struct sockaddr*)&client_addr, len) < 0)
         handle_error("[-]Error send...");
        if(strcmp("Stop", buffer) == 0) break;

        if(recvfrom(sockfd, buffer, 1024 , 0 ,(struct sockaddr*)& client_addr, &len) < 0)
          handle_error("[-]Error recvfrom...");
        
        printf("Reply: %s\n", buffer);  
    }
    close(sockfd);
    return 0;

}