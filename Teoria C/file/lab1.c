#include <stdio.h>

int main(int argc, char **argv)
{
    
    int a =10;
    int b=5;
    int c= 'c';

    // per la stampa dobbiamo inserire ("%d", a);
    //poiu sono le variabili piu devo mettere la %d
    /*
     alxune funzioni che possono servire:

     strcpy copia stringa 2 su stringa 1 

     strncpy copia i primi n caratteri di stringa 2 in stringa1:

     strcat concatena due stinghe 






     -STRUCT
     gli elementi della struttura sono detti membri ; essi sono identificati da un nome,nomemembro e da un tipo, tipoMembro.

     Una volta definit una struttura, nomeStruttura diviene un nuovo tipo a tutti gli effetti 

    
    
    

    
                    printf("%d",a);
                    prinf("c=%c",c);
                    int v[4]; // per dichiarare un array stessa sintassi del c++

      
    */

}



/*





-Strutture e puntatori

struct data
{
    int giorno;
    chat *mese;
    int anno;
};

int main( int argc, int **argv)
{
    struct data *pd, oggi;
    pd = &oggi;
    (*pd).giorno=31;
    (*pd).mese = "Gennaio";
    (*pd).anno = 2023;
    ...
    return 0;
}

--FILE 
per poter mantenere disponibili i datitra le diverse esecuzioni di un programma (persistenza dei dati) é necessario poterli archiviare nella memoria 

°File é una struttura definita nello header stardaard stdio.h

per aprire un file si usa la funzione:
FILE* fopen(char fname[], char modo[])
questa funzione apre il file di nome fname nel modo specificato e restituisce un puntatore a file 
(che punta a una nuova struttura FILE appositamente creata).

NB: il nome del file (in particolare il path) é indicato in m,aniera diversa 


modo specifica come aprire il file:
r apertura in lettura(read) Se il file non esiste -> fallimento
w apertura di un file vuoto in scrittura(write). Se il file 




--CHIUSRA FILE IN C 

int fclose(FILE*)


FUNZIONI CHE POSSONO ESSERE UTILI

funzione feof()

durante la fase di accesso ad un file é possibile verificare la presenza del fine file con la funzione di libreria:

--ESEMPIO COMPLETO FILE

#define DIM 30
#include <stdio.h>
#include <stdlib.h>

struct persona 
{
    char cognome[31], nome[31], sesso[2];
    int anno;

};

int main()
{
    struct persona v[DIM]; 
    int k=0; 
    FILE* f;
    if((f=fopen("people.txt", "r"))==NULL)
    {
        printf("Il file non esiste!");
        exit(1);

    }
    while(fscanf(f,%s%s%s%d, v[k].cognome, v[k].nome, v[k].sesso, &v[k].anno) !=EOF)

     k++;
   
     fclose(f);
}





*/
