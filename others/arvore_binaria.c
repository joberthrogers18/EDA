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
void emOrdem_ArvBin(ArvBin* raiz);
void posOrdem_ArvBin(ArvBin* raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin* raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int consulta_ArvBin(ArvBin *raiz, int valor);

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

void posOrdem_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    emOrdem_ArvBin(&((*raiz)->esq));
    emOrdem_ArvBin(&((*raiz)->dir));
    printf("%d\n", (*raiz)->info);
  }
}

int insere_ArvBin(ArvBin* raiz, int valor)
{
  if(raiz == NULL)
    return 0;
  struct NO* novo;
  novo = (struct NO*)malloc(sizeof(struct NO));
  if(novo = NULL)
    return 0;
  novo->info = valor;
  novo->dir = NULL;
  novo->esq = NULL;

  if(*raiz == NULL)
  {
    *raiz = novo;
  }
  else
  {
    struct NO* atual =  *raiz;
    struct NO* ant =  NULL;

    while(atual != NULL){     // navega pela arvoreaté chegar numa folha
        ant = atual;

        if(valor == atual->info)
        {
          free(novo);
          return 0; // elemento já existe
        }
        if(valor > atual->info)
          atual = atual->dir;
        else
          atual = atual->esq;
    }

    if(valor > atual->info)   // insere como filho desse nó  folha
      atual->dir = novo;
    else
      atual->esq = novo;
  }

  return 1;
}

int remove_ArvBin(ArvBin* raiz,int valor)
{
  /*
    FUNÇÃO RESPONSAVEL PELA BUSCA
    DO NÓ A SER REMOVIDo
  */

  if(raiz == NULL) return 0;
  struct NO* atual =  *raiz;
  struct NO* ant =  NULL;
  while(atual != NULL)
  {
    if(valor ==  atual->info){
      if(atual ==  *raiz)
        *raiz = remove_atual(atual);
      else{
        if(ant->dir == atual)
          ant->dir = remove_atual(atual);
        else
          ant->esq = remove_atual(atual);
      }
      return 1;
    }
    ant = atual;

    if(valor > atual->info)
      atual= atual->dir;
    else
      atual = atual->esq;
  }

}

struct NO* remove_atual(struct NO* atual)
{
  /*
    FUNÇÃO RESPONSAVEL POR TRATAR
    OS 3 TIPOS DE REMOÇÃO
  */

  struct NO *no1, *no2;
   if(atual->esq == NULL){    // sem filho da esquerda aponta para filha da direita(trata nó folha e nó com um filho)
     no2 = atual->dir;
     free(atual);
     return no2;
   }
   no1 = atual;
   no2 = atual->esq;
   while (no2->dir != NULL) {  //procura filho mais a direita na subarvore da esquerda
     no1 = no2;
     no2 = no2->dir;
   }

   if (no1 != atual){
     no1->dir = no2->esq;
     no2->esq = atual->esq;  //procura filho mais a direita na subarvore da esquerda para o lugar do nó removido
   }
   no2->dir = atual->dir;
   free(atual);
   return no2;

}

int consulta_ArvBin(ArvBin *raiz, int valor){
  if (raiz==NULL) return 0;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual->info){
      return 1;
      //aqui outras coisas podem ser feitas.
    }
    if(valor > atual->num)
      atual = atual->direito;
    else
      atual = atual->esquerdo;
  }
  return 0;
}
