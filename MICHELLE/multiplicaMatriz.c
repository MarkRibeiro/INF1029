#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <immintrin.h>
#include "multiplicaMatriz.h"

typedef struct {
	int startingLine;
	int finishLine;
} calcula_matriz;

void preencheMatriz(Matriz *matriz, float value){
	unsigned long int m = matriz->colunas, n = matriz->linhas;
	int i=0,j=0;

	__m256 val = _mm256_set1_ps(value);
	
	for(i=0;i<m*n; i += 8){
		_mm256_store_ps(&matriz->valor[i], val);
	}
}

void multMatrizes (int numThreads) {

	// Inicializa o contador do programa como um todo
    clock_t begin = clock();

	// Faz o vetor de threads
	pthread_t threads[numThreads];
	int threadCounter = 0;

	int matrizSplitSize = matrizA.linhas/numThreads;

	// Número de linhas e colunas da matriz A, B e C são iguais
	for (int t=0; t < numThreads; t++){

		calcula_matriz *args = (calcula_matriz*) malloc (sizeof (calcula_matriz));
		args->startingLine = matrizSplitSize*t*8;
		args->finishLine = args->startingLine + matrizSplitSize*8;	// Prob adicionar 8 aqui

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

	int inicio = val->startingLine;
	int fim = val->finishLine;
	int colunasMatrizB = matrizB.colunas;
	int linhasMatrizA = matrizA.linhas;

	for (int linhaA=inicio;linhaA<fim;linhaA+=8) {
        for(int colunaB=0;colunaB<colunasMatrizB;colunaB+=8) {

			int acc=0;
			for(int k=0; k<linhasMatrizA; k++) {
				acc += matrizA.valor[linhaA*linhasMatrizA + k] * matrizB.valor[k*colunasMatrizB + colunaB];		
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
			printf(" %f ", matriz->valor[i*n + j]);
		}
		printf("\n");
	}

}