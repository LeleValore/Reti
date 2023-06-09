#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *fp;
    char msg[80], n;
    fp= fopen("test.txt", "rb");
    if(fp==NULL)
      exit(1);
     n = fread(msg,1,80,fp);
     printf("%s", msg);
     fclose(fp); 
}