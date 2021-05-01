#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

void printaMatriz(int **mat, int tam, char *nome){

    printf("%s\n", nome);

    for(int i=0;i<tam;i++){

        printf("[");

        for(int j=0;j<tam;j++){

            if(j == tam - 1){
                printf("%d",mat[i][j]);
            } 
            else{
                printf("%d, ",mat[i][j]);
            }

        }
        printf("]\n");
    }
    printf("\n");
}

void inicializaMatriz(int **mat, int tam, int val){
    
    for(int i=0;i<tam;i++){
        mat[i] = (int*) malloc (tam * sizeof (float));
    }

    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            mat[i][j] = val;
        }
    }
}

void main (int argc, char *argv[]){
    int tam = atoi(argv[1]);
    float mult = atoi(argv[2]);
    int *MA[tam], *MB[tam];

    float *ma = (float*) aligned_alloc (32, tam * sizeof (float));
    float *mb = (float*) aligned_alloc (32, tam * sizeof (float));

    for(int i=0;i<tam;i++){
        ma[i] = 5;
        mb[i] = 2;
    }

    inicializaMatriz(MA, tam, 5);
    inicializaMatriz(MB, tam, 2);
    printaMatriz(MA, tam, "MA");
    printaMatriz(MB, tam, "MB");
    

    /*
    for (int i=0; i < tam; i+=8){
        __m256 esc = _mm256_set1_ps(mult);
        __m256 vet_piece = _mm256_load_ps(&ma[i]);
        __m256 result = _mm256_mul_ps(esc, vet_piece);
        _mm256_store_ps(&ma[i], result);
    }
    */

    printf("ma =[ ");

    for (int i=0; i < tam; i++){
        printf("%f ", ma[i]);
    }

    printf("]\n");
}