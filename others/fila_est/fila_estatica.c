#include <stdio.h>
#include "fila_estatica.h"

struct fila {
  int inicio, fim, qtd;
  struct aluno dados[MAX];
};

Fila* cria_Fila(){
    Fila *fila = (Fila*)malloc(sizeof(struct(fila))); // aloco uma struct fila no ponteiro fila
    if(fi != NULL){ // caso o fi for diferente de null o inicio, fim e struct daquela struct alocada recebem 0
      fi->inicio = 0;
      fi->fim = 0;
      fi->qtd = 0;
    }
    return fi;
}
