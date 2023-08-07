#include <stdio.h>
#include <stdlib.h>
#define COR_BURACO "\033[30;44m"
#define COR_PROCESSO "\033[30;47m"
#define COR_PADRAO "\033[m"

int tamMemoria = 0;
int qntdProcessos = 0;                          // PIDs existentes na memoria
int indiceUltimaAlocacao = 0;                   // indice do ultimo buraco preenchido pelo algoritmo Cicular Fit

// considerar para a memoria: 0 = lacuna / 1 = processo

void mostraMenu() {
    printf("\n\n-----------------------------------");
    printf("\nOpcoes disponiveis:\n");
	printf("[1] Inserir processo na memoria\n");
	printf("[2] Remover processo da memoria\n");
	printf("[3] Listar estado das memorias\n");
	printf("[4] Finalizar aplicacao\n");
    printf("\nDigite o numero correspondente a opcao desejada: ");
}

void inicializaMemoria(int *memoria) {         // memoria inicialmente "vazia"
    for(int i = 0; i < tamMemoria; i++) {
        memoria[i] = 0;
    } 
}

void imprimeVetor(int *vetor) {
    printf("|");
    for(int i = 0; i < tamMemoria; i++)
        printf(" %d |", vetor[i]);
    printf("\n");

}

void imprimeMemoria(int *vetor) {
    int i = 0;
    while (i < tamMemoria) {
        int valor = vetor[i];

        if (valor == 0) {
            // Segmento livre (buraco)
            int tamBuraco = 0;
            int j = i;
            while (j < tamMemoria && vetor[j] == 0) {
                tamBuraco++;
                j++;
            }
            printf("%s|%s B<%d> ", COR_PADRAO, COR_BURACO, tamBuraco);
            i = j;
        } else {
            // Segmento ocupado (processo)
            int pid = valor;
            int tamProcesso = 0;
            int j = i;
            while (j < tamMemoria && vetor[j] == pid) {
                tamProcesso++;
                j++;
            }
            printf("%s|%s P%d<%d> ", COR_PADRAO, COR_PROCESSO, pid, tamProcesso);
            i = j;
        }
    }
    printf("%s|", COR_PADRAO);
}

void insereFirstFit(int *vetor, int tamProcesso) {
    int qntdBuracosConsecutivos = 0;
    int elementoAnterior = -1;                 // valor igual a 0: elemento anterior era buraco
    int indiceInicioBuraco = -1;               // posicao onde comeca uma sequencia de buracos

    for(int i = 0; i < tamMemoria && qntdBuracosConsecutivos != tamProcesso; i++) {
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
        for(int i = indiceInicioBuraco; cont != tamProcesso; i++) {
            vetor[i] = qntdProcessos;
            cont++;
        }
        printf("Processo (%d) adicionado com sucesso", qntdProcessos);
    } else {
        printf("Sem espaco suficiente para inserir o processo");
    }
}

void insereBestFit(int *vetor, int tamProcesso) {
	int existeMelhor = 0;						// valor = 0: melhor escolha nao foi encontrada
	int qntdBuracosConsecutivos = 0;
	int qntdBuracosMelhor = tamMemoria;				// quantidade de buracos da melhor escolha
    int elementoAnterior = -1;                  // valor igual a 0: elemento anterior era buraco
    int indiceInicioBuraco = -1;                // posicao onde comeca uma sequencia de buracos
    int indiceInicioMelhor = -1;				// posicao onde comeca a sequencia de buracos da melhor escolha

	for(int i = 0; i <= tamMemoria; i++) {
		if(vetor[i] == 0 && i != tamMemoria) {
			qntdBuracosConsecutivos++;
			if(elementoAnterior != 0) indiceInicioBuraco = i;
		} else {
            if(elementoAnterior == 0) {
                if(qntdBuracosConsecutivos <= qntdBuracosMelhor && qntdBuracosConsecutivos >= tamProcesso) {
                    indiceInicioMelhor = indiceInicioBuraco;
                    qntdBuracosMelhor = qntdBuracosConsecutivos;
                    existeMelhor = 1;		// valor = 1: ha uma melhor escolha disponivel para alocar o processo
                    if(qntdBuracosMelhor == tamProcesso) break;
                }
                qntdBuracosConsecutivos = 0;
            }
        }
        elementoAnterior = vetor[i];
	}

	if(existeMelhor == 1) {
		// insere o processo no vetor
		int cont = 0;
		for(int i = indiceInicioMelhor; cont != tamProcesso; i++) {
            vetor[i] = qntdProcessos;
            cont++;
        }
        printf("Processo (%d) adicionado com sucesso", qntdProcessos);
	} else {
        printf("Sem espaco suficiente para inserir o processo");
    }
}

