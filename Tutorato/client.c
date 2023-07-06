#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define SECRET_SIZE 51
#define VM_LIST_SIZE 128
#define USERNAME_SIZE 21

typedef enum
{
    LOGIN = 'l',
    UPDATE_LIST = 'u',
    UPDATE_SECRET = 's',
    GET_SECRET = 'g',
    EXIT = 'e',
} Operation;

typedef struct
{
    Operation op;
    char secret[SECRET_SIZE];
    char vm_list[VM_LIST_SIZE];
    char username[USERNAME_SIZE];

} Message;

void handle(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    Message msg;

    if (argc < 3)
        handle("error argc");

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        handle("error socket()");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[2]));

    while (1)
    {

        printf("Enter a request:\n");
        printf("<l> login:\n");
        printf("<u> to update a user:\n");
        printf("<s> update the secret message:\n");
        printf("<g> to get a secret message:\n");
        printf("<e> to exit:\n");
       


        msg.op = getchar();
        while(getchar() != '\n'){

            printf("operazione: %c\n", msg.op);
            switch(msg.op)
            {

                case LOGIN:

                   printf("Inserisci il tuo username:\n");
                   fgets(buffer, BUFFER_SIZE , stdin);
                   msg.username[strlen(msg.username) - 1] = '\0';
                   printf("Inserisci la tua macchina con la quale condividere il messaggio\n:");
                   fgets(buffer, BUFFER_SIZE , stdin);
                   msg.vm_list[strlen(msg.vm_list) - 1] = '\0';
                   printf("Inserisci il tuo segreto:");
                   fgets(buffer, BUFFER_SIZE , stdin);
                   msg.secret[strlen(msg.secret) - 1] = '\0';
                   break;

                case UPDATE_LIST:

                   printf("Inserisci la tua macchina con la quale condividere il messaggio\n:");
                   fgets(buffer, BUFFER_SIZE , stdin);
                   msg.vm_list[strlen(msg.vm_list) - 1] = '\0';
                   break;

                case UPDATE_SECRET:

                   printf("Inserisci il tuo segreto:");
                   fgets(buffer, BUFFER_SIZE , stdin);
                   msg.secret[strlen(msg.secret) - 1] = '\0';
                   break;

                case GET_SECRET:

                  printf("Inserisci la tua macchina con la quale condividere il messaggio\n:");
                  fgets(buffer, BUFFER_SIZE , stdin);
                  msg.vm_list[strlen(msg.vm_list) - 1] = '\0';
                  break;

                case EXIT:
                    
                  close(sockfd);
                  exit(EXIT_SUCCESS);

                default:
                  printf("Enter a VALID REQUEST:");
                  continue;

            }

            if(strcmp(msg.username , buffer) == 0){

                printf("Devi effettuare il login:");
                exit(EXIT_FAILURE);
            }

            if((sendto(sockfd, &msg , sizeof(Message), 0 , (struct sockaddr*)&server_addr , len)) < 0)
             handle("Error to sendto()");

            if((n = recvfrom(sockfd, buffer, sizeof(buffer), 0 , (struct sockaddr*)&server_addr, &len)) < 0)
             handle("Error recvfrom()");


        }
    }

    return 0;
}