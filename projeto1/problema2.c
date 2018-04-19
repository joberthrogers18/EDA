//autores: 
// Joberth Rogers Tavares Costa - 16/0128013
// Elias Bernardo Marques Magalhães - 15/0009011

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

void recebe_notas (float *notas, int *APR, int tamanho);
void contador_notas (int *APR, int tamanho, int *aprovados, int *reprovados);
int percent_aprov (int *aprovados, int *reprovados, float *perc_aprov, float *perc_reprov);

int main (){

    int contador = 0;
    float notas[TAMANHO];
    int APR[TAMANHO];
    int aprovados = 0;
    int reprovados = 0;
    float perc_aprov = 0.0;
    float perc_reprov = 0.0;

    for (contador = 0; contador < TAMANHO; contador++){
        printf("Digite a %dº nota: ", contador + 1);
        scanf("%f", &notas[contador]);
    }

    recebe_notas(notas, APR, TAMANHO);
    contador_notas(APR, TAMANHO, &aprovados, &reprovados);

    printf("\n");

    printf("Quantidade de aprovados: %d \n",aprovados);

    printf("Quantidade de reprovados: %d \n",reprovados);

    printf("\n");

    percent_aprov (&aprovados, &reprovados, &perc_aprov, &perc_reprov);

    printf("Percentual de aprovados: %.1f%%\n", perc_aprov);

    printf("Percentual de reprovados: %.1f%%\n", perc_reprov);

    printf("\n");

    if (percent_aprov (&aprovados, &reprovados, &perc_aprov, &perc_reprov) == 1)
        printf("A maioria da turma foi APROVADA\n");
    else
        printf("A maioria da turma foi REPROVADA\n");

    printf("\n");

    return 0;
}

void recebe_notas ( float *notas, int *APR, int tamanho){
    int contador = 0;

    for(contador = 0; contador < tamanho; contador++){
        if (*(notas + contador) >= 6.0)
            *(APR + contador) = 1;
        else
            *(APR + contador) = 0;
    }

}

void contador_notas (int *APR, int tamanho, int  *aprovados, int *reprovados){
    int contador = 0;

    for (contador = 0; contador < tamanho; contador++){
        if(*(APR + contador) == 1)
            *aprovados += 1;

        else if(*(APR + contador) == 0)
            *reprovados += 1;

    }

}

int percent_aprov (int *aprovados, int *reprovados, float *perc_aprov, float *perc_reprov){
    *perc_aprov = ((*aprovados)  / 10.00) * 100.00 ;
    *perc_reprov = ((*reprovados )/ 10.00) * 100.00;

    if (*aprovados > 5)
        return 1;
    else
        return 0;
}
