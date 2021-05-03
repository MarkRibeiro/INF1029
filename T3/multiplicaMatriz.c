#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

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

		if(pthread_create(&threads[t], NULL, calculaMatriz, args)){
			free(args);
		}

	}
	// Espera todas as threads terminarem de executar
	for(int t=0; t < numThreads; t++){
		pthread_join(threads[t],NULL); 
	}
	// Finaliza o timer de execução do programa como um todo
    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    double start_time_mili = start_time.tv_sec*1000000 + start_time.tv_usec;
    double end_time_mili = end_time.tv_sec*1000000 + end_time.tv_usec;
    double total_time = (end_time_mili - start_time_mili)/1000000;

    printf("Tempo de execução total do calculo da matriz: %lf \n", total_time);

}

void *calculaMatriz(void *args){

	calcula_matriz *val = args;

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

	for (int linhaA=inicio;linhaA<fim; linhaA++) {

		//Selecionando a linha de C para ser a mesma de A
		//valorC = matrizC.valor+(linhaA*matrizA.colunas);
		//Selecionando elementos de A
        for(int colunaBi=0;colunaBi<colunasMatrizB;colunaBi++) {
			__m256 acc = _mm256_set1_ps(matrizA.valor[linhaA*linhasMatrizA + colunaBi]);
			for(int colunaBj=0;colunaBj<colunasMatrizB;colunaBj+=8) {
				__m256 pLinhaA = _mm256_load_ps(&matrizB.valor[linhaA*linhasMatrizA + colunaBj]);
				__m256 pLinhaC = _mm256_load_ps(&matrizC.valor[linhaA*linhasMatrizA + colunaBj]);
				__m256 pLinhaf = _mm256_fmadd_ps(pLinhaA, acc, pLinhaC);
				_mm256_store_ps(&matrizC.valor[linhaA*linhasMatrizA + colunaBj], pLinhaf);
			}
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
			printf(" %.1f ", matriz->valor[i*n + j]);
		}
		printf("\n");
	}

}