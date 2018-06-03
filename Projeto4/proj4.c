#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DEP 10
#define LAND 20
/*Estruturas dos voos*/
struct voo{
      char codigo[7] ;
      char tipo;//A ou D;
      int comb;
      struct voo* prox ;
      };
typedef struct voo Voo;

/*Estruturas das pistas*/
struct fila{
      Voo* ini ;
      Voo* fim ;
};
typedef struct fila Fila ;

/*Cabecalho das funcoes*/
int geraRand(int min, int max);
Voo* insereEV(Voo* EV, char* codigo, char t);
void libera(Fila *f);
void insere(Fila *f, Voo* aux);
void decre_comb(Voo *ini);
Voo* ins_fim(Voo* fim, Voo* aux);
Fila *cria(void);
void imprimeFila(Voo* ini);
Voo *EVretira(Voo* EV);
int BuscaComb0(Voo* EV, Fila** pista);
int max(int x1, int x2, int x3);
void retira_Fila(Fila* f);
int veri_comb0(Voo *ini);
void retira_pri(Voo* ini, int liber);

int main(){
    time_t agora1,agora2,agora3;
    agora1=agora2=agora3=(time(NULL)/60)%60; /*tempo em minutos*/
    int hora=((time(NULL)/3600)-3)%24, min = (time(NULL)/60)%60;
    int total_simulacao=0;
    int NApro=0, NDec=0, NVoos=0;
    int i, j = 0, comb0;
    Voo* EVlist=NULL;
    Fila *pista[3];
    char codigos[][7] = {"VG3001", "JJ4404", "LN7001", "TG1501",
    "GL7602", "TT1010", "AZ1009", "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603",
    "RL7880", "AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
    "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004",
    "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029",
    "VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
    "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020", "AZ1098",
    "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611"};

    /*geração dos voos*/
    srand(time(NULL));
    NVoos = geraRand(20,64);
    NApro = geraRand(10,32);
    NDec = NVoos - NApro;

    /*Preenchendo o campo de codigos nos primeiros voos na lista de eventos*/
    for(i=0;i<NApro;i++)
        EVlist = insereEV(EVlist,codigos[i],'a');
    /*Preenchendo o campo de codigos os restantes dos voos com na lista de eventos*/
    for(i=NApro;i<NVoos;i++)
        EVlist = insereEV(EVlist,codigos[i],'d');

    /*Criação das pistas (filas)*/
    for(i=0;i<3;i++)
        pista[i] = cria();

    /*Computando a quantidade de voos com combustivel 0*/
    comb0 = BuscaComb0(EVlist,pista);
    if(comb0>=3){
        printf("Alerta Geral de Desvio de Aeronave!\n\n");
    }
    printf("%d", comb0);

    int aux_temp0 = 0;
    int aux_temp1 = 0;
    int aux_temp2 = 0;

    /*Preenchendo os voos em suas respectivas pistas (filas)*/
    for(i=0;i<NVoos-comb0;i++){
      printf(" comb0: %d", comb0);
        switch (EVlist->tipo){
            case 'a':
                insere(pista[0],EVlist);

                      /*   aux_temp0 += LAND;
                        if(aux_temp0 >= 10){
                          decre_comb(pista[0]->ini);
                          aux_temp0 = 0;
                        }
                        agora1=agora1+LAND;
                         printf("\n\nTempo total na pista 1: %ld minutos\n", agora1);*/
            break;
                    case 'd':
                    insere(pista[1], EVlist);
                    /* aux_temp1 += LAND;
                    if(aux_temp1 >= 10){
                      decre_comb(pista[1]->ini);
                      aux_temp1 = 0;
                    }
                    agora2=agora2+DEP;*/
            break;
        }
        EVlist = EVretira(EVlist);
   }

   printf("\n ---------------------------------------------------------------------------------\n");
   printf("Aeroporto Internacional de Brasília\n");
   printf("Hora Inicial: %d: %d\n", hora, min);
   printf("Fila de Pedidos: [código do voo – P/D – prioridade]\n");
   printf("NVoos: %d\n", NVoos);
   printf("Naproximações: %d\n", NApro);
   printf("NDecolagens: %d\n", NDec);
   printf(" ---------------------------------------------------------------------------------\n");

   /*Imprimindo os resultados dos eventos*/
   printf("Hora Atual: %d horas %d minutos\n\n", hora,min);
   total_simulacao = max(agora1,agora2,agora3);
   printf("\tPista1: \n\n");
   imprimeFila(pista[0]->ini);
   printf("\n\nTempo total na pista 1: %ld minutos\n\n", agora1);
   printf("\tPista2: \n\n");
   imprimeFila(pista[1]->ini);
   printf("\n\nTempo total na pista 2: %ld minutos\n\n", agora2);
   printf("\n\nTotal da simulação (em minutos): %d minutos\n\n", total_simulacao);

   //retira_Fila(pista[0]);

   //imprimeFila(pista[0]->ini);

   /*printf("*****comeco**************\n");
   imprimeFila(pista[0]->ini);
   printf("********************\n");*/

   int combustivel = 0;

   while(1){

      Fila* p;
      Fila* p2;


     /*combustivel = veri_comb0(pista[0]->ini);

     printf("combustiveis 0 : %d\n", combustivel);

     if(combustivel > 0)
     {
          retira_pri(pista[0]->ini,2);
          printf("********************\n");
          imprimeFila(pista[0]);
          printf("********************\n");
     }*/


    if(pista[0]->ini!=NULL){

         aux_temp0 += LAND;

           printf("Voo: %s\n", pista[0]->ini->codigo);
           printf("combustivel: %d\n", pista[0]->ini->comb);

           p = pista[0]->ini;
           pista[0]->ini= pista[0]->ini->prox;
           free(p);

           if(aux_temp0 >= 50){
             decre_comb(pista[0]->ini);
             aux_temp0 = 0;
           }
           agora1=agora1+LAND;

           retira_pri(pista[0]->ini,10);

     }

     if(pista[1]->ini!=NULL){
       printf("test2: %s\n", pista[1]->ini->codigo);
       p2 = pista[1]->ini;
       pista[1]->ini= pista[1]->ini->prox;
       free(p2);
     }

     if(pista[0]->ini==NULL && pista[1]->ini==NULL){
       printf("acabou\n");
       break;
     }

   }


   system("pause");
   return 0;
}//fim do programa principal

