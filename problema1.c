#include<stdio.h>
#include<stdlib.h>

#define TAMANHO 10

int nivel_agitacao = 0;     // o neurônio já começa inibido

void fneuronio(float *entradas, float *pesos, int tamanho_vetor, float limiar);

int main(){

  float entradas[TAMANHO];
  float pesos[TAMANHO];
  float limiar_T;
  int contador = 0;

  for(contador = 0; contador < TAMANHO; contador++){
    printf("Entre com o valor do %dº entrada: ", (contador + 1) );
    scanf("%f", &entradas[contador]);
  }

  printf("\n");

  for(contador = 0; contador < TAMANHO; contador++){
    printf("Entre com o valor do %dº peso: ", (contador + 1));
    scanf("%f", &pesos[contador]);
  }

  printf("\n");

  printf("Digite o valor do limiar T: ");
  scanf("%f", &limiar_T);

  printf("\n" );

  fneuronio(entradas, pesos, TAMANHO, limiar_T);

  return 0;
}

void fneuronio (float *entradas, float *pesos, int tamanho_vetor, float limiar){

  int contador = 0;
  float media_ponderada = 0.0;

  for(contador = 0; contador < tamanho_vetor; contador++){
    media_ponderada += *(entradas + contador) * *(pesos + contador);
  }

  printf("%f\n", media_ponderada );

}
