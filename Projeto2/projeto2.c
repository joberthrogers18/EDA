#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int mediamatriz(int **, int, int);
float trans_bin_dec(char *bin);
void glcm(int **, int, int, int, int, float *, int);
void normalizacao(float *);

int main (int argc, char *argv[])
{
    FILE *fp;
    int numero,linha = 0, col = 0;          // declaração de caracteres
    char pegar_p , palavra , p_virg = ';';
    int i,j, **mat, cont = 0, *media, menor = 0;
    float *freq;

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


    freq = (float*)calloc(536,sizeof(float));

    for (i = 0; i < 536; i++) {
      printf("%f", freq[i]);
    }

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
          menor = mediamatriz(mat, i, j);
          menor = menor - 1;
          printf("menor fora: %d\n",menor );
          *(freq + menor) += 1;
          cont++;
        }
      }

      for (i = 0; i < 536; i++) {
        printf("%.1f;", freq[i]);
      }

    for (i=0;i<linha;i++){
      for (j=0;j<col;j++){
          printf("%d ",*(*(mat+i)+j));    // imprime a matriz
          }
          printf("\n");
        }

    glcm(mat , linha, col, 0, -1, freq, 512); // esquerda
    printf("\n");
    glcm(mat, linha, col, 0, +1, freq, 515); // direita
    printf("\n");
    glcm(mat , linha, col, -1, 0, freq, 518); // cima
    printf("\n");
    glcm(mat , linha, col, +1, 0, freq, 521); // baixo
    printf("\n");
    glcm(mat , linha, col, -1, -1, freq, 524); // diagonal superior esquerda
    printf("\n");
    glcm(mat , linha, col, -1, +1, freq, 527); // diagonal superior direita
    printf("\n");
    glcm(mat , linha, col, +1, +1, freq, 530); // diagonal inferior direita
    printf("\n");
    glcm(mat , linha, col, +1, -1, freq, 533); // diagonal inferior esquerda
    printf("\n");

    for (i = 0; i < 536; i++) {
      printf("%.1f;", freq[i]);
    }

    normalizacao(freq);

    for (i = 0; i < 536; i++) {
      printf("%.1f;", freq[i]);
    }

      for (i=0;i<linha;i++)       //libera as linhas da matriz
        free(*(mat+i));

      free(mat);    // libera o vetor de ponteiros

      free(media);

      free(freq);

    printf("numero de linhas: %d\n", linha );
    printf("numero de colunas: %d\n", col );

    fclose(fp);
    return 0;
}

int mediamatriz(int **M, int L, int C){
  int i, j, contl = 0, contc = 0, menor = 999999999, num;
  char bin_c[9], bin[3][3], bit_2;

  float soma = 0.0;

    for(i = L - 1; i<L + 2; i++){
      for(j = C - 1; j<C + 2; j++){
        soma += *(*(M+i)+j);
      }
  }

  soma = soma / 9.0;

    printf("\n");

    for(i = L - 1; i<L + 2; i++){
          for(j = C - 1; j<C + 2; j++){
            if(soma < *(*(M+i)+j)){
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

    num =  trans_bin_dec(bin_c);

    if(num < menor){
      menor = num;
    }

    printf("\n");

    bit_2 = 'a';

    for (i = 0; i < 9; i++) {

      bit_2 = bin_c[0];
      for (j = 0; j < 9; j++) {
        bin_c[j] = bin_c[j+1];
      }
      bin_c[8] = bit_2;

      num =  trans_bin_dec(bin_c);

      if(num < menor){
        menor = num;
      }

      printf("\n");
    }

    printf("%d\n", menor);

    return menor;

}

float trans_bin_dec(char *bin){
  int i, j;
  float dec;

  for ( i = 0; i < 9; i++) {
    if(*(bin + i) == '1'){
      dec += pow(2,8 - i);
    }
  }

  return dec;
}


void glcm(int **img , int L, int C, int pos_lin, int pos_col, float *freq, int pos_freq){
  int **glcm, i, j, lin_glcm, col_glcm;
  float energia = 0.0, contraste = 0.0, homogeneidade = 0.0;

  glcm = (int**)calloc(256,sizeof(int *));

  for(i = 0; i<256; i++)                         //declaração da matriz
    *(glcm+i) = (int*)calloc(256,sizeof(int));


    for(i = 1; i<L - 1; i++){
      for(j = 1; j<C - 1; j++){     //verificar toda a posição da matriz com seus vizinhos
          lin_glcm = img[i][j];
          col_glcm = img[i + pos_lin][j + pos_col]; // posição linha e posição coluna define para qual direção o glcm irá indicar cima/baixo/direita/esquerda..
          *(*(glcm+lin_glcm)+col_glcm) += 1;

        }
      }

      for (i = 0; i < 256; i++){
          for (j = 0; j < 256; j++){
          if(*(*(glcm + i)+ j) >= 1){
            contraste += (*(*(glcm + i)+ j)) * pow(i - j, 2);    //imprimir onde esta colocando na matriz
            energia += pow((*(*(glcm + i)+ j)), 2);
            homogeneidade += (*(*(glcm + i)+ j))/(pow(i - j, 2) + 1);
          }
        }
      }

    energia = sqrt(energia);

    *(freq + pos_freq) = contraste;
    *(freq + (pos_freq + 1)) = energia;
    *(freq + (pos_freq + 2)) = homogeneidade;

    printf("Cont: %f ener: %f homo: %f \n", contraste, energia, homogeneidade);

   for (i=0;i<256;i++)       //libera as linhas da matriz
      free(*(glcm+i));

    free(glcm);    // libera o vetor de ponteiros


}

void normalizacao(float *freq){
  int i = 0;
  float menor = 999999999, maior = 0;

  for(i = 0; i < 536; i++){
    if(*(freq + i) > maior){
        maior = *(freq + i);
    }

    if(*(freq + i) < menor){
      menor = *(freq + i);
    }
  }

  for(i = 0; i < 536; i++){
    *(freq + i) = (*(freq + i) - menor) / (maior - menor);
  }

}
