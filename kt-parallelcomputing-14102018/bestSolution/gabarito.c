/*###########################
 *Author: Gabriel B Moro
 *---------------------------
 *Matrices Multiplication
 *###########################
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "hpcelo.h"

#define HIDE_TIMER 0

void printerOfMatrix(double **, int);

int main() 
{
	/*Inicializacao de variaveis*/
	int size=10000;

	double **A, **B, **R;

	/*Inicialização das matrizes*/
	A = hpcelo_create_matrix (size);
	B = hpcelo_create_matrix (size);
	R = hpcelo_create_matrix (size);

	HPCELO_DECLARE_TIMER;
	HPCELO_START_TIMER;

	/*Multiplicacao das matrizes matA e matB*/
	int i,j,k;
	double tmp=0.0;
	
	#pragma omp parallel for private(i,j,k,tmp) schedule(static)
	for(i=0;i < size; i++)
	{
		for(j=0;j < size; j++)
		{
			tmp=0;
			for(k=0; k < size; k++) {
				tmp = tmp + A[i][k] * B[k][j];
			}

			R[i][j] = tmp;
		}
	}

	HPCELO_END_TIMER;
	HPCELO_REPORT_TIMER;

	printerOfMatrix(R,size);

	hpcelo_free_matrix(A,size);
	hpcelo_free_matrix(B,size);
	hpcelo_free_matrix(R,size);
	
	return 0;
}

void printerOfMatrix(double **R, int size)
{
	int i,j;

	for(i=0; i < size; i++)
	{
		for(j=0; j < size; j++)
		{
			 printf("%f\n", R[i][j]);
		}
	}
}
