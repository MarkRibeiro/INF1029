#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "multiplicaMatriz.h"
 

int main (void) {

    // Usa o tempo atual como ssed para geração de números aleatórios
    srand(time(0));

    // Matriz A
    Matriz matrizA;
    matrizA.colunas = 2;
    matrizA.linhas = 2;
    matrizA.valor = (int*) malloc (sizeof(int) * matrizA.colunas);
    
    preencheMatriz(&matrizA);

    printf("Matriz A:\n");
    showMatriz(&matrizA);

    printf ("\n");

    // Matriz B
    Matriz matrizB;
    matrizB.colunas = 2;
    matrizB.linhas = 2;
    matrizB.valor = (int*) malloc (sizeof(int) * matrizB.colunas);
    
    preencheMatriz(&matrizB);

    printf("Matriz B:\n");
    showMatriz(&matrizB);

    printf ("\n");

    // Multiplicação de Matrizes
    Matriz matrizC;
    matrizC.colunas = 2;
    matrizC.linhas = 2;
    matrizC.valor = (int*) malloc (sizeof(int) * matrizC.colunas);
    
    multMatrizes(&matrizA, &matrizB, &matrizC);

    printf("Matriz A x MatrizB:\n");
    showMatriz(&matrizC);

    printf ("\n");

    //Matriz matrizB = {4,4, 0};


    /*printf("Enter age: ");
    scanf("%d", &personPtr->age);*/

    //showMatriz(&matrizA);

    //Matriz matrizB = {4,4};
    //preencheMatriz(&matrizB);
    //showMatriz(&matrizB);


    //a();

    return 0;
}
