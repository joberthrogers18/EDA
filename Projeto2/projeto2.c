#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int numero,linha = 0, col = 0;          // declaração de caracteres
    char pegar_c , palavra , p_virg = ';';

    if (argc!=2) {
        printf("Você esqueceu de importar o arquivo.\n");      // mensagem caso o arquivo não seja indicado
        exit(1);
    }

    fp=fopen("test.txt", "r");          // abri o arquivo

    if(fp==NULL) {
        printf("Não foi possivel abri o arquivo.\n");        // caso o arquivo não exista
        exit(2);
    }

    while ((palavra=fgetc(fp))!=EOF) {
        // to do: implementar o contador e verificar como ler o número sem ponto e virgula

        if(palavra == '\n')
        {
          linha++;           // verficando quantas linhas no arquivo
        }
        else if(linha == 1 && palavra == p_virg){
          col++;         // verificando quantas colunas no arquivo
        }

    }


    printf("%d\n", linha );
    printf("%d\n", col );

    fclose(fp);
    return 0;
}
