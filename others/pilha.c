#include <stdio.h>
#include <stdlib.h>
#define MAX_PILHA 10


typedef struct {
  int valor[MAX_PILHA];
  int topo;
}Tpilha;

typedef Tpilha *Ppilha; //ponteiro para a pilha

Ppilha criar_pilha(){
    Ppilha p = (Ppilha) malloc (sizeof(Tpilha));
    p->topo = -1; //inicializando o topo com -1 para demontrar que esta vazia
    return p;
}

int push (Ppilha p, int val){
  if(p == NULL)
    return -1; //pilha não inicializada
  if(p->topo >= MAX_PILHA-1)
    return -1;  // no caso se a pilha estiver cheia

  (p->topo)++; //somando o ponteiro do topo mais um para acrescentar
  p->valor[p->topo] = val; //o valor daquela posição eh atribuido 
  return 1;


}

int main(){

}
