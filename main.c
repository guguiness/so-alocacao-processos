#include <stdio.h>
#define TAM 10

// considerar para a memoria: 0 = lacuna / 1 = processo

void inicializaMemoria(int *memoria) {         // memoria inicialmente "vazia"
    for(int i = 0; i < TAM; i++) {
        memoria[i] = 0;
    } 
}

void imprimeVetor(int *vet) {
    printf("|");
    for(int i = 0; i < TAM; i++)
        printf(" %d |");
}

int main() {
    int memoria_ff[TAM];            // first fit
    int memoria_bf[TAM];            // best fit
    int memoria_wf[TAM];            // worst fit
    int memoria_cf[TAM];            // circular fit

    inicializaMemoria(memoria_ff);
    inicializaMemoria(memoria_bf);
    inicializaMemoria(memoria_wf);
    inicializaMemoria(memoria_cf);

    printf("\n");
    return 0;
}