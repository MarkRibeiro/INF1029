#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "multiplicaMatriz.h" 

int main (void) {

    int threads;
    int matSize;

    // Seta o número de threads
    printf("Digite o número de Threads que serão executadas: ");
    scanf("%d",&threads);

    // Seta o tamanho da matriz
    printf("Digite o tamanho das matrizes a serem multiplicadas: ");
    scanf("%d",&matSize);

    // Inicializa o contador do programa como um todo
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    // Usa o tempo atual como ssed para geração de números aleatórios
    //srand(time(0));

    // Matriz A
    matrizA.colunas = matSize;
    matrizA.linhas = matSize;
    matrizA.valor = (int*) malloc (sizeof(int) * matrizA.colunas * matrizA.linhas);
    
    preencheMatriz(&matrizA);

        //printf("Matriz A:\n");
        //showMatriz(&matrizA);

        //printf ("\n");

    // Matriz B
    matrizB.colunas = matSize;
    matrizB.linhas = matSize;
    matrizB.valor = (int*) malloc (sizeof(int) * matrizB.colunas * matrizB.linhas);
    
    preencheMatriz(&matrizB);

        //printf("Matriz B:\n");
        //showMatriz(&matrizB);

        //printf ("\n");

    // Multiplicação de Matrizes
    matrizC.colunas = matSize;
    matrizC.linhas = matSize;
    matrizC.valor = (int*) malloc (sizeof(int) * matrizC.colunas  * matrizC.linhas);
    
    multMatrizes(threads);

        //printf("Matriz A x Matriz B:\n");
        //showMatriz(&matrizC);

        //printf ("\n");

    // Finaliza o timer de execução do programa como um todo
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    
    double start_time_mili = start_time.tv_sec*1000000 + start_time.tv_usec;
    double end_time_mili = end_time.tv_sec*1000000 + end_time.tv_usec;
    double total_time = (end_time_mili - start_time_mili)/1000000;

    printf("Tempo de execução total do programa: %lf \n", total_time);

    return 0;
}
