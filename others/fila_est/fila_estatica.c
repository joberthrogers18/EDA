#include <stdio.h>
#include <stdlib.h>
#include "fila_estatica.h"

struct fila {
  int inicio, fim, qtd;
  struct aluno dados[MAX];
};

Fila* cria_Fila(){
    Fila *fi = (Fila*)malloc(sizeof(struct fila)); // aloco uma struct fila no ponteiro fila
    if(fi != NULL){ // caso o fi for diferente de null o inicio, fim e struct daquela struct alocada recebem 0
      fi->inicio = 0;
      fi->fim = 0;
      fi->qtd = 0;
    }
    return fi;
}

void liberar_Fila(Fila* fi){ //destruir a fila
  free(fi);
}

int tamanho_Fila(Fila* fi){
  if(fi == NULL){
    return -1;  //  verifica se a fila eh nula
  }
  return fi->qtd;   //caso contrario retorna a quantidade
}

int Fila_cheia(Fila* fi){
  if(fi == NULL)return -1;  // se a fila for igual a nula retorna nulo
  if(fi->qtd == MAX)    // se a quantidade for igual a maxima retorna 1
    return 1;
  else      // caso contrario retorne 0
    return 0;
}

int Fila_vazia(Fila* fi){
  if(fi == NULL) return -1;
  if(fi->qtd == 0)        // se a quantidade for 0 é pq esta vazia e então retorne 1
    return 1;
  else
    return 0;
}

int insere_Fila(Fila* fi, struct aluno al){
  if(fi == NULL) return 0;
  if(Fila_cheia(fi))return 0;
  fi->dados[fi->fim] = al;
  fi->fim = (fi->fim + 1)%MAX;
  fi->qtd++;
  return 1;
}

int remove_Fila(Fila* fi){
  if(fi == NULL || Fila_vazia(fi))
    return 0;
  fi->inicio = (fi->inicio + 1)%MAX;
  fi->qtd--;
  return 1; 
}
