#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include "multiplicaMatriz.h" 

int main (int argc, char *argv[]) {

    int threads = atoi(argv[1]);
    int matSize = atoi(argv[2]);

    // Inicializa o contador do programa como um todo
    clock_t begin = clock();

    // Matriz A
    matrizA.colunas = matSize;
    matrizA.linhas = matSize;
    matrizA.valor = (float*)aligned_alloc(32,matSize*matSize*sizeof(float));

    preencheMatriz(&matrizA, 5.0f);

    //printf("Matriz A:\n");
    //showMatriz(&matrizA);
    //printf ("\n");

    // Matriz B
    matrizB.colunas = matSize;
    matrizB.linhas = matSize;
    matrizB.valor = (float*)aligned_alloc(32,matSize*matSize*sizeof(float));
    
    preencheMatriz(&matrizB, 2.0f);

    //printf("Matriz B:\n");
    //showMatriz(&matrizB);
    //printf ("\n");

    // Multiplicação de Matrizes
    matrizC.colunas = matSize;
    matrizC.linhas = matSize;
    matrizC.valor = (float*)aligned_alloc(32,matSize*matSize*sizeof(float));
    preencheMatriz(&matrizC, 0.0f);
    
    multMatrizes(threads);

    //printf("Matriz A x Matriz B:\n");
    //showMatriz(&matrizC);
    //printf("\n");

    // Finaliza o timer de execução do programa como um todo
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo de execução total do programa: %lf \n", time_spent);

    return 0;
}



