#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "multiplicaMatriz.h"

typedef struct {
	int linhaA;
	int colunaB;
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

	// Inicializa o tempo de execução da multiplicação de matrizes
	clock_t begin = clock();

	// Faz o vetor de threads
	pthread_t threads[numThreads];
	int threadCounter = 0;

	// Número de linhas e colunas da matriz A, B e C são iguais
    
	for (int i=0;i<matrizA.linhas;i++) {
        for(int j=0;j<matrizA.colunas;j++) {

			// Cria as threads para fazer os calculo de Matriz A * Matriz B
			calcula_matriz *args = (calcula_matriz*) malloc (sizeof (calcula_matriz));
			args->linhaA = i;
			args->colunaB = j;

			if(pthread_create(&threads[threadCounter], NULL, calculaMatriz, args)){
				free(args);
			}

			threadCounter += 1;

			if (threadCounter == numThreads){
				threadCounter = 0;
			}
            
        }
    }

	// Espera todas as threads terminarem de executar
	for(int t=0; t < numThreads; t++){
		pthread_join(threads[t],NULL); 
	}

	// Finaliza o tempo de execução da multiplicação de matrizes
	clock_t end = clock();
    printf("Tempo de execução da multiplicação de matrizes: %lf \n", (double)(end - begin) / CLOCKS_PER_SEC);
	printf("\n");

}

void *calculaMatriz(void *args){

	calcula_matriz *val = args;

	int linhaA = val->linhaA;
	int colunaB = val->colunaB;

	int acc=0;
	for(int i=0; i<matrizA.linhas; i++) {
		acc += matrizA.valor[linhaA*matrizA.linhas + i] * matrizB.valor[i*matrizB.colunas + colunaB];		
	} 

	matrizC.valor[linhaA*matrizC.linhas + colunaB] = acc;         

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