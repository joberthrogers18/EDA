#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int fneuronio(int *ENTRADAS, int *PESOS, int T,int n,int *status);

int main (int argc, char *argv[]){
    
    int ENTRADAS[MAX], //vetor de entradas
        PESOS[MAX],//vetor de pesos
        T,//limiar T
        agitacao =0,
        *status = &agitacao;//determina se o status é "inibido" ou "ativado"
        
    printf("Entre com os valores de Entrada\n");
    for (int i=0; i<10;i++){
        scanf("%d", &ENTRADAS[i]);
    }
    
    printf("Entre com os valores de Pesos\n");
    for (int i=0; i<10;i++){
        scanf("%d", &PESOS[i]);
   }
    
    printf("Entre com o limiar T\n");
    scanf("%d", &T);
    
    printf("Limiar vale %d\n", agitacao);
    
    agitacao = fneuronio(ENTRADAS, PESOS, T, 10, status);
    
    printf("Limiar agora vale %d\n", agitacao);
    if (agitacao == 1){
        printf("Neuronio ativado");
    }
    else printf ("Neuronio inibido");
    
    return 0;
}

int fneuronio(int *ENTRADAS, int *PESOS, int T,int n, int *status){
    int Somap=0;
    
    for (int i=0; i<n; i++){
        Somap+= ENTRADAS[i]*PESOS[i];
        printf("%d\n",Somap);
    }
    
    if (Somap>T)
        *status = 1;
    
    printf("\n%d\n",Somap);
    return *status;
}
