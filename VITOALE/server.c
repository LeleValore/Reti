#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>


#define MAX_GIOCATORE 2
#define BUFFER_SIZE 1024

typedef struct{
    char* nome;
    struct sockaddr_in client_addr;
    int vita;

}Giocatore;

void handle_error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char** argv){

    int n ,sockfd;
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr, server_addr;
    char buffer[BUFFER_SIZE];
    Giocatore giocatore[MAX_GIOCATORE];

    char *matrix[] = {"Ciao", "Miao", "Errore", "Ingegnere"};

    if(argc < 2)
     handle_error("Error pochi errori");

    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle_error("Error socket...");

    memset(&server_addr, 0 , size);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port= htons(atoi(argv[1]));

    


    



}