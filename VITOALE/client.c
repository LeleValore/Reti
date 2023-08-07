#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void handle_error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc , char** argv){

    int sockfd, n;
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    if(argc < 3)
     handle_error("errore servono piu argomenti");
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle_error("Error socket");

    memset(&server_addr , 0 , size);
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[2]));


    printf("Inserisci il nome per l'autenticazione\n");
    memset(buffer, 0 , strlen(buffer));
    fgets(buffer, strlen(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '0';


    printf("Connesione col server\n");
    sendto(sockfd, buffer, BUFFER_SIZE, 0 , (struct sockaddr*)&server_addr, size);
    perror("Errore autenticazione");


    for(;;){
        
        memset(buffer, 0 , strlen(buffer));
        recvfrom(sockfd, buffer, strlen(buffer)+1 , 0 , (struct sockaddr*)&server_addr, &size);
        perror("Error recvfrom()");

        printf("%s", buffer);

        if(strstr(buffer, "Fine partita"))
         break;


        printf("Inserisci una parola o una lettera\n");
        fgets(buffer, strlen(buffer)+1, stdin);
        buffer[strcspn(buffer, "\n")]= '0';


        printf("Hai scelto la lettera o parola%s %s \n", strlen(buffer) == 1  ? "lettera" : "parola", buffer);

        
        sendto(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&server_addr, size);
       perror("Errore sendto()");
    }
    close(sockfd);

    return 0;

}
