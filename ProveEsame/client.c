/*
Realizzare un programma scritto in c (o c++) che simuli una partita a "Carta-Sasso-Forbice" fra i due Client, 
con il Server in mezzo a fare da arbitro. 
Si assuma che il numero di giocatori sia esattamente 2 e che tutti rispettino il protocollo descritto.
Appena avviato, ogni Client si connette al Server per registrarsi, 
fornendo anche le informazioni che il Server userà per comunicare durante la partita (ip, porta).
Quando entrambi i Client si sono registrati, 
il Server avvia la partita, impostando il numero di vite di entrambi i giocatori ad un valore stabilito. 
Inizia quindi ad interpellare a turno i due giocatori, chiedendo la loro mossa. Quando entrambi hanno giocato,
il Server comunica il risultato della partita a entrambi i giocatori. Se non si è verificato un pareggio, 
toglie una vita a quello che ha perso e ricomincia il ciclo.
Quando un giocatore rimane senza vite, il Server comunica il vincitore ad entrambi e termina la partita.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>


#define BUFFER_SIZE 1024

void handle_error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char** argv){
    int sockfd, n;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char responce[BUFFER_SIZE];
    char recvline[BUFFER_SIZE];


    if(argc < 3)
     handle_error("Error argc()");

    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle_error("error socket()");

    memset(&server_addr, 0 , len);
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[1]));

    sendto(sockfd, "REG", 3 , 0 , (struct sockaddr*)&server_addr, len);

    for(;;){
        printf("------\n");
        n = recvfrom(sockfd, recvline, BUFFER_SIZE , 0 , (struct sockaddr*)&server_addr, &len);
        printf("Server\n%s", recvline);

        if(strncmp(recvline, "TURNO", 5) == 0){
            fgets(responce, BUFFER_SIZE, stdin);
            sendto(sockfd, responce , BUFFER_SIZE, 0 , (struct sockaddr*)&server_addr,len);
            
        }

    }

}
