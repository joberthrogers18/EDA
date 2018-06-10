#include <stdio.h>
#include <stdlib.h>

struct NO{
  int info;
  struct NO* esq;
  struct No* dir;
};

typedef struct NO* ArvBin; //é um ponteiro que aponta para minha struct nó

ArvBin* cria_ArvBin(); // criação de uma arvore binaria null


int main(int argc, char const *argv){
  ArvBin* raiz; // criando a raiz da arvore


  return 0;
}

ArvBin* cria_ArvBin(){
  ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
  if(raiz != NULL){ // se deu certo a alocação o ponteiro para raiz recebe null
    *raiz = NULL;
  }
  return raiz;
}