/**************************Funcoes************************/

/*Insere o voo na lista de eventos e preenche o codigo e combustivel*/
Voo* insereEV(Voo* EV, char* codigo, char t){
     Voo* v = (Voo*)malloc(sizeof(Voo));
     strcpy(v->codigo, codigo);
     if(t=='d')
        v->comb = 12;
     else
         v->comb = geraRand(0,12);
     v->tipo = t;
     v->prox = EV;
     return v;
}
/*cria a filas(pistas)*/
Fila *cria(void){
    Fila* f = (Fila*)malloc(sizeof(Fila)) ;
    f->ini = f->fim = NULL ;
    return f ;
}
/*insere o novo voo no fim da lista de eventos*/
Voo* ins_fim(Voo* fim, Voo* aux){
   Voo* p = (Voo*)malloc(sizeof(Voo)) ;
   strcpy(p->codigo,aux->codigo);
   p->tipo = aux->tipo;
   p->comb = aux->comb;
   p->prox=NULL;
   if(fim!=NULL)
     fim->prox = p ;
   return p ;
}
/*Insere o voo na fila (pista)*/
void insere(Fila *f, Voo* aux){
    f->fim = ins_fim(f->fim, aux);
    if (f->ini==NULL)
      f->ini = f->fim ;
}
/*Verifica se a fila esta vazia*/
int vazia(Fila* f){
   return (f->ini==NULL);
}
/*Libera a fila*/
void libera(Fila *f){
    Voo* q = f->ini;
    while(q!=NULL){
      Voo* t = q->prox ;
      free(q);
      q = t ;
    }
    free(f);
}
/*Gerador de numeros pseudoaleatorios*/
int geraRand(int min, int max){
    int r;
    r=min+rand()%(max-min+1);
    return r;
}
/*Imprime os elementos da referida fila (pista)*/
void imprimeFila(Voo* ini){
    while(ini!=NULL){
        printf("Voo: %s", ini->codigo);
        printf(" [%c(%d)]\n\n", ini->tipo, ini->comb);
        ini = ini->prox;
    }
}

void decre_comb(Voo *ini){
  while(ini!=NULL){
       ini->comb = ini->comb - 1;
      ini = ini->prox;
  }
}

/*Retira o elemento da lista de eventos apos ser processado*/
Voo* EVretira(Voo* EV){
  Voo* p = EV->prox;
  free(EV);
  return p;
}

void retira_Fila(Fila* f){
  Fila* p = f->ini;
  f->ini = f->ini->prox;
  free(p);
}

void retira_pri(Voo* ini, int liber){
/*  int i = 0;
  printf("Seria a remoção");
  while(ini!= NULL){
      if(ini->prox->comb == 0){
        /*if(i < liber){
          printf("\n\nCódigo do voo: %s\n", ini->prox->codigo);
          printf("Status: aeronave pousou\n");
          printf("Horário do início do procedimento:\n");
          printf("Número da pista: 1\n\n");
          i++;
        }

        Voo* p = ini->prox;
        ini = ini->prox->prox;
        free(p);      printf("passou\n");
        ini = ini->prox->prox;

     }
     else{
       ini = ini->prox;
     }
  }*/

  Voo* ant=NULL;
  ant = ini;
  ini = ini->prox;

  while(ini!=NULL){
     if(ini->comb==0){
        ini = EVretira(ini);
        ant->prox = ini;
     }
     ant = ini;
     //retira o elemento do final da lista de eventos
     if(ini!=NULL)
     ini = ini->prox;
  }

}

int veri_comb0(Voo *ini){
  int comb = 0;
  while(ini!=NULL){
      if(ini->comb == 0){
        comb++;
      }
      ini = ini->prox;
  }
  return comb;
}

//Busca os Voos com prioridade de atendimento e coloca nas filas
int BuscaComb0(Voo* EV, Fila** pista){
   int comb0=0;
   Voo* ant=NULL;
   //retira os primeiro evento da lista se tiverem combustivel 0
   //e coloca em uma das pistas
   while(EV->comb==0){
      insere(pista[comb0%3],EV);
      EV = EVretira(EV);
      comb0++;
   }

   ant = EV;
   EV = EV->prox;

   //retira um evento do meio da lista e coloca nas filas de pouso
   //em caso de combustivel 0
   while(EV!=NULL){
      if(EV->comb==0){
         insere(pista[comb0%3], EV);
         comb0++;
         EV = EVretira(EV);
         ant->prox = EV;
      }
      ant = EV;
      //retira o elemento do final da lista de eventos
      if(EV!=NULL)
      EV = EV->prox;
   }
   //retorna o numero de Voos com combustivel 0
   return comb0;
 }

 /*Escolhe o maior dos 3 numeros*/
 int max(int x1, int x2, int x3){
    if(x1>=x2 && x1>=x3)
        return x1;
    else if(x2>=x1 && x2>=x3)
        return x2;
        else
            return x3;
 }
