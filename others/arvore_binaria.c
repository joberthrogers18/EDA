#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define espaco 4
#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

typedef int ELEMENT;

typedef struct BSTNode_struct BSTNode;

struct BSTNode_struct {
    BSTNode *ptesq, *ptdir;

    //length of the edge from this no to its children
    int edge_length;

    int altura;

    ELEMENT element;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
};

struct NO{
  int info;
  struct NO* esq;
  struct NO* dir;
};

typedef struct NO* ArvBin; //é um ponteiro que aponta para minha struct nó

//adjust gap between left and right nos
int gap = 3;

//used for printing next no in the same level,
//this is the x coordinate of the next char printed
int print_next;

int MIN(int X, int Y) {
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y) {
    return ((X) > (Y)) ? (X) : (Y);
}

BSTNode *build_ascii_tree_recursive(struct NO *arvore) {
    BSTNode *no;

    if (arvore == NULL) return NULL;

    no = malloc(sizeof(BSTNode));
    no->ptesq = build_ascii_tree_recursive(arvore->esq);
    no->ptdir = build_ascii_tree_recursive(arvore->dir);

    if (no->ptesq != NULL) {
        no->ptesq->parent_dir = -1;
    }

    if (no->ptdir != NULL) {
        no->ptdir->parent_dir = 1;
    }

    sprintf(no->label, "%d", arvore->info);
    no->element = strlen(no->label);

    return no;
}


//Copy the tree into the ascii no structre
BSTNode *build_ascii_tree(struct NO *arvore) {
    BSTNode *no;
    if (arvore == NULL) return NULL;
    no = build_ascii_tree_recursive(arvore);
    no->parent_dir = 0;
    return no;
}

