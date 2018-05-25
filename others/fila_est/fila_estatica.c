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
    return -1;
  }
  return fi->qtd;
}

int Fila_cheia(Fila* fi){
  if(fi == NULL)return -1;
  if(fi->qtd == MAX)
    return 1;
  else
    return 0;
}
