typedef struct Matriz{
	unsigned long int colunas;
	unsigned long int linhas;
	int *valor;
} Matriz;

Matriz matrizA;
Matriz matrizB;
Matriz matrizC;

void preencheMatriz(Matriz *matriz);

void multMatrizes(int Threads);

void *calculaMatriz(void *args);

void showMatriz(Matriz *matriz);