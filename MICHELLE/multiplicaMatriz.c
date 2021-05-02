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
		args->startingLine = matrizSplitSize*t;
		args->finishLine = args->startingLine + matrizSplitSize;

		if (matrizA.linhas%numThreads != 0 && t == numThreads - 1){
			args->finishLine += 1;
		}

		if(pthread_create(&threads[threadCounter], NULL, calculaMatriz, args)){
			printf("saiiii\n");
			free(args);
			printf("Não foi aqui victor, relaxa\n");
		}

		printf("start: %d\nFinish: %d\n", args->startingLine, args->finishLine);

	}
	// Espera todas as threads terminarem de executar
	for(int t=0; t < numThreads; t++){
		pthread_join(threads[t],NULL); 
	}
	// Finaliza o timer de execução do programa como um todo
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo de execução total do calculo da matriz: %lf \n", time_spent);

}

void *calculaMatriz(void *args){

	calcula_matriz *val = args;

	printf("\n");

	int inicio = val->startingLine;
	int fim = val->finishLine;
	int colunasMatrizB = matrizB.colunas;
	int linhasMatrizA = matrizA.linhas;

	__m256 a;
	__m256 b;
	__m256 c;
	__m256 escalar_a_b;

	float *valorA = matrizA.valor;
	float *valorB = matrizB.valor;
	float *valorC = matrizC.valor;

	for (int linhaA=inicio;linhaA<fim; linhaA++/*, valorA+=8*/) {

		//Selecionando a linha de C para ser a mesma de A
		//valorC = matrizC.valor+(linhaA*matrizA.colunas);
		printf("LinhaA: %d\n", linhaA);
		//Selecionando elementos de A
        for(int colunaB=0;colunaB<colunasMatrizB;colunaB++) {
			
			//a = _mm256_set1_ps(valorA[j]);
			int acc=0;
			for(int k=0; k<colunasMatrizB; k++/*, valorB+=8, valorC+=8*/) {
				printf("%d ", k);
				acc += matrizA.valor[linhaA*linhasMatrizA + k] * matrizB.valor[k*colunasMatrizB + colunaB];
			} 
			printf("\nlinha: %d coluna: %d\n", linhaA, colunaB);
			valorC[linhaA*linhasMatrizA + colunaB] = acc;
			printf("Victor\n");
			//printf("\nvalor que vai ser armazenado: %.1f \n", valorC[linhaA*linhasMatrizA + colunaB]);

		}
		printf("sai do segundo for\n");

		//valorB = matrizB.valor;
	}
	printf("sai do terceiro for\n");
	
	// Encerra aquela thread
	pthread_exit(NULL); 
	return 0;

}


void showMatriz(Matriz *matriz){

	unsigned long int m = matriz->colunas, n = matriz->linhas;
	int i=0,j=0;

	for(i=0;i<m; i++){
		for(j=0; j<n; j++){
			printf(" %.1f ", matriz->valor[i*n + j]);
		}
		printf("\n");
	}

}