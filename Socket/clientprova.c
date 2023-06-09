#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Hello, server!";

    // crea una socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    // inizializza la struttura per l'indirizzo del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // indirizzo IP del server
    server_addr.sin_port = htons(PORT);

    // invia i dati al server
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Errore nell'invio dei dati");
        exit(EXIT_FAILURE);
    }

    printf("Dati inviati: %s\n", buffer);

    // riceve la risposta dal server
    if (recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL) < 0) {
        perror("Errore nella ricezione della risposta");
        exit(EXIT_FAILURE);
    }

    printf("Risposta ricevuta: %s\n", buffer);

    // chiude la socket
    close(sockfd);

    return 0;
}
