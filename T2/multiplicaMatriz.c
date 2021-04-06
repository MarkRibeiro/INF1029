#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "multiplicaMatriz.h"

typedef struct {
    Matriz matrizA;
	Matriz matrizB;
	Matriz matrizC;
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

	// Número de linhas e colunas da matriz A, B e C são iguais
    
	for (int i=0;i<matrizA->linhas;i++) {
        for(int j=0;j<matrizA->colunas;j++) {

			// Cria as threads para fazer os calculo de Matriz A * Matriz B
			for(int t=0; t<numThreads; t++) {

				calcula_matriz *args;
				args->matrizA = *matrizA;
				args->matrizB = *matrizB;
				args->matrizC = *matrizC;
				args->linhaA = i;
				args->colunaB = j;

				printf("foi até aqui \n");


				pthread_create(&threads[t], NULL, calculaMatriz, args);
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
	Matriz matrizA = val->matrizA;
	Matriz matrizB = val->matrizB;
	Matriz matrizC = val->matrizC;

	// matriz A: {x, y, w, z}
	// x y
	// w z

	// matriz B: {a, b, c, d}
	// a b
	// c d

	// Ta na linha i = 0 da A:	{x, y}
	// Ta na coluna 0 do B:	{a, c}
	// Coloca na linha 0 coluna 0 do C: (x * a) + (y * c) -> faz na thread esse calculo
		// x * a = A[0 + 0] * B[0 + 0] = A[i + k] * B[k + j]
		// y * c = A[0 + 1] * B[1 + 1] = A[i + k] * B[k + j] -> deu cao

	// Ta na linha 0 da A:	{x, y}
	// Ta na coluna 1 do B:	{b, d}
	// Coloca na linha 0 coluna 1 do C: (x * b) + (y * d) -> faz na thread esse calculo

	double acc=0;
	for(int i=0; i<val->linhaA; i++) {

		printf("linha da Matriz A: %lu \n", (linhaA*matrizA.linhas + i));
		printf("coluna da Matriz B: %lu \n", (i*matrizB.colunas + colunaB));
		acc += matrizA.valor[linhaA*matrizA.linhas + i] * matrizB.valor[i*matrizB.colunas + colunaB];
		
		//acc+=A[i][j] * B[j][k];
	} 

	matrizC.valor[linhaA*matrizC.linhas + colunaB]  = acc;         
	//C[i][k]=acc;

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