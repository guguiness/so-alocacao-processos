#include <stdio.h>
#define TAM 10

int qntdProcessos = 0;          // PIDs existentes na memoria (compartilhado??)

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

int insereFirstFit(int *vetor, int tamProcesso) {
    int qntdBuracosConsecutivos = 0;
    int anterior = -1;                  // valor igual a 0: elemento anterior era buraco
    int posIncioBuraco = -1;                 // posicao onde comeca uma sequencia de buracos

    if(tamProcesso > TAM) return 1;

    for(int i = 0; i < TAM && qntdBuracosConsecutivos != tamProcesso; i++) {
        if(vetor[i] == 0) {
            qntdBuracosConsecutivos++;
            if(anterior != 0) posIncioBuraco = i;
        } else {
            if(anterior == 0) qntdBuracosConsecutivos = 0;
        }
        anterior = vetor[i];
    }

    if(qntdBuracosConsecutivos == tamProcesso) {
        // insere o processo no vetor
        int cont = 0;
        qntdProcessos++;            // PID do novo processo
        for(int i = posIncioBuraco; cont != tamProcesso; i++) {
            vetor[i] = qntdProcessos;
            cont++;
        }
        return 0;
    } else {
        // sem espaco suficiente
        return 1;
    }
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