#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
    FILE *f;
    if((f = fopen("binary.dad", "rb"))== 0)
    {
        printf("Errore apertura file\n");
        exit(1);
    }
    int a[10];
    int n = fread(a,sizeof(int), 10, f);
    for(int i =0; i<n; i++)
       printf("a[%d]= %d\n", i, a[i]);
    fclose(f);
    return 0;
}


