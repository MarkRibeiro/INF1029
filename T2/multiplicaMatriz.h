typedef struct Matriz{
	unsigned long int colunas;
	unsigned long int linhas;
	int *valor;
} Matriz;

void preencheMatriz(Matriz *matriz);

void multMatrizes(Matriz *matrizA, Matriz *matrizB, Matriz *matrizC);

void showMatriz(Matriz *matriz);