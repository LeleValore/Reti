#include <stdio.h>
#include <stdlib.h>



int main(){
    int codice;
    printf("Inserire codice: ");
    scanf("%d", &codice);

    FILE *file_handle = fopen("codice.txt" ,"a");

    if(file_handle == NULL){
        printf("Errore di apertura dei file.");
        exit(1);
    }

    fprintf(file_handle, "%d", codice);
    printf("Codice [%d] scritto in codice.txt", codice);

    fclose(file_handle);
    printf("\nFile chiuso.");
    return 0;
}