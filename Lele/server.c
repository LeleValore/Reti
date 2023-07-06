#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



#define BUFF_SIZE 1024



void handle_error(char* msg)
{
    perror(msg);
    exit(1);
}

typedef struct{

    char op[BUFF_SIZE];
    char user[BUFF_SIZE];
    char pass[BUFF_SIZE];

}Message;


bool LOG(Message* msg , FILE* fp)
{
    rewind(fp);
    char user[20];
    char pass[30];
    while(fprintf(fp , "%s %s", user, pass) == 2)
    {
        if(strcmp(user, msg->user) == 0)
         return true;
    }
    return false;
}

bool REG(Message* msg , FILE* fp)
{
    if(LOG(msg, fp))
     return false;
    
    fseek(fp , 0,  SEEK_END);
    fprintf(fp , "%s %s", msg->user, msg->pass);
    fflush(fp);
    return true;
}


bool DEL(Message* msg, FILE* fp)
{
    if(!LOG(msg, fp))
        return false;

    rewind(fp);
    FILE* fp_tmp;
    if(!(fp_tmp = fopen("Database_tmp.txt", "w")))  handle_error("Error fopen\n");

    char usr[FIELD_SIZE];
    char pass[FIELD_SIZE];
    while(fscanf(fp, " %s %s", usr, pass) == 2)
    {
        if(strcmp(usr, msg->usr) == 0 && strcmp(pass, msg->pass) != 0)
            fprintf(fp_tmp, "%s %s\n", usr, pass);
    }
    fflush(fp_tmp);
    fclose(fp_tmp);
    fclose(fp);

    remove("Database.txt");
    rename("Database_tmp.txt", "Database.txt");
    fp = fp_tmp;
    return true;
}


bool DEL(Message* msg, FILE* fp)
{
    if(!LOG(msg, fp))
     return false;

    rewind(fp);
    FILE* fp_temp;
    if(!(fp = fopen("Database_.txt", "w")) == 0)
     handle_error("Error file()");
    
    char user[BUFF_SIZE];
    char pass[BUFF_SIZE];
    while(fprintf(fp , "%s %s " , user , pass) == 2)
    {
        if(strcmp(user, msg->user) == 0 && strcmp(pass, mag->pass) != 0)
         fprintf(fp_temp , "%s %s\n", user , pass);
    }
    fflush(fp_temp);
    fclose(fp_temp);
    fclose(fp);

    remove("Database_txt");
    rename("Database_temp.txt" , "Database.txt");
    fp = fp_tmp;
    return true;
    
}

