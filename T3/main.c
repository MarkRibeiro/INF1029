#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main (int argc, char *argv[]) {

    int threads = atoi(argv[1]);
    int matSize = atoi(argv[2]);

    while(matSize%8!=0){
        matSize++;
    }

    printf("Número de Threads que serão executadas: %d\n", threads);
    printf("Tamanho das matrizes a serem multiplicadas: %d\n", matSize);

    // Inicializa o contador do programa como um todo
    struct timeval start_time;
    gettimeofday(&start_time, NULL);



    // Finaliza o timer de execução do programa como um todo
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    double start_time_mili = start_time.tv_sec*1000000 + start_time.tv_usec;
    double end_time_mili = end_time.tv_sec*1000000 + end_time.tv_usec;
    double total_time = (end_time_mili - start_time_mili)/1000000;

    printf("Tempo de execução total do programa: %lf \n", total_time);

    return 0;
}
