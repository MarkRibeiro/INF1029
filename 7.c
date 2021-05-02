#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

void main (int argc, char *argv[]) {

	int tam = atoi(argv[1]);
	int mult = atoi(argv[2]);

	int *v = (int*) aligned_alloc (32, tam * sizeof (int));

	for(int i=0;i<tam;i++){
		v[i] = 2;
	}

	for (int i=0; i < tam; i+=8){
		__m256i esc = _mm256_set1_epi32(mult);
		__m256i vet_piece = _mm256_load_si256((__m256i*)&v[i]);
		__m256i result = _mm256_mullo_epi32(esc, vet_piece);
		_mm256_store_si256((__m256i*)&v[i], result);
	}

	printf("v =[ ");
	for (int i=0; i < tam; i++){
		printf("%d ", v[i]);
	}
	printf("]\n");
}