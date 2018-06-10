#include <stdio.h>
#include <stdlib.h>

struct NO{
  int info;
  struct NO* esq;
  struct NO* dir;
};

typedef struct NO* ArvBin; //é um ponteiro que aponta para minha struct nó

ArvBin* cria_ArvBin(); // criação de uma arvore binaria null
void libera_ArvBin(ArvBin* raiz);
void libera_NO(struct NO* no);
int estaVazia_ArvBin(ArvBin* raiz);
int altura_ArvBin(ArvBin* raiz);
int totalNO_ArvBin(ArvBin* raiz);
void preOrdem_ArvBin(ArvBin* raiz);
void preOrdem_ArvBin(ArvBin* raiz);

int main(int argc, char const *argv){
  ArvBin* raiz = cria_ArvBin();; // criando a raiz da arvore

  libera_ArvBin(raiz);

  return 0;
}

ArvBin* cria_ArvBin()
{
  ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
  if(raiz != NULL){ // se deu certo a alocação o ponteiro para raiz recebe null
    *raiz = NULL;
  }
  return raiz;
}

void libera_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL)   // se não tem nada alocado
    return;
  libera_NO(*raiz);
  free(raiz); // libera raiz
}

void libera_NO(struct NO* no)
{
  if(no == NULL)
    return;
  libera_NO(no->esq);  // corre recursivamente o nó da esquerda
  libera_NO(no->dir);  // corre recursivamente o nó da esquerda
  free(no);
  no = NULL;

}

int estaVazia_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL) //se o no for igual a null ele retorna 1
    return 1;
  if(*raiz == NULL) // se o conteudo da raiz for null ele retorna senão retorna 0
    return 1;
  return 0;

}

int altura_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL) // verifica se a alocação foi feita
    return 0;
  if(*raiz == NULL) // verifica se o conteudo eh nulo
    return 0;

  int alt_esquerda = altura_ArvBin(&((*raiz)->esq)); // recursivamente pelo nó esquerdo
  int alt_direita = altura_ArvBin(&((*raiz)->esq)); // recursivamente pelo nó direito

  if(alt_esquerda > alt_direita)    // ver qual o maior nó retorna o tamanho do maior +1
    return (alt_esquerda + 1);
  else
    return (alt_direita + 1);
}

int totalNO_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL) // verfica se alocção foi feita
    return 0;
  if(*raiz == NULL) // verifica o conteúdo e retorna zero se null
    return 0;

  int no_esq = totalNO_ArvBin(&((*raiz)->esq));
  int no_dir = totalNO_ArvBin(&((*raiz)->dir));
  return (no_esq + no_dir + 1);

}
void emOrdem_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    emOrdem_ArvBin(&((*raiz)->esq));
    printf("%d\n", (*raiz)->info);
    emOrdem_ArvBin(&((*raiz)->dir));
  }
}
