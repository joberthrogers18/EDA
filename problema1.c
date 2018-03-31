#include<stdio.h>
#include<stdlib.h>

#define TAMANHO 10

int main(){

  float entradas[TAMANHO];
  float peso[TAMANHO];
  float limiar_T;
  int contador = 0;

  for(contador = 0; contador < TAMANHO; contador++){
    printf("Entre com o valor do %dº entrada: ", contador );
    scanf("%d", &entrada[contador]);
  }

  printf("\n");

  for(contador = 0; contador < TAMANHO; contador++){
    printf("Entre com o valor do %dº peso: ", contador );
    scanf("%d", &peso[contador]);
  }

  printf("Digite o valor do limiar T desejado: ");
  scanf("%d\n", &limiar_T);


  return 0;
}
