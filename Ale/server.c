#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>


#define BUFF_SIZE 1024
void handle_error(char* msg)
{
    perror(msg);
    exit(1);
}


void REG(char *ip , int port){

    FILE * fp;
    if((fp = fopen("database.txt", "w+")) < 0 )
     handle_error("Error apertura del file");

    int id = rand() % __INT_MAX__;
    fprintf(fp, "%s %d %d\n", ip , port, id);
    fclose(fp);
}

char* elenco_risorse(){

    FILE *fp;
    if((fp = fopen("risorsa.txt", "r")) < 0)
     handle_error("error apertura del file..");
    


    char buffer[BUFF_SIZE];
    memset(buffer, 0 , BUFF_SIZE);
    strcpy(buffer,"");
    char *risorsa , *quantita;
    char string[BUFF_SIZE];
    while(fscanf(fp,"%s\n", buffer)==1) //ricorda fare la fscanf
    {
        risorsa = strtok(buffer, ":");
        quantita = strtok(NULL, ":");

        if(atoi(quantita) > 0){ 
          strcat(string, risorsa);
          strcat(string,"\n");
        }
       
         
    }
    return strdup(string); //modo per tornare una copia esatta di una stringa;
    

     
}


void prenota_risorsa(char* ip, int port, char* nrisorsa)
{
    FILE *fp_tmp, *fp;
    char buffer[BUFF_SIZE];
    char string[BUFF_SIZE];
    char *risorsa , *quantita, *resto;
    int id = take_id();

    if((fp = fopen("risorsa.txt", "a+")) < 0)
     handle_error("Error fopen()");
    if((fp_tmp = fopen("risorse.txt", "w+")) < 0)
     handle_error("Error fopen()");
    while(fprintf(fp, "%s\n", buffer) == 1){

        if(strncmp(buffer, risorsa,strlen(risorsa)) != 0)
            fprintf(fp_tmp, "%s", buffer);

        else{ 

            risorsa = strtok(string, ":");
            quantita = strtok(NULL, ":");
            resto = strtok(NULL,"\n");
            if(resto == NULL) 
                    fprintf(fp_tmp,"%s%c%d%c%d%c",risorsa,":",atoi(quantita)-1,":",id,":");
            else{ 
                fprintf(fp_tmp,"%s%c%d%c%s%c%d%c",risorsa,":",atoi(quantita)-1,":",resto,':',id,":");
                }
        }
        
    }
    fclose(fp);
    fclose(fp_tmp);
    remove("risorsa.txt");
    rename("risorse.txt", "risorsa.txt");

}


int take_id(char* ip , int port){

    FILE *fp;
    char buffer[BUFF_SIZE];
    char string[BUFF_SIZE];
    char *risorsa , *quantita, *resto;

    while(fscanf(fp,"%s\n"));
}









int main(int argc , char** argv)
{
    int n , sockfd;
    char* risorsa;
    struct sockaddr_in server_addr , client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[BUFF_SIZE];

    if(argc <2)
     handle_error("Error argc");

    if((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
     handle_error("Error socket()");

    memset(&server_addr , 0 , len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));

    if((bind(sockfd, (struct sockaddr*)&server_addr, len)) < 0)
     handle_error("Error bind");



    for(;;){
         
        n = recvfrom(sockfd, buffer, BUFF_SIZE , 0 , (struct sockaddr*)&client_addr , &len);
        buffer[n] = '\0';

        if(strncmp(buffer, "REG" , 3) == 0)
         REG(inet_ntoa(client_addr.sin_addr) , ntohs(client_addr.sin_port));

        if(strncmp(buffer,"RISORSA", 7) == 0){
         risorsa =elenco_risorse();
         sendto(sockfd, risorsa ,999 , 0 , (struct sockaddr*)&client_addr, len);
        }
        if(strncmp(buffer,"PRENOTAZIONE", 12) == 0){
            prenota_risorsa(inet_ntoa(client_addr.sin_addr) , ntohs(client_addr.sin_port));
        }


    }
    close(sockfd);
    return 0;
}