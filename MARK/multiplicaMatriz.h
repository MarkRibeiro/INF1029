typedef struct Matriz{
	unsigned long int colunas;
	unsigned long int linhas;
	float *valor;
} Matriz;

Matriz matrizA;
Matriz matrizB;
Matriz matrizC;

void preencheMatriz(Matriz *matriz, float val);

void multMatrizes(int Threads);

void *calculaMatriz(void *args);

void showMatriz(Matriz *matriz);