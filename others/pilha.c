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

int push (Ppilha p, int val){ // acrescenta valor na pilha
  if(p == NULL)
    return -1; //pilha não inicializada
  if(p->topo >= MAX_PILHA-1)
    return -1;  // no caso se a pilha estiver cheia

  (p->topo)++; //somando o ponteiro do topo mais um para acrescentar
  p->valor[p->topo] = val; //o valor daquela posição eh atribuido
  return 1;

}

int pop(Ppilha p){ // recebe a pilha e o valor que será armazenado o resultado
  int aux = 0;
  if(p==NULL)
    return -1;
  if(p->topo < 0)
    return -1;  //pilha vazia
  aux = p->valor[p->topo];
  p->topo--;
  return aux;
}

int peek(Ppilha p){  // apenas retorna o topo da pilha
  return p->valor[p->topo];
}

void libera(Ppilha p){
  int i;
  free(p); // libera o ponteiro
}

void imprime(Ppilha p){
  int i;
  if(p == NULL){
    printf("Pilha Vazia\n");
    return;
  }
  printf("Numero de elementos na pilha: %d\n",p->topo+1);

  for(i = p->topo; i >= 0; i--){
    printf("pilha[%d] = %d\n",i,p->valor[i]);     // libera todos os valores da pilha
  }
}

int main(){
  Ppilha p;
  int res;

  p = criar_pilha();
  push(p, 1);
  imprime(p);
  push(p, 2);
  imprime(p);
  push(p, 3);
  imprime(p);
  push(p, 4);
  imprime(p);
  push(p, 5);
  imprime(p);
  res = pop(p);
  imprime(p);
  libera(p);

  return 0;
}
