#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int numero;
    char comma;

    if (argc!=2) {
        printf("You forgot to enter the filename.\n");
        exit(1);
    }

    fp=fopen("test.txt", "r");

    if(fp==NULL) {
        printf("Cannot open file.\n");
        exit(2);
    }

    fscanf (fp, "%d%c", &numero, &comma);

    while (!feof(fp)) {
        // to do: implementar o contador e verificar como ler o número sem ponto e virgula
        if(){
          printf("%d\n", numero); /* print on screen */
          fscanf(fp, "%d%c", &numero, &comma);
        }
        printf("%d ", numero); /* print on screen */
        fscanf(fp, "%d%c", &numero, &comma);
    }

    fclose(fp);
    return 0;
}
