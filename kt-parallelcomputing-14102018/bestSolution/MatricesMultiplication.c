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

int min(int, int);

void printerOfMatrix(double *, int);

void transpose(double *, int);

int main() 
{
	/*Inicialização de variavéis*/
	int size=10000;
	int block=64;

	double *A, *B, *R;

	A = hpcelo_create_matrixC (size);
	B = hpcelo_create_matrixC (size);
	R = hpcelo_create_matrixC (size);

	HPCELO_DECLARE_TIMER;
	HPCELO_START_TIMER;

	transpose(B,size);

	/*Multiplicação das matrizes matA e matB*/
	int i,j,k,jj,kk;
	double tmp=0.0;

	for(jj=0; jj < size; jj=jj+block) {
	    for(kk=0; kk < size; kk=kk+block) {
		#pragma omp parallel for private(i,j,k,tmp)
		for(i=0;i < size; i++) {
		    for(j=jj;j < min(jj+block, size); j++) {
			tmp=0;
			for(k=kk; k < min(kk+block,size); k=k+5) {
					tmp = tmp + A[i * size + k] * B[j * size + k] +
					A[i * size + k + 1] * B[j * size + k + 1] +
					A[i * size + k + 2] * B[j * size + k + 2] +
					A[i * size + k + 3] * B[j * size + k + 3] +
					A[i * size + k + 4] * B[j * size + k + 4];
			}
			R[i * size + j] = tmp;
		    }
		}
	    }
	}

	HPCELO_END_TIMER;
	HPCELO_REPORT_TIMER;

	printerOfMatrix(R,size);

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
		{
			 printf("%f\n", R[i*size+j]);
		}
	}
}

void transpose(double *B, int size)
{
	int i,j;
	double tmp=0;

	#pragma omp parallel for private(i,j,tmp)
	for(i = 0; i < size; i++)
	{
		for(j=i+1; j < size; j++)
		{
			tmp = B[i*size+j];
			B[i*size+j] = B[j*size+i];
			B[j*size+i] = tmp;
		}
	}
}

int min(int x, int y) {
    if(x < y)
		return x;
	else
		return y;
}
