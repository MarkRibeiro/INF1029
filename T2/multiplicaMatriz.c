#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "multiplicaMatriz.h"

typedef struct {
	int startingLine;
	int finishLine;
} calcula_matriz;

void preencheMatriz(Matriz *matriz){
	unsigned long int m = matriz->colunas, n = matriz->linhas;
	int i=0,j=0;
	
	for(i=0;i<m; i++){
		for(j=0; j<n; j++){
            // Gera números aletórios entre 0 e 10
			matriz->valor[i * n + j] = (rand() % (10 - 0 + 1)) + 0;
		}
	}
}

void multMatrizes (int numThreads) {

	// Inicializa o contador do programa como um todo
    clock_t begin = clock();

	// Faz o vetor de threads
	pthread_t threads[numThreads];
	int threadCounter = 0;

	int matrizSlitSize = matrizA.linhas/numThreads;

	// Número de linhas e colunas da matriz A, B e C são iguais
	for (int t=0; t < numThreads; t++){

		calcula_matriz *args = (calcula_matriz*) malloc (sizeof (calcula_matriz));
		args->startingLine = matrizSlitSize*t;
		args->finishLine = args->startingLine + matrizSlitSize;

		if (matrizA.linhas%numThreads != 0 && t == numThreads - 1){
			args->finishLine += 1;
		}

		if(pthread_create(&threads[threadCounter], NULL, calculaMatriz, args)){
			free(args);
		}

	}

	// Espera todas as threads terminarem de executar
	for(int t=0; t < numThreads; t++){
		pthread_join(threads[t],NULL); 
	}

	// Finaliza o timer de execução do programa como um todo
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo de execução total do programa: %lf \n", time_spent);

}

void *calculaMatriz(void *args){

	calcula_matriz *val = args;

	printf("args->startingLine %d\n", val->startingLine);
	printf("args->finishingLine %d\n", val->finishLine);

	printf("\n");

	for (int linhaA=val->startingLine;linhaA<val->finishLine;linhaA++) {
        for(int colunaB=0;colunaB<matrizB.colunas;colunaB++) {

			int acc=0;
			for(int k=0; k<matrizA.linhas; k++) {
				acc += matrizA.valor[linhaA*matrizA.linhas + k] * matrizB.valor[k*matrizB.colunas + colunaB];		
			} 

			matrizC.valor[linhaA*matrizC.linhas + colunaB] = acc;  

		}
	}

	// Encerra aquela thread
	pthread_exit(NULL); 
	return 0;

}


void showMatriz(Matriz *matriz){

	unsigned long int m = matriz->colunas, n = matriz->linhas;
	int i=0,j=0;

	for(i=0;i<m; i++){
		for(j=0; j<n; j++){
			printf(" %d ", matriz->valor[i*n + j]);
		}
		printf("\n");
	}

}