#include <stdio.h>
#include <stdlib.h>

void Menu();
void cadastra(FILE *arquivo);

int main(int argc, char const *argv[]) {

  FILE *arquivo;
  int escolha;

  arquivo = fopen("materias.txt", "a+"); // abrir aquivo para leitura e gravaçãonce

  if (arquivo==NULL) {
    printf("Arquivo não encontrado.\n");    //verificando se o arquivo existe
    exit(1);
  }

  while (1) {
    Menu();
    scanf("%d", &escolha);
    switch (escolha) {
      case 1:
        cadastra(arquivo);
        continue;
      break;
      case 7:
        fclose(arquivo);
        return 0;
      break;
      default:
        printf("Comando errado digite novamente!!!\n\n");
    }
  }

}

void Menu(){
  printf("1) Cadastrar uma disciplina\n");
  printf("2) Cadastrar um turma\n");
  printf("3) Excluir disciplina\n");;
  printf("4) Excluir turma\n");
  printf("5) Gerar relatório por disciplina\n");
  printf("6) Gerar relatório geral\n");
  printf("7) Sair do programa\n");
}

void cadastra(FILE *arquivo){
  int numero, numero2, numero3;

  printf("Digite um numero:");
  scanf("%d", &numero);
  printf("Digite um numero");
  scanf("%d", &numero2);
  printf("Digite um numero:");
  scanf("%d", &numero3);
  fprintf(arquivo, "%d ", numero);
  fprintf(arquivo, "%d ", numero2);
  fprintf(arquivo, "%d\n", numero3);
}
