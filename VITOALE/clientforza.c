#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void handle_error(char* msg){
    perror(msg);
    exit(1);
}

char** creatematrix(){

    char** matrix = (char**)malloc(6*sizeof(char*));
    for(int i = 0 ; i < 6 ; i++){
        matrix[i] = (char*)malloc(7*sizeof(char));
        for(int j = 0 ; j < 7 ; j++){
            matrix[i][j] = ' ';
        }
    }
    return matrix;
}


char** azzera_matrice(char** matrix){
  
    for(int i = 0 ; i < 6 ; i++){
        for(int j = 0 ; j < 7 ; j++){
            matrix[i][j] = ' ';
        }
    }
    return matrix;
}


typedef struct{

    struct sockaddr_in client;

}Giocatore;

// void sett giocartore 


char * manda_stato_gioco(char** matrix){
    char buffer[BUFFER_SIZE];
    strcpy(buffer, " ");

    for(int i = 0; i < 6 ; i++){
        strcat(buffer, " | ");
        strcat(buffer, "\n");
        for(int j = 0; j < 7; j++){
            strcat(buffer, "_");

        }
    }
    return strdup(buffer);

}

void moss_giocatore(int giocatore , int colonna ,char** matrix)
{
    int indice;

    for(int i = 0; i< 6 ; i++){
            if(matrix[i][colonna] = ' '){
                indice = i-1;
                break;
            }
    }
    if(giocatore == 1){
        matrix[indice][colonna] = 'X';
    }else if(giocatore == 2){
         matrix[indice][colonna] = '0';
    }

}

void partita(Giocatore uno, Giocatore due , int sockfd, socklen_t len, char** matrix){
    printf("[+]Inizio partita\n");
    int turno = 1;
    int n;
    char buffer[BUFFER_SIZE];
    int numeroClient;

    for(;;){
        if(turno == 1){
            sendto(sockfd,"TURNO MANDA UN NUMERO DA 1 a 7",100,0,(struct sockaddr*)&uno.client, len);
            n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&due.client, &len);
            buffer[n]= '\0';
            numeroClient = atoi(buffer);
            while(numeroClient < 1 || numeroClient > 7){
                sendto(sockfd, "ERRORE HAI MESSO UN NUMERO INADATTO", 100, 0 , (struct sockaddr*)&uno.client, len);
                n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&due.client, &len);
                buffer[n]= '\0';
                numeroClient = atoi(buffer);
            }
            
        }else if( turno == 2){
            
            sendto(sockfd,"TURNO MANDA UN NUMERO DA 1 a 7",100,0,(struct sockaddr*)&due.client, len);
            n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&uno.client, &len);
            buffer[n]= '\0';
            numeroClient = atoi(buffer);
            while(numeroClient < 1 || numeroClient > 7){
                sendto(sockfd, "ERRORE HAI MESSO UN NUMERO INADATTO", 100, 0 , (struct sockaddr*)&due.client, len);
                n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&uno.client, &len);
                buffer[n]= '\0';
                numeroClient = atoi(buffer);
            }
            mossa_giocatore();
            turno = 1;   
        }
        

    }
}

int main(int argc, char** argv){
    int sockfd, n;
    struct sockaddr_in client_addr, server_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    char** matrix = creatematrix();
    char* stampa_matrice = manda_stato_gioco(matrix);
    int n_giocatore = 0;
    printf("%s \n", stampa_matrice);
    Giocatore uno;
    Giocatore due;

    if(argc < 2) 
     handle_error("Errore argomenti");

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
     handle_error("Errore sockfd");


    memset(&server_addr, 0 , len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));

    if((bind(sockfd, (struct sockaddr*)&server_addr, len)) < 0)
     handle_error("Error bind()");


    for(;;){
        while(n_giocatore != 2){
            n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0 , (struct sockaddr*)&client_addr, &len);
            buffer[n]='\0';

            if(strcmp(buffer, "REG") == 0){

            }
        }

    }

    

    
}