//autores: 
// Joberth Rogers Tavares Costa - 16/0128013
// Elias Bernardo Marques Magalhães - 15/0009011

#include<stdio.h>
#include<stdlib.h>

#define TAMANHO 10

void fneuronio(float *entradas, float *pesos, int tamanho_vetor, float limiar, int *agitacao);

int main(){

  float entradas[TAMANHO];
  float pesos[TAMANHO];
  float limiar_T;
  int contador = 0;
  int nivel_agitacao = 0;     // o neurônio já começa inibido
  int *Pnivel_agitacao = &nivel_agitacao;

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

  fneuronio(entradas, pesos, TAMANHO, limiar_T, Pnivel_agitacao);

  if(nivel_agitacao == 1)
    printf("“Neurônio ativado!”\n");
  else
    printf("“Neurônio inibido!”\n");

  return 0;
}

void fneuronio (float *entradas, float *pesos, int tamanho_vetor, float limiar, int *agitacao){

  int contador = 0;
  float SOMAP = 0.0;

  for(contador = 0; contador < tamanho_vetor; contador++){
    SOMAP += *(entradas + contador) * *(pesos + contador);
  }

  if(SOMAP > limiar){
    *agitacao = 1;
  }


}
