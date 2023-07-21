#include <stdio.h>
#define TAM 10

// considerar para a memoria: 0 = lacuna / 1 = processo

void inicializaMemoria(int *memoria) {         // memoria inicialmente "vazia"
    for(int i = 0; i < TAM; i++) {
        memoria[i] = 0;
    } 
}

int main() {
    int memoria_ff[TAM];
    int memoria_bf[TAM];
    int memoria_wf[TAM];
    int memoria_cf[TAM];

    inicializaMemoria(memoria_ff);
    inicializaMemoria(memoria_bf);
    inicializaMemoria(memoria_wf);
    inicializaMemoria(memoria_cf);

    printf("\n");
    return 0;
}