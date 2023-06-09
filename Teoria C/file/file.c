#include <stdio.h>



/*
Si scriva su un file di testotesto.txtquello
che l’utente inserisce datastiera parola per parola, 
finché non inserisce la parola"FINE"(usando lafprintf).

*/

int main()
{
  FILE *file;
  file=fopen("testo.txt", "w");
  if(file==NULL)
  {
    printf("Errore nell'apertura del file.");
    return 1;

  }

  char parola[100];
  while(1)
  {
    printf("Inserisci una parola:");
    scanf("%s", parola);
    if(strcmp(parola,"FINE")==0)
    {
      break;
    }
    fprintf(file, "%s", parola);

  }
  fclose(file);
  return 0;
}