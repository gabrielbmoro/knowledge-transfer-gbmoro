/*###########################
 *Autor: Gabriel B Moro
 *---------------------------
 *Matrices Multiplication
 *###########################
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "hpcelo.h"
 
#define HIDE_TIMER 0

void printerOfMatrix(double *, int);

int main(int argc, char *argv[]) 
{
	/*Inicializacao de variaveis*/
	int size=10;

	double *A, *B, *R;

	if (argc > 1){
	  size = atoi(argv[1]);
	}

	/*Inicialização das matrizes*/
	A = hpcelo_create_matrixC (size);
	B = hpcelo_create_matrixC (size);
	R = calloc(size*size, sizeof(double));

	HPCELO_DECLARE_TIMER;
	HPCELO_START_TIMER;

	/*Multiplicacao das matrizes matA e matB*/
	int i,j,k;
	double tmp=0.0;

	#pragma omp parallel for private(i,j,k) schedule(static)
	for(i=0;i < size; i++)
		for(j=0;j < size; j++)
		{
			tmp=0;
			for(k=0; k < size; k++)
				tmp = tmp + A[i * size + k] * B[k * size + j];
			R[i * size + j] = tmp;
		}

	HPCELO_END_TIMER;
	
	if(HIDE_TIMER!=1)
	{
		HPCELO_REPORT_TIMER;
		
		//printf("The last element is %.2f\n", R[size*size-1]);
	} else {
		printerOfMatrix(R, size);
	}


	hpcelo_free_matrixC(A);
	hpcelo_free_matrixC(B);
	hpcelo_free_matrixC(R);
	
	return 0;
}

void printerOfMatrix(double *R, int size)
{
	int i,j;

	for(i=0; i < size; i++)
	{
		for(j=0; j < size; j++)
			 printf("%f\t", R[i * size + j]);
	    printf("\n");
	}
}
