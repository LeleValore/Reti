#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *fp = fopen("macherine.txt", "a");

    if(fp == NULL){
        printf("\nErrore nell'apertura del file..");
        exit(1);
    }else{
        printf("File aperto con successo...\n");
    }


    while(1){
        char name[30];
        int mask_count=0;

        printf("- Nome: ");
        scanf("%s", name);

        printf("- Mascherina: ");
        scanf("%d", &mask_count); //se metti masck_count anziche &masck_count ti da warning inerente alla tipologia di dato int* e int

        if(mask_count == 0){
            break;
        }
        fprintf(fp, "Nome=[%s], Numero=[%d]\n", name, mask_count);
        printf("%s prende %d mascherine.\n\n", name , mask_count);
        
    }
    fclose(fp);
    printf("Chiuso File\n");
    return 0;
}