#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

void recebe_notas (float *notas, int *APR, int tamanho);
void contador_notas (int *APR, int tamanho, int *aprovados, int *reprovados);

int main (){

    int contador = 0;
    float notas[TAMANHO];
    int APR[TAMANHO];
    int aprovados = 0;
    int reprovados = 0;

    for (contador = 0; contador < TAMANHO; contador++){
        printf("Digite a %dº nota: ", contador + 1);
        scanf("%f", &notas[contador]);
    }

    recebe_notas(notas, APR, TAMANHO);
    contador_notas(APR, TAMANHO, &aprovados, &reprovados);

    printf("aprovados: %d ",aprovados);

    printf("reprovados: %d ",reprovados);


    return 0;
}

void recebe_notas ( float *notas, int *APR, int tamanho){
    int contador = 0;

    for(contador = 0; contador < tamanho; contador++){
        if (notas[contador] >= 6.0)
            APR[contador] = 1;
        else
            APR[contador] = 0;
    }

}

void contador_notas (int *APR, int tamanho, int  *aprovados, int *reprovados){
    int contador = 0;

    for (contador = 0; contador < tamanho; contador++){
        if(APR[contador] == 1)
            *aprovados += 1;

        else if(APR[contador] == 0)
            *reprovados += 1;

    }

}
