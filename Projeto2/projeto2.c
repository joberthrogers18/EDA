#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int numero,linha = 0, col = 0;          // declaração de caracteres
    char pegar_p , palavra , p_virg = ';';
    int i,j, **mat;

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

    col++;

    mat = (int**)malloc(linha*sizeof(int *));

    for(i = 0; i<linha; i++)                         //declaração da matriz
      *(mat+i) = (int*)malloc(col*sizeof(int));

    rewind(fp); //voltando o ponteiro do arquivo para o ínicio


    for (i=0;i<linha;i++){
        for (j=0;j<col;j++){

           if (!feof(fp)){
              // to do: implementar o contador e verificar como ler o número sem ponto e virgula
                fscanf(fp, "%d%c", *(mat+i)+j, &pegar_p);
          }
      }
    }

    for (i=0;i<linha;i++){
      for (j=0;j<col;j++){
          printf("%d ",*(*(mat+i)+j));    // imprime a matriz
          }
          printf("\n");
        }

      for (i=0;i<linha;i++)       //libera as linhas da matriz
        free(*(mat+i));

      free(mat);    // libera o vetor de ponteiros



    printf("numero de linhas: %d\n", linha );
    printf("numero de colunas: %d\n", col );

    fclose(fp);
    return 0;
}
