#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <immintrin.h>
#include "multiplicaMatriz.h"

typedef struct {
	int startingLine;
	int finishLine;
} calcula_matriz;

void preencheMatriz(Matriz *matriz, float val){
	unsigned long int m = matriz->colunas, n = matriz->linhas;
	int i=0,j=0;
	
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
            // Gera números aletórios entre 0 e 10
			matriz->valor[i * n + j] = val;
		}
	}
}

void multMatrizes (int numThreads) {

	// Inicializa o contador do programa como um todo
    struct timeval start_time;
  	gettimeofday(&start_time, NULL);

	// Faz o vetor de threads
	pthread_t *threads = (pthread_t*) malloc (numThreads * sizeof (pthread_t));
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

	free(threads);

	// Finaliza o timer de execução do programa como um todo
	struct timeval end_time;
  	gettimeofday(&end_time, NULL);

  	double start_time_mili = start_time.tv_sec*1000000 + start_time.tv_usec;
  	double end_time_mili = end_time.tv_sec*1000000 + end_time.tv_usec;
	double total_time = (end_time_mili - start_time_mili)/1000000;

    printf("Tempo de execução da multiplicacao da matriz: %lf \n", total_time);

}

void *calculaMatriz(void *args){

	calcula_matriz *val = args;

	for (int linhaA=val->startingLine;linhaA<val->finishLine;linhaA++) {
        for(int colunaB=0;colunaB<matrizB.colunas;colunaB++) {

			__m256 acc=_mm256_setzero_ps();
			for(int k=0; k<matrizA.linhas/8; k++) {
				__m256 MA = _mm256_load_ps(&matrizA.valor[linhaA*matrizA.linhas + 8*k]);
				__m256 MB = _mm256_load_ps(&matrizB.valor[8*k*matrizB.colunas + colunaB]);
				acc = _mm256_fmadd_ps(MA, MB, acc);
				//acc += matrizA.valor[linhaA*matrizA.linhas + k] * matrizB.valor[k*matrizB.colunas + colunaB];
			} 

			matrizC.valor[linhaA*matrizC.linhas + colunaB] = (float*)&acc;  

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
			printf(" %.2f ", matriz->valor[i*n + j]);
		}
		printf("\n");
	}

}