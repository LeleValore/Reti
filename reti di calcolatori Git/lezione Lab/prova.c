#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>


#define IP "127.0.0.1"
#define PORT 8080 //deve essere tra 0 e 65535



/* Utilizzata per rappresentare un indirizzo IP di una socket in TCP/IP come architettura di rete 
        struct sockaddr_in
        {
            short int sin_family;  (famiglia di protocolli utilizzata (IPV4, IPV6))
            unsigned short int sin_port; (porta utilizzata per la comunicazione 0 - 65535)
            struct in_addr sin_addr; (contiene indirizzo ip del host remoto)
            unsigned char sin_zero[8]; (8 byte di zeri)
        }


        struct sockaddr
        {
            u_short sa_family;  //socket adress family, usato per distinguere tra ipv4 o ipv6 (AF_INET opp AF_INET6)
            char sa_data[14];   //socket adress data
        }




*/


int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in addr;
    char buffer[100];
    

    if(sockfd = socket(AF_INET, SOCK_DGRAM , 0) < 0)//in socket abbiamo definito (domain (ipv4), abbiamo fatto SOCK_DGRAM per indicare che é di tipo UDP, 0 é il protocollo utilizzato)
    {
        perror("Server Socket Error\n");
        exit(1);

    }
    print("SOcket Creata");

    memset(&addr , 0 , sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, IP, &(addr.sin_addr));
    addr.sin_port= htons(PORT);

    int n = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)); //sockfd é il descrittore del socket da associare all'IP e porta definiti #define IP #define PORT)
    if(n < 0 )                                                     // (struct sockaddr*)&server_addr casting del puntatore generico alla struttura sockaddr ci serve per associare la socket é un parametro necessario per la funzione bind )
    {
        perror("Socket Server Error");
        exit(1);

    }
    printf("Binding Socket");

    listen(sockfd,  5);
    puts("Ascolto...");


    while(1)
    {
        socklen_t size = sizeof(addr);//utilizzaya per memorizzare la dimensione dell'indirizzo del pacchetto ricevuto.
        ssize_t nread = recvfrom(sockfd, buffer, sizeof(buffer), 0 ,(struct sockaddr*)&addr, &size); // recvfrom() riceve un pacchetto dalla socked sockfd inizializzata all'inizio e lo memorizza nel buffer 
        // ha i seguenti parametri 
        /*
        sockfd -->descrittore della sulla quale ricevere il pacchetto
        buffer --> il puntatore buffer in cui memorizzare i dati ricevuti 
        sizeof(buffer) -->la dimensione massima del buffer 
        (struct sockaddr*) & addr --> il pèuntatore alla struttura scockaddr in cui memorizzare l'indirizzo del mitente del pacchetto.
        &size -->contiene la dimensione dell'indirizzo del mitente
        */

        char client[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr.sin_addr), client, INET_ADDRSTRLEN);
        /*
          Ha parametri:
          AF_INET -> il tipo di indirizzo utilizzato (ipv4)
          &(addr.sin_addr) -> puntatore all'indirizzo ipv4 da convertire 
          client -> il buffer in cui vengono memorizzati i risultati 
          INET_ADDRSTRLEN -> la dimensione massima del buffer in byte
        
        */
       printf("Request from client %s:\t%s\n\n", client, buffer); // stampo il messaggio ricevuto dal mitente 
       
       char* response = "OK";
       ssize_t nwrite = sendto( sockfd, response, strlen(response), 0, (struct sockaddr*)&addr, size);
       
       /*
        PARAMETRI SENDTO() -->restituisce il numero di byte effettivamente inviati, che viene memorizzato nella variabile nwrite di tipo struct ssize_t
        sockfd: il descrittore della socket sulla quale inviare il pacchetto.

        response: il puntatore ai dati da inviare.

        strlen(response): la lunghezza dei dati in byte da inviare.

        (struct sockaddr*) &addr: il puntatore alla struttura sockaddr contenente l'indirizzo del destinatario.

        size: la dimensione dell'indirizzo del destinatario.


            
       
       */

    }
    close(sockfd);
    return 0;





}