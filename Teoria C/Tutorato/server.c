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


void handle(char *msg)
{
    perror(msg);
    exit(1);
}

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


bool login(const char username[], const char ip[], int port)
{
    char line[128];
    FILE *db = fopen("database.txt", "r+"); // Controllo che db != NULL
    while (fgets(line, sizeof(line), db))
        if (strcmp(username, strtok(line, " ")) == 0) // Trovato conflitto
        {
            fclose(db);
            return 0; // Username già presente, operazione fallita
        }
    fprintf(db, "%s %s %d\n", username, ip, port); // Registrazione utente
    fclose(db);
    return true;

}


bool reg(Message* msg, FILE* fp)
{
    if(login(msg, fp))
     return false;
    fseek(fp, 0 , SEEK_END);
    fprintf(fp, "%s %s %d\n",msg->username, msg->)
   
}




int main(int argc, char* argv[])
{
    int sockfd , n;
    struct sockaddr_in client_addr, server_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    Message msg;

    if(argc < 2)
     handle("Erro argc");

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0 )) < 0)
     handle("Error socket()");


    memset(&msg, 0, sizeof(Message));
    memset(&client_addr , 0 , len);
    memset(&server_addr, 0 , len);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(argv[2]);


    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle("Error socket()");
    if((bind(sockfd, (struct sockaddr*)&server_addr, len)) < 0)
     handle("Error bind()");

    listen(sockfd, 5);

    puts("Listening...");


    while(1){

    }
    



    


}