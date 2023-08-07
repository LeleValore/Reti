#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 1024

char** create_matrix(){

    char** matrix = (char**)malloc(3* sizeof(char*));
    for(int i = 0;i < 3 ; i++){
        matrix[i]= (char*)malloc(3*sizeof(char));
        for(int j = 0 ; j < 3 ; j++){
            matrix[i][j] = '-';
        }
    }
    return matrix;
}

void printMatrix(char** matrix)
{
    for(int i = 0;i < 3 ; i++){
      
        for(int j = 0 ; j < 3 ; j++){
            
            printf("%s    ", matrix);
        }
    }
    printf("%s\n"); 
}

typedef struct{
    char ip[20];
    int porta;
}Giocatore;












int main(int argc, char** argv)
{

}