//Free all the nos of the given tree
void free_ascii_tree(BSTNode *no) {
    if (no == NULL) return;
    free_ascii_tree(no->ptesq);
    free_ascii_tree(no->ptdir);
    free(no);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(BSTNode *no, int x, int y) {
    int i, eh_esq;
    if (no == NULL) return;
    eh_esq = (no->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((no->element - eh_esq) / 2));
    if (no->ptesq != NULL) {
        for (i = 1; i <= no->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(no->ptesq, x - no->edge_length - 1, y + no->edge_length + 1);
    compute_lprofile(no->ptdir, x + no->edge_length + 1, y + no->edge_length + 1);
}

void compute_rprofile(BSTNode *no, int x, int y) {
    int i, n_eh_esq;
    if (no == NULL) return;
    n_eh_esq = (no->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((no->element - n_eh_esq) / 2));
    if (no->ptdir != NULL) {
        for (i = 1; i <= no->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(no->ptesq, x - no->edge_length - 1, y + no->edge_length + 1);
    compute_rprofile(no->ptdir, x + no->edge_length + 1, y + no->edge_length + 1);
}

//This function fills in the edge_length and
//altura fields of the specified tree
void filledge(BSTNode *no) {
    int h, hmin, i, delta;
    if (no == NULL) return;
    filledge(no->ptesq);
    filledge(no->ptdir);

    /* first fill in the edge_length of no */
    if (no->ptdir == NULL && no->ptesq == NULL) {
        no->edge_length = 0;
    }
    else {
        if (no->ptesq != NULL) {
            for (i = 0; i < no->ptesq->altura && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(no->ptesq, 0, 0);
            hmin = no->ptesq->altura;
        }
        else {
            hmin = 0;
        }
        if (no->ptdir != NULL) {
            for (i = 0; i < no->ptdir->altura && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(no->ptdir, 0, 0);
            hmin = MIN(no->ptdir->altura, hmin);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the no has two children of altura 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((no->ptesq != NULL && no->ptesq->altura == 1) ||
             (no->ptdir != NULL && no->ptdir->altura == 1)) && delta > 4) {
            delta--;
        }

        no->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the altura of no
    h = 1;
    if (no->ptesq != NULL) {
        h = MAX(no->ptesq->altura + no->edge_length + 1, h);
    }
    if (no->ptdir != NULL) {
        h = MAX(no->ptdir->altura + no->edge_length + 1, h);
    }
    no->altura = h;
}

//This function prints the given level of the given tree, assuming
//that the no has the given x cordinate.
void printLevel(BSTNode *no, int x, int level) {
    int i, isleft;
    if (no == NULL) return;
    isleft = (no->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((no->element - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", no->label);
        print_next += no->element;
    }
    else if (no->edge_length >= level) {
        if (no->ptesq != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (no->ptdir != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        printLevel(no->ptesq,
                   x - no->edge_length - 1,
                   level - no->edge_length - 1);
        printLevel(no->ptdir,
                   x + no->edge_length + 1,
                   level - no->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
void printElements(ArvBin *raiz) {
    BSTNode *proot;
    int xmin, i;
    if (raiz == NULL) return;
    proot = build_ascii_tree(*raiz);
    filledge(proot);
    for (i = 0; i < proot->altura && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->altura && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->altura; i++) {
        print_next = 0;
        printLevel(proot, -xmin, i);
        printf("\n");
    }
    if (proot->altura >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}


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
void impre_ArvBin(ArvBin* raiz);
void desenha_arvore_horiz(struct NO *arvore, int depth, char *path, int direita);
void desenha_arvore_ver(struct NO *arvore, int depth, char *path, int direita);
void draw_arvore_hor(struct NO *arvore);
void draw_arvore_ver(struct NO *arvore);
void ler_arquivo(char* nome, ArvBin* raiz);

int main(int argc, char const *argv){

  int x;
  char nome[200];

  printf("Digite o arquivo que deseja ler: \n");
  scanf("%[^\n]s", nome);


  ArvBin* raiz = cria_ArvBin();; // criando a raiz da arvore

  ler_arquivo(nome,raiz);

  printElements(raiz);

  x = altura_ArvBin(raiz);

  printf("altura_ArvBin: %d\n", x);

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
  int alt_direita = altura_ArvBin(&((*raiz)->dir)); // recursivamente pelo nó direito

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

void preOrdem_ArvBin(ArvBin* raiz)
{
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    printf("%d\n", (*raiz)->info);
    preOrdem_ArvBin(&((*raiz)->esq));
    preOrdem_ArvBin(&((*raiz)->dir));
  }
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
    posOrdem_ArvBin(&((*raiz)->esq));
    posOrdem_ArvBin(&((*raiz)->dir));
    printf("%d\n", (*raiz)->info);
  }
}

int insere_ArvBin(ArvBin* raiz, int valor)
{
  if(raiz == NULL)
    return 0;
  struct NO* novo;
  novo = (struct NO*)malloc(sizeof(struct NO));
  if(novo == NULL)
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

    if(valor > ant->info)   // insere como filho desse nó  folha
      ant->dir = novo;
    else
      ant->esq = novo;
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
    if(valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return 0;
}

//secondary function
void desenha_arvore_horiz(struct NO *arvore, int depth, char *path, int direita)
{
    // stopping condition
    if (arvore== NULL)
        return;

    // increase spacing
    depth++;

    // start with direita no
    desenha_arvore_horiz(arvore->dir, depth, path, 1);

    // set | draw map
    path[depth-2] = 0;

    if(direita)
        path[depth-2] = 1;

    if(arvore->esq)
        path[depth-1] = 1;

    // print root after spacing
    printf("\n");

    for(int i=0; i<depth-1; i++)
    {
      if(i == depth-2)
          printf("+");
      else if(path[i])
          printf("|");
      else
          printf(" ");

      for(int j=1; j<espaco; j++)
      if(i < depth-2)
          printf(" ");
      else
          printf("-");
    }

    printf("%d\n", arvore->info);

    // vertical espacors below
    for(int i=0; i<depth; i++)
    {
      if(path[i])
          printf("|");
      else
          printf(" ");

      for(int j=1; j<espaco; j++)
          printf(" ");
    }

    // go to esquerda no
    desenha_arvore_horiz(arvore->esq, depth, path, 0);
}

//primary fuction
void draw_arvore_hor(struct NO *arvore)
{
    // should check if we don't exceed this somehow..
    char path[255] = {};

    //initial depth is 0
    desenha_arvore_horiz(arvore, 0, path, 0);
}

void draw_arvore_ver(struct NO *arvore)
{
    // should check if we don't exceed this somehow..
    char path[255] = {};

    //initial depth is 0
    desenha_arvore_ver(arvore, 0, path, 0);
}

void desenha_arvore_ver(struct NO *arvore, int depth, char *path, int direita)
{
    // stopping condition
    if (arvore== NULL)
        return;


  printf("\n");

    printf("--");
    if(direita == 1){

    printf("\t\t\t%d", arvore->info);
    }
    else if(direita == 0){
      printf("%d", arvore->info);
    }
    printf("--");

  desenha_arvore_ver(arvore->esq, depth, path, 0);
  desenha_arvore_ver(arvore->dir, depth, path, 1);
}

void ler_arquivo(char* nome, ArvBin* raiz)
{
  char nome_f[200];
  FILE* arquivo;
  int f;
  arquivo = fopen("BSTs/bst1.txt", "r");

  if(arquivo == NULL){
    printf("Não existe esse arquivo\n");
    return;
  }
  else{
    while(!feof(arquivo)){
      fscanf(arquivo,"%d ",&f);
      insere_ArvBin(raiz,f);
    }
    fclose(arquivo);
  }

}
