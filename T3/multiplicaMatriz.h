typedef struct Matriz{
	unsigned long int colunas;
	unsigned long int linhas;
	float *valor;
} Matriz;

void multMatrizes(int Threads);

void *calculaMatriz(void *args);

void showMatriz(Matriz *matriz);