void insereWorstFit(int *vetor, int tamProcesso) {
	int existePior = 0;							// valor = 0: pior escolha nao foi encontrada
	int qntdBuracosConsecutivos = 0;
	int qntdBuracosPior = 0;					// quantidade de buracos da melhor escolha
    int elementoAnterior = -1;                  // valor igual a 0: elemento elementoAnterior era buraco
    int indiceInicioBuraco = -1;                // posicao onde comeca uma sequencia de buracos
    int indiceInicioPior = -1;					// posicao onde comeca a sequencia de buracos da melhor escolha

	for(int i = 0; i <= tamMemoria; i++) {
		if(vetor[i] == 0 && i != tamMemoria) {
			qntdBuracosConsecutivos++;
			if(elementoAnterior != 0) indiceInicioBuraco = i;
		} else {
            if(elementoAnterior == 0) {
                if (qntdBuracosConsecutivos >= qntdBuracosPior && qntdBuracosConsecutivos >= tamProcesso) {
                    indiceInicioPior = indiceInicioBuraco;
                    qntdBuracosPior = qntdBuracosConsecutivos;
            		existePior = 1;										// valor = 1: ha uma pior escolha disponivel para alocar o processo
            		//if (qntdBuracosPior == tamProcesso) break;		// caso a aplicacao parasse apos encontrar um buraco com tamanho exatamente igual ao do processo
                }
                qntdBuracosConsecutivos = 0;
            }
        }
        elementoAnterior = vetor[i];
	}
	
	if (existePior == 1) {
		// insere o processo no vetor
		int cont = 0;
		for(int i = indiceInicioPior; cont != tamProcesso; i++) {
            vetor[i] = qntdProcessos;
            cont++;
        }
        printf("Processo (%d) adicionado com sucesso", qntdProcessos);
	} else {
        printf("Sem espaco suficiente para inserir o processo");
    }
}

void insereCircularFit(int *vetor, int tamProcesso) {
    int qntdBuracosConsecutivos = 0;
    int elementoAnterior = -1;                  // valor igual a 0: elemento elementoAnterior era buraco
    int indiceInicioBuraco = -1;                 // posicao onde comeca uma sequencia de buracos
    int i;

    // Primeira busca a partir do indice da ultima alocacao
    for(i = indiceUltimaAlocacao; i < tamMemoria && qntdBuracosConsecutivos != tamProcesso; i++) {
        if(vetor[i] == 0) {
            qntdBuracosConsecutivos++;
            if(elementoAnterior != 0) indiceInicioBuraco = i;
        } else {
            if(elementoAnterior == 0) qntdBuracosConsecutivos = 0;
        }
        elementoAnterior = vetor[i];
    }

    // Segunda busca a partir do inicio do vetor ate o indice da ultima alocacao
    if(qntdBuracosConsecutivos != tamProcesso) {
        qntdBuracosConsecutivos = 0;
        for(i = 0; i < indiceUltimaAlocacao && qntdBuracosConsecutivos != tamProcesso; i++) {
            if(vetor[i] == 0) {
                qntdBuracosConsecutivos++;
                if(elementoAnterior != 0) indiceInicioBuraco = i;
            } else {
                if(elementoAnterior == 0) qntdBuracosConsecutivos = 0;
            }
            elementoAnterior = vetor[i];
        }
    }

    if(qntdBuracosConsecutivos == tamProcesso) {
        // insere o processo no vetor
        int i = 0;
        int cont = 0;
        for(i = indiceInicioBuraco; cont != tamProcesso; i++) {
            vetor[i] = qntdProcessos;
            cont++;
        }
        indiceUltimaAlocacao = (indiceInicioBuraco + tamProcesso) % tamMemoria;
        printf("Processo (%d) adicionado com sucesso", qntdProcessos);
    } else {
        printf("Sem espaco suficiente para inserir o processo");
    }
}

