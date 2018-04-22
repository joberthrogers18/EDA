#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mediamatriz(int **, int, int);

int main (int argc, char *argv[])
{
    FILE *fp;
    int numero,linha = 0, col = 0;          // declaração de caracteres
    char pegar_p , palavra , p_virg = ';';
    int i,j, **mat, cont = 0, *media;

    /*if (argc!=2) {
        printf("Você esqueceu de importar o arquivo.\n");      // mensagem caso o arquivo não seja indicado
        exit(1);
    }*/

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

    media = (int*)malloc(((col - 1 )*(linha - 1))*sizeof(int));

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

    cont = 0;

    for(i = 1; i<linha - 1; i++){
      for(j = 1; j<col - 1; j++){     //verificar toda a posição da matriz com seus vizinhos
          mediamatriz(mat, i, j);
          cont++;
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

      free(media);

    printf("numero de linhas: %d\n", linha );
    printf("numero de colunas: %d\n", col );

    fclose(fp);
    return 0;
}

void mediamatriz(int **M, int L, int C){
  int i, j, contl = 0, contc = 0;
  char bin_c[9], bin[3][3], bit_2;

  float soma = 0.0;

    for(i = L - 1; i<L + 2; i++){
      for(j = C - 1; j<C + 2; j++){
        soma += *(*(M+i)+j);
      }
  }

  soma = soma / 9.0;

  printf("%f\n", soma);

    printf("\n");

    for(i = L - 1; i<L + 2; i++){
          for(j = C - 1; j<C + 2; j++){
            if(soma >= *(*(M+i)+j)){
              bin[contl][contc] = '1';
              contc++;
            }
            else{
              bin[contl][contc] = '0';
              contc++;
            }
          }
      }

    bin_c[0] = bin[0][0];
    bin_c[1] = bin[0][1];
    bin_c[2] = bin[0][2];
    bin_c[3] = bin[1][2];
    bin_c[4] = bin[2][2];
    bin_c[5] = bin[2][1];
    bin_c[6] = bin[2][0];
    bin_c[7] = bin[1][0];
    bin_c[8] = bin[1][1];

    for(i = 0; i< 9; i++){
          printf("%c ", bin_c[i]);
    }

    printf("\n");

    bit_2 = 'a';
    int zre = 0;

    for (i = 0; i < 9; i++) {
      bit_2 = bin_c[zre];
      for (j = 0; j < 9; j++) {
        bin_c[j] = bin_c[j+1];
      }
      bin_c[8] = bit_2;

      for(int l= 0; l< 9; l++){
            printf("%c ", bin_c[l]);
      }

      printf("\n");
    }


}
