typedef struct Matriz{
	unsigned long int colunas;
	unsigned long int linhas;
	int *valor;
} Matriz;

void preencheMatriz(Matriz *matriz);

void multMatrizes(int Threads, Matriz *matrizA, Matriz *matrizB, Matriz *matrizC);

void *calculaMatriz(void *args);

void showMatriz(Matriz *matriz);