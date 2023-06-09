#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv[])
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    FILE *f;
    if(f= fopen("binary.dad", " wb")== NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(0);
    }
    fwrite(a, sizeof(int), 10 , f );
fclose(f);
return 0;

}
