#include <stdio.h>
#include <stdlib.h>



int main(){
    int codice;
    printf("Inserire codice: ");
    scanf("%d", &codice);

    FILE *file_handle = fopen("codice.txt" ,"r");

    if(file_handle == NULL){
        printf("\nErrore di apertura dei file.");
        exit(1);
    }else{
        printf("\nFile aperto con successo");
    }
     

    fprintf(file_handle, "%d", codice);
    printf("\nCodice [%d] scritto in codice.txt", codice);

    fclose(file_handle);
    printf("\nFile chiuso.");
    return 0;
}