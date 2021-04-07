#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "multiplicaMatriz.h" 

int main (void) {

    // Inicializa o contador do programa como um todo
    clock_t begin = clock();

    int threads;
    int matSize;

    // Seta o número de threads
    printf("Digite o número de Threads que serão executadas: ");
    scanf("%d",&threads);

    // Seta o tamanho da matriz
    printf("Digite o tamanho das matrizes a serem multiplicadas: ");
    scanf("%d",&matSize);

    // Usa o tempo atual como ssed para geração de números aleatórios
    //srand(time(0));

    // Matriz A
    Matriz matrizA;
    matrizA.colunas = matSize;
    matrizA.linhas = matSize;
    matrizA.valor = (int*) malloc (sizeof(int) * matrizA.colunas);
    
    preencheMatriz(&matrizA);

    printf("Matriz A:\n");
    showMatriz(&matrizA);

    printf ("\n");

    // Matriz B
    Matriz matrizB;
    matrizB.colunas = matSize;
    matrizB.linhas = matSize;
    matrizB.valor = (int*) malloc (sizeof(int) * matrizB.colunas);
    
    preencheMatriz(&matrizB);

    printf("Matriz B:\n");
    showMatriz(&matrizB);

    printf ("\n");

    // Multiplicação de Matrizes
    Matriz matrizC;
    matrizC.colunas = matSize;
    matrizC.linhas = matSize;
    matrizC.valor = (int*) malloc (sizeof(int) * (matrizC.colunas));
    
    printf("Entrei\n");
    multMatrizes(threads, &matrizA, &matrizB, &matrizC);
    printf("Sai\n");

    printf("Matriz A x Matriz B:\n");
    showMatriz(&matrizC);

    printf ("\n");

    // Finaliza o timer de execução do programa como um todo
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo de execução total do programa: %lf \n", time_spent);

    return 0;
}
