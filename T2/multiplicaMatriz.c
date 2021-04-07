#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "multiplicaMatriz.h"

typedef struct {
    Matriz *matrizA;
	Matriz *matrizB;
	Matriz *matrizC;
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

void multMatrizes (int numThreads, Matriz *matrizA,  Matriz *matrizB, Matriz *matrizC) {

	// Inicializa o tempo de execução da multiplicação de matrizes
	clock_t begin = clock();

	// Faz o vetor de threads
	pthread_t threads[numThreads];
	int threadCounter = 0;

	// Número de linhas e colunas da matriz A, B e C são iguais
    
	for (int i=0;i<matrizA->linhas;i++) {
        for(int j=0;j<matrizA->colunas;j++) {

			// Cria as threads para fazer os calculo de Matriz A * Matriz B
			//printf("\nUsando a Thread: %d\n", threadCounter + 1);

			showMatriz(matrizB);

			calcula_matriz *args = (calcula_matriz*) malloc (sizeof (calcula_matriz));

			//args.matrizA = (Matriz*) malloc (sizeof(Matriz) * matrizA->linhas);
			args->matrizA = matrizA;

			//args.matrizB = (Matriz*) malloc (sizeof(Matriz) * matrizB->colunas);
			args->matrizB = matrizB;
			args->matrizC = matrizC;
			args->linhaA = i;
			args->colunaB = j;

			showMatriz(matrizB);


			/*if(pthread_create(&threads[threadCounter], NULL, calculaMatriz, args)){
				free(args);
			}*/

			calculaMatriz(args);
			free(args);

			threadCounter += 1;

			if (threadCounter == numThreads){
				threadCounter = 0;
			}
            
        }
    }

	// Espera todas as threads terminarem de executar
	/*for(int t=0; t < numThreads; t++){
		pthread_join(threads[t],NULL); 
	}*/

	// Finaliza o tempo de execução da multiplicação de matrizes
	clock_t end = clock();
    printf("Tempo de execução da multiplicação de matrizes: %lf \n", (double)(end - begin) / CLOCKS_PER_SEC);
	printf("\n");

}

void *calculaMatriz(void *args){

	calcula_matriz *val = args;

	int linhaA = val->linhaA;
	int colunaB = val->colunaB;
	Matriz *matrizA = val->matrizA;
	Matriz *matrizB = val->matrizB;
	Matriz *matrizC = val->matrizC;

	printf("linha da Matriz A: %d \n", (linhaA));
	printf("coluna da Matriz B: %d \n", (colunaB));

	double acc=0;
	for(int i=0; i<matrizA->linhas; i++) {

		printf("linha A: %d coluna A:%d posição no array A: %lu -> %d\n", linhaA, i, (linhaA*matrizA->linhas + i), matrizA->valor[linhaA*matrizA->linhas + i]);
		printf("linha B: %d coluna B:%d posição no array B: %lu -> %d\n \n", i, colunaB, (i*matrizB->colunas + colunaB), matrizB->valor[i*matrizB->colunas + colunaB]);
		acc += matrizA->valor[linhaA*matrizA->linhas + i] * matrizB->valor[i*matrizB->colunas + colunaB];		
	} 

	matrizC->valor[linhaA*matrizC->linhas + colunaB]  = acc;         

	// Encerra aquela thread
	pthread_exit(NULL); 

}


void showMatriz(Matriz *matriz){

	unsigned long int m = matriz->colunas, n = matriz->linhas;
	int i=0,j=0;

	for(i=0;i<m; i++){
		for(j=0; j<n; j++){
			printf(" %d ",matriz->valor[i*n + j]);
		}
		printf("\n");
	}

}