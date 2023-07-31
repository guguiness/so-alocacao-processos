#include <stdio.h>
#define TAM 10

int qntdProcessos = 0;          // PIDs existentes na memoria

// considerar para a memoria: 0 = lacuna / 1 = processo

void mostraMenu() {
    printf("\n\n---\tOpcoes disponiveis:\t---\n");
	printf("[1] Inserir processo na memoria\n");
	printf("[2] Remover processo da memoria\n");
	printf("[3] Listar estado das memorias\n");
	printf("[4] Finalizar aplicacao\n");
    printf("\nDigite o numero correspondente a opcao desejada: ");
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
    printf("\n");
}

void insereFirstFit(int *vetor, int tamProcesso) {
    int qntdBuracosConsecutivos = 0;
    int elementoAnterior = -1;                  // valor igual a 0: elemento elementoAnterior era buraco
    int indiceInicioBuraco = -1;                 // posicao onde comeca uma sequencia de buracos

    if(tamProcesso > TAM) {
        printf("Sem espaco suficiente para inserir o processo");
        return;
    }

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
        printf("Processo (%d) adicionado com sucesso", qntdProcessos);
    } else {
        printf("Sem espaco suficiente para inserir o processo");
    }
}

void removeProcesso(int *vetor, int pidProcesso) {
	int contTamProcesso = 0;

	for(int i = 0; i < TAM; i++) {
		if (vetor[i] == pidProcesso) {
			vetor[i] = 0;
			contTamProcesso++;
		}
	}
	
	if(contTamProcesso == 0) {
		printf("O processo nao existe na memoria\n");
	} else {
		printf("Processo (%d) removido com sucesso. Unidades de memoria liberadas: %d\n", qntdProcessos, contTamProcesso);
	}
}

int main() {
    int tamProcesso = 0;
    int pid = 0;
    int exec = 1;

    int memoria_ff[TAM];            // first fit
    // int memoria_bf[TAM];            // best fit
    // int memoria_wf[TAM];            // worst fit
    // int memoria_cf[TAM];            // circular fit

    inicializaMemoria(memoria_ff);
    // inicializaMemoria(memoria_bf);
    // inicializaMemoria(memoria_wf);
    // inicializaMemoria(memoria_cf);

    while(exec == 1) {
        int opcao = 0;

        mostraMenu();
        scanf("%i", &opcao);
        
        switch (opcao) {
            case 1:             // inserir processo
                printf("\nDigite o tamanho do processo a ser inserido: ");
                scanf("%i", &tamProcesso);

                if(tamProcesso <= 0) {
                    printf("\nERRO: Tamanho invalido");
                    break;
                }
                
                printf("\nFirst Fit: ");
                insereFirstFit(memoria_ff, tamProcesso);

                // printf("\nBest Fit: ");
                //insereBestFit(memoria_bf, tamProcesso);

                // printf("\nWorst Fit: ");
                //insereWorstFit(memoria_wf, tamProcesso);

                // printf("\nCircular Fit: ");
                //insereCircularFit(memoria_cf, tamProcesso);
                
                break;
                
            case 2:             // remover processo
                printf("\nDigite o PID do processo a ser removido: ");
                scanf("%i", &pid);
                
                printf("\nFirst Fit: ");
                removeProcesso(memoria_ff, pid);

                // printf("\nBest Fit: ");
                //removeProcesso(memoria_bf, pid);

                // printf("\nWorst Fit: ");
                //removeProcesso(memoria_wf, pid);

                // printf("\nCircular Fit: ");
                //removeProcesso(memoria_cf, pid);
                
                break;
                
            case 3:             // listar processos
                printf("\nMemoria First Fit: ");
                imprimeVetor(memoria_ff);

                // printf("\nMemoria Best Fit: ");
                // imprimeVetor(memoria_bf);

                // printf("\nMemoria Worst Fit: ");
                // imprimeVetor(memoria_wf);

                // printf("\nMemoria Circular Fit: ");
                // imprimeVetor(memoria_cf);
                break;
            case 4:             // finalizar aplicacao
                printf("\n---\tAplicacao finalizada\t---\n");
                exec = 0;
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
        }
    }

    printf("\n");
    return 0;
}