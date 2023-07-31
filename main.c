#include <stdio.h>
#define TAM 10

int qntdProcessos = 0;          // PIDs existentes na memoria

// considerar para a memoria: 0 = lacuna / 1 = processo

void mostraMenu() {
	
	int opcao = 0;
	
	printf("Digite o numero correspondente a opcao desejada: \n");
	printf("1. Inserir processo na memoria\n");
	printf("2. Remover processo da memoria\n");
	printf("3. Listar estado das memorias\n");
	printf("4. Finalizar aplicacao\n");
	
	scanf("%i", &opcao);
	
	switch (opcao) {
		case 1:
			int tam = 0;
			printf("Qual o tamanho do processo a ser inserido?\n");
			scanf("%i", &tam);
			
			//insereFirstFit(memoria_ff, tam);
			//insereBestFit(memoria_bf, tam);
			//insereWorstFit(memoria_wf, tam);
			//insereCircularFit(memoria_cf, tam);
			
			break;
			
		case 2:
			int pid = 0;
			printf("Qual o PID do processo a ser removido?\n");
			scanf("%i", &pid);
			
			//removeProcesso(memoria_ff, pid);
			//removeProcesso(memoria_bf, pid);
			//removeProcesso(memoria_wf, pid);
			//removeProcesso(memoria_cf, pid);
			
			break;
			
		case 3:
			printf("Memoria First Fit: \n");
			// funcao
			printf("Memoria Best Fit: \n");
			// funcao
			printf("Memoria Worst Fit: \n");
			// funcao
			printf("Memoria Circular Fit: \n");
			// funcao
			break;
		case 4:
			printf("Aplicacao finalizada\n");
			exit(0);
		default:
			printf("Opcao Invalida");
	}
}

void inicializaMemoria(int *memoria) {         // memoria inicialmente "vazia"
    for(int i = 0; i < TAM; i++) {
        memoria[i] = 0;
    } 
}

void imprimeVetor(int *vetor) {
    printf("|");
    for(int i = 0; i < TAM; i++)
        printf(" %d |", vetor[i]);
}

int insereFirstFit(int *vetor, int tamProcesso) {
    int qntdBuracosConsecutivos = 0;
    int elementoAnterior = -1;                  // valor igual a 0: elemento elementoAnterior era buraco
    int indiceInicioBuraco = -1;                 // posicao onde comeca uma sequencia de buracos

    if(tamProcesso > TAM) return 1;

    for(int i = 0; i < TAM && qntdBuracosConsecutivos != tamProcesso; i++) {
        if(vetor[i] == 0) {
            qntdBuracosConsecutivos++;
            if(elementoAnterior != 0) indiceInicioBuraco = i;
        } else {
            if(elementoAnterior == 0) qntdBuracosConsecutivos = 0;
        }
        elementoAnterior = vetor[i];
    }

    if(qntdBuracosConsecutivos == tamProcesso) {
        // insere o processo no vetor
        int cont = 0;
        qntdProcessos++;            // PID do novo processo
        for(int i = indiceInicioBuraco; cont != tamProcesso; i++) {
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