void removeProcesso(int *vetor, int pidProcesso) {
	int contTamProcesso = 0;

	for(int i = 0; i < tamMemoria; i++) {
		if (vetor[i] == pidProcesso) {
			vetor[i] = 0;
			contTamProcesso++;
		}
	}
	
	if(contTamProcesso == 0) {
		printf("O processo nao existe na memoria");
	} else {
		printf("Processo (%d) removido com sucesso. Unidades de memoria liberadas: %d", pidProcesso, contTamProcesso);
	}
}

int main() {
    int tamProcesso = 0;
    int pid = 0;
    int exec = 1;

    while(1) {
        printf("\nDigite o tamanho das memorias: ");
        scanf("%i", &tamMemoria);
        if(tamMemoria > 0) break;
        printf("\nERRO: tamanho de memoria invalido. Tente novamente\n");
    }

    int *memoria_ff = (int *)malloc(sizeof(int) * tamMemoria);
    int *memoria_bf = (int *)malloc(sizeof(int) * tamMemoria);
    int *memoria_wf = (int *)malloc(sizeof(int) * tamMemoria);
    int *memoria_cf = (int *)malloc(sizeof(int) * tamMemoria);

    inicializaMemoria(memoria_ff);
    inicializaMemoria(memoria_bf);
    inicializaMemoria(memoria_wf);
    inicializaMemoria(memoria_cf);

    while(exec == 1) {
        int opcao = 0;

        mostraMenu();
        scanf("%i", &opcao);
        
        switch (opcao) {
            case 1:             // inserir processo
                printf("\n-----------------------------------");
                printf("\nDigite o tamanho do processo a ser inserido: ");
                scanf("%i", &tamProcesso);

                if(tamProcesso <= 0) {
                    printf("\nERRO: Tamanho invalido");
                    break;
                }

                if(tamProcesso > tamMemoria) {
                    printf("\nERRO: Sem espaco suficiente para inserir o processo");
                    break;
                }

                qntdProcessos++;            // PID do novo processo

                printf("\nFirst Fit: ");
                insereFirstFit(memoria_ff, tamProcesso);

                printf("\nBest Fit: ");
                insereBestFit(memoria_bf, tamProcesso);

                printf("\nWorst Fit: ");
                insereWorstFit(memoria_wf, tamProcesso);

                printf("\nCircular Fit: ");
                insereCircularFit(memoria_cf, tamProcesso);
                
                break;
                
            case 2:             // remover processo
                printf("\n-----------------------------------");
                printf("\nDigite o PID do processo a ser removido: ");
                scanf("%i", &pid);
                
                printf("\nFirst Fit: ");
                removeProcesso(memoria_ff, pid);

                printf("\nBest Fit: ");
                removeProcesso(memoria_bf, pid);

                printf("\nWorst Fit: ");
                removeProcesso(memoria_wf, pid);

                printf("\nCircular Fit: ");
                removeProcesso(memoria_cf, pid);
                
                break;
                
            case 3:             // listar processos
                printf("\n-----------------------------------");
                printf("\n[First Fit]\t");
                // imprimeVetor(memoria_ff);
                imprimeMemoria(memoria_ff);

                printf("\n[Best Fit]\t");
                // imprimeVetor(memoria_bf);
                imprimeMemoria(memoria_bf);

                printf("\n[Worst Fit]\t");
                // imprimeVetor(memoria_wf);
                imprimeMemoria(memoria_wf);

                printf("\n[Circular Fit]\t");
                // imprimeVetor(memoria_cf);
                imprimeMemoria(memoria_cf);
                break;
            case 4:             // finalizar aplicacao
                free(memoria_ff);
                free(memoria_bf);
                free(memoria_wf);
                free(memoria_cf);

                printf("\n---\tAplicacao finalizada\t---\n");
                exec = 0;
                break;
            default:
                printf("\nOpcao invalida, aplicacao encerrada.\n");
                exec = 0;
                break;
        }
    }

    printf("\n");
    return 0;
}
