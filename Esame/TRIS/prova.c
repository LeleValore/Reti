/*
Realizzare un programma scritto in c (o c++) che simuli una partita a "Tris" fra i due Client, con il Server in mezzo a fare da arbitro.
 * Si assuma che il numero di giocatori sia esattamente 2 e che tutti rispettino il protocollo descritto.
 * Appena avviato, ogni Client si connette al Server per registrarsi, fornendo anche le informazioni che il 
 * Server userà per comunicare durante la partita (ip, porta).
 * Quando entrambi i Client si sono registrati, il Server avvia la partita.
 * Inizia quindi ad interpellare a turno i due giocatori, chiedendo dove porre il loro simbolo sulla griglia.
 * Dopo ogni mossa, il Server risponde inviando la griglia aggiornata.
 * Quando un giocatore ha vinto, il Server invia un messaggio di vittoria al vincitore e di sconfitta al perdente, 
 * quindi termina la partita.
*/


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void handle_error(char* msg){
    perror(msg);
    exit(1);
}


int main(int argc , char** argv){

    int n, sockfd;
    struct sockaddr_in6 server_addr;
    socklen_t len = sizeof(struct sockaddr_in6);
    char buffer[BUFFER_SIZE];

    if(argc < 3)
     handle_error("Errore argc");

    if((sockfd = socket(AF_INET6, SOCK_STREAM , 0)) < 0)
     handle_error("Errore socket()");

    memset(&server_addr, 0 , len);
    server_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &server_addr.sin6_addr);
    server_addr.sin6_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr*)&server_addr, len);


    printf("Connessione al server\n");
    for(;;){

        n = recv(sockfd, buffer, BUFFER_SIZE, 0);
        buffer[n] = '\0';

        if( n == 0)
         break;

        printf("%s\n", buffer); // 

        if(strstr(buffer, "hai vinto") == 0)
         break;
        
        int move;
        do
        {
            printf("Inserisci il valore nella matrice\n");
            printf(" | 1 | | 2 | | 3 |\n");
            printf(" | 4 | | 5 | | 6 |\n");
            printf(" | 7 | | 8 | | 9 |\n");
            fgets(buffer, BUFFER_SIZE, stdin);
            move = atoi(buffer);
            printf("Hai scelto la mossa %d\n", move); //
            
            
        }while(move < 1 || move > 9);

        printf("Invio l'informazione al server\n");
        send(sockfd, &move, sizeof(int),0 );

    }
    close(sockfd);
    return 0;
}