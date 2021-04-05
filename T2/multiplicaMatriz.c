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

void multMatrizes(Matriz *matrizA, Matriz *matrizB, Matriz *matrizC){

	// Inicializa o tempo de execução da multiplicação de matrizes
	clock_t begin = clock();

	unsigned long int m = matrizA->colunas, q = matrizB->linhas, n = matrizA->linhas;
	int ValorMultiplicado;

	/*if((m%8!=0)||(q%8!=0)||(n%8!=0)||(matrizA->linhas!=matrizB->colunas)){
		return 0;
	}*/

    for(int i=0; i<m; i++){
        for(int k=0;k<q;k++){
            for(int j=0; j<n; j++){
            	ValorMultiplicado = matrizA->valor[i*matrizA->linhas + j] * matrizB->valor[j*matrizB->linhas + k];
            	matrizC->valor[i*matrizC->linhas + k] += ValorMultiplicado;                            
            }
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