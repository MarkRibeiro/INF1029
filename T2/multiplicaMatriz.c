#include <stdio.h>
#include <stdlib.h>
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

/*int multMatrizes(Matriz *matrizA, Matriz *matrizB, Matriz *matrizC){
	unsigned long int m = matrizA->colunas, q = matrizB->linhas, n = matrizA->linhas;
	int ValorMultiplicado;

	if((m%8!=0)||(q%8!=0)||(n%8!=0)||(matrizA->linhas!=matrizB->colunas)){
		return 0;
	}

    for(int i=0; i<m; i++){
        for(int k=0;k<q;k++){
            for(int j=0; j<n; j++){
            	ValorMultiplicado = matrizA->valor[i*matrizA->linhas + j] * matrizB->valor[j*matrizB->linhas + k];
            	matrizC->valor[i*matrizC->linhas + k] += ValorMultiplicado;                            
            }
        }
        
    }

    return 1;
}*/

int multMatrizes(Matriz *matrizA, Matriz *matrizB, Matriz *matrizC){
	unsigned long int linhas = matrizA->linhas;
	//int ValorMultiplicado;

    int ValorA, ValorB;

	/*if((m%8!=0)||(q%8!=0)||(n%8!=0)||(matrizA->linhas!=matrizB->colunas)){
		return 0;
	}*/
    int index = 0;

    for (int i=0; i<linhas ; i++){

        for (int j=0; j<linhas; i++){
            ValorA *= matrizA->valor[i*matrizA->linhas + j];
        }

        for (int k=0; k<linhas; k++){
            ValorB *= matrizA->valor[k*matrizA->linhas + i];
        }

        matrizC->valor[index] = ValorA * ValorB;

        index += 1;

    }


    /*for(int i=0; i<m; i++){
        for(int k=0;k<q;k++){
            for(int j=0; j<n; j++){
            	ValorMultiplicado = matrizA->valor[i*matrizA->linhas + j] * matrizB->valor[j*matrizB->linhas + k];
            	matrizC->valor[i*matrizC->linhas + k] += ValorMultiplicado;                            
            }
        }
        
    }*/

    return 1;
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