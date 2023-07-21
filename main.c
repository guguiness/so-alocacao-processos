#include <stdio.h>
#define TAM 10

// considerar para a memoria: 0 = lacuna / 1 = processo

void criaMemoria(int *memoria) {         // memoria inicialmente "vazia"
    for(int i = 0; i < TAM; i++) {
        memoria[i] = 0;
    } 
}

int main() {


    printf("\n");
    return 0;
}