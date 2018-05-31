#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct voo{
      char codigo[7] ;
      char tipo;//A ou D;
      int comb;
      struct voo* prox ;
      };
typedef struct voo Voo;

int num_voo()
{
  int voo;
  voo = 20 + (rand()%44);

  return voo;
}

int num_prioridade()
{
  int prioridade;
  prioridade = (rand()%12);

  return prioridade;
}

int main(void)
{
    int voo, prioridade;
    srand(time(NULL));

    voo = num_voo();


    for (int i = 0; i < 64; i++) {
      printf("%s ", cod_voo[i]);

    }



     return 0;
}
