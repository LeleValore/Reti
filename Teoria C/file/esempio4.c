#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    FILE *fp;
    char msg[]= " Ah, l'esame\nsi avvicina!";
    fp = fopen("testo.txt", "wb");
    if(fp == NULL)
      exit(1);
    fwrite(msg, strlen(msg)+1,1,fp);
    fclose(fp);  

}