#include<stdio.h>

void multmm (int m, int n, int q, double **A, double **B, double **C)
{
    for (int i=0;i<m;i++)
    {
        for(int k=0;k<q;k++)
        {

            double acc=0;
            for(int j=0;j<n;j++)
            {
               acc+=A[i][j] * B[j][k];
            }            
            C[i][k]=acc;
        }
    }

}

void prtmm (int linha, int coluna, int q, double **A)
{
    for (int i=0;i<coluna;i++)
    {
	for(int j=0;j<linha;j++){
		printf("%lf ", A[i][j]);
	}            
	printf("\n");
    }

}

int main (){
	double v10[2] = {1,2};
	double v11[2] = {3,4};
	double *v1[2] = {v10,v11};

	double v2[2][2] = {{5, 6}, {7, 8}};

	double vr0[2];
	double vr1[2];
	double *vr[2] = {vr0,vr1};


	multmm (2, 2, 2, (double **)v1, (double **)v1, (double **)vr);
	prtmm (2, 2, 2, (double **)vr);

	return 0;
}