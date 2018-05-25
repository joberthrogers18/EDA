#include <stdio.h>
#include "fila_estatica.h"

int main(int argc, char const *argv[]) {
  Fila *fi;

  fi = cria_Fila();

  liberar_Fila(fi);

  return 0;
}
