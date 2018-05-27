#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_estatica.h"

int main(int argc, char const *argv[]) {
  Fila *fi;

  struct aluno *dados;
  dados = (struct aluno*)malloc(sizeof(struct aluno));
  dados->matricula = 123;
  dados->n1 = 10;
  dados->n2 = 8;
  dados->n3 = 9;

  struct aluno *dados2;
  dados2 = (struct aluno*)malloc(sizeof(struct aluno));
  dados2->matricula = 133;
  dados2->n1 = 1;
  dados2->n2 = 2;
  dados2->n3 = 3;

  fi = cria_Fila();

  liberar_Fila(fi);

  int x = tamanho_Fila(fi);

  int y = Fila_vazia(fi);

  int insere1 = insere_Fila( fi, *dados);

  insere_Fila(fi, *dados2);

  remove_Fila(fi);

  printf( fi->matricula );

  return 0;
}
