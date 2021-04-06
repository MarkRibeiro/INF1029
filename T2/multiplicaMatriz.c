#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "multiplicaMatriz.h"

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

void multMatrizes (Matriz *matrizA,  Matriz *matrizB, Matriz *matrizC) {

	// Inicializa o tempo de execução da multiplicação de matrizes
	clock_t begin = clock();

	// Número de linhas e colunas da matriz A, B e C são iguais
    
	for (int i=0;i<matrizA->linhas;i++) {

        for(int k=0;k<matrizA->colunas;k++) {

            double acc=0;
            for(int j=0;j<matrizB->colunas;j++) {

				printf("linha da Matriz A: %lu \n", (i*matrizA->linhas + j));
				printf("coluna da Matriz B: %lu \n", (i*matrizB->colunas + j));
               acc += matrizA->valor[i*matrizA->linhas + j] * matrizB->valor[j*matrizB->colunas + k];
			   
			   //acc+=A[i][j] * B[j][k];
            } 

			matrizC->valor[i*matrizC->linhas + k]  = acc;         
            //C[i][k]=acc;
        }
    }

	// Finaliza o tempo de execução da multiplicação de matrizes
	clock_t end = clock();
    printf("Tempo de execução da multiplicação de matrizes: %lf \n", (double)(end - begin) / CLOCKS_PER_SEC);
	printf("\n");

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