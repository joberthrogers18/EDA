#ifndef filaET
#define filaET

#define MAX 100  //tamanho maximo da fila
struct aluno{
  int matricula;
  char nome[100];       //struct para aluno
  float n1, n2, n3;
};
  typedef struct fila Fila; // definindo struct fila

Fila* cria_Fila(); // função para criar uma fila nula

void liberar_Fila(Fila* fi); // destruir a fila

#endif
