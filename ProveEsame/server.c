#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>


#define BUFFER_SIZE 1024

void handle_error(char* msg){
    perror(msg);
    exit(1);
}

typedef struct{
    char mossa[20];
    struct sockaddr_in client;
    int vita;
    int vittoria;

}Giocatore;

void inizializza_giocatore(Giocatore *uno, struct sockaddr_in client_addr){
    int porta = ntohs(client_addr.sin_port);
    uno->client.sin_port = htons(porta);
    uno->vita = 1;
    uno->client.sin_family = AF_INET;
    uno->client.sin_addr = client_addr.sin_addr;

}

void mossa_vincente(Giocatore *uno, Giocatore *due)
{
    printf("MOSSA GIOCATORE UNO%s MOSSA GIOCATORE DUE%s", uno->mossa , due->mossa);
    if(strcmp(uno->mossa, "FORBICE") == 0 && strcmp(due->mossa, "SASSO") == 0)
    {
        due->vittoria = 1;
        return;
    }
    if(strcmp(uno->mossa, "FORBICE") == 0 && strcmp(due->mossa, "CARTA") == 0)
    {
        uno->vittoria = 1;
        return;
    }
    if(strcmp(uno->mossa, "SASSO") == 0 && strcmp(due->mossa, "CARTA") == 0)
    {
        due->vittoria = 1;
        return;
    }
    if(strcmp(uno->mossa, "SASSO") == 0 && strcmp(due->mossa, "FORBICE") == 0)
    {
        uno->vittoria = 1;
        return;
    }
    if(strcmp(uno->mossa, "CARTA") == 0 && strcmp(due->mossa, "SASSO") == 0)
    {
        uno->vittoria = 1;
        return;
    }
    if(strcmp(uno->mossa, "CARTA") == 0 && strcmp(due->mossa, "FORBICE") == 0)
    {
        due->vittoria = 1;
        return;
    }

}


void partita(Giocatore uno , Giocatore due, int sockfd , socklen_t len)
{
    int n;
    char recvline[BUFFER_SIZE];

    sendto(sockfd, "PARTITA INIZIATA", 30 , 0 , (struct sockaddr*)&uno.client, len);
    sendto(sockfd, "PARTITA INIZIATA", 30 , 0 , (struct sockaddr*)&due.client, len);

    printf("Partita iniziata\n");
    int contamosse= 0;
    int turno = 0;
    char *mossa;
    int numero_giocatori;
    while(uno.vita != 0 && due.vita != 0){

        if(turno== 0){
            sendto(sockfd, "TURNO SCEGLI CARTA FORBICE SASSO", 100, 0 , (struct sockaddr*)&uno.client, len);
            n = recvfrom(sockfd, recvline, BUFFER_SIZE , 0 , (struct sockaddr*)&uno.client, &len);
            mossa = strtok(recvline, "\n");
            strcpy(uno.mossa, mossa);
            contamosse++;
            turno = 1;
        }else{
            sendto(sockfd, "TURNO TUO SCEGLI CARTA FORBICE SASSO", 100, 0 , (struct sockaddr*)&due.client, len);
            n = recvfrom(sockfd, recvline, BUFFER_SIZE, 0 , (struct sockaddr*)&due.client, &len);
            mossa = strtok(recvline, "\n");
            strcpy(due.mossa, mossa);
            contamosse++;
            turno = 0;
        }
        if(contamosse % 2 == 0){
            if(strcmp(uno.mossa, due.mossa) == 0){
                sendto(sockfd, "PAREGGIO", 100, 0 , (struct sockaddr*)&uno.client, len);
                sendto(sockfd, "PAREGGIO", 100, 0 , (struct sockaddr*)&uno.client, len);
            }else{
                if(uno.vittoria == 1){
                    mossa_vincente(&uno , &due);
                    sendto(sockfd, "VINTO", 100, 0 , (struct sockaddr*)&uno.client, len);
                    sendto(sockfd, "PERSO", 100, 0 , (struct sockaddr*)&due.client, len);
                    due.vita = due.vita -1 ;
                }else if( due.vittoria == 1){
                     sendto(sockfd, "VINTO", 100, 0 , (struct sockaddr*)&due.client, len);
                    sendto(sockfd, "PERSO", 100, 0 , (struct sockaddr*)&uno.client, len);
                    uno.vita = uno.vita -1 ;
                }

            }
            printf("VITA 1 %d VITA 2 %d\n", uno.vita, due.vita);
        }
      
    }
    printf("FINE PARTITA\n");

}


int main(int argc, char** argv)
{
    int sockfd, n;
    struct sockaddr_in remote_addr ,local_addr;
    int numero_giocatori = 0;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    char *mossa;
    int turno = 0;
    Giocatore uno;
    Giocatore due;

    if(argc < 2 )
     handle_error("Errore argc");
    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle_error("Errore socket");



    memset(&local_addr, 0 , len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    if((bind(sockfd, (struct sockaddr*)&local_addr, len)) < 0)
     handle_error("Error bind()");
    
    for(;;){
        while(numero_giocatori != 2){
            n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&remote_addr, &len);
            buffer[n] = 0;
            if(strncmp(buffer, "REG", 3 ) == 0 && numero_giocatori == 0){
                inizializza_giocatore(&uno, remote_addr);
                numero_giocatori++;
            }else if (strncmp(buffer, "REG", 3 ) == 0 && numero_giocatori == 1){
                inizializza_giocatore(&due, remote_addr);
                numero_giocatori++;
            }
        }
        partita(uno , due , sockfd, len);
        numero_giocatori = 0;
    }


    

}