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

void transpose(double **, int);

int main(int argc, char *argv[]) 
{
	/*Inicializacao de variaveis*/
	int size=10;

	double **A, **B, **R;

	if (argc > 1){
	  size = atoi(argv[1]);
	}

	/*Inicialização das matrizes*/
	A = hpcelo_create_matrix (size);
	B = hpcelo_create_matrix (size);
	R = hpcelo_create_matrix (size);

	HPCELO_DECLARE_TIMER;
	HPCELO_START_TIMER;

	transpose(B,size);

	/*Multiplicacao das matrizes matA e matB*/
	int i,j,k;
	double tmp=0.0;
	
	#pragma omp parallel for private(i,j,k,tmp) schedule(static)
	for(i=0;i < size; i++)
	{
		for(j=0;j < size; j++)
		{
			tmp=0;
			for(k=0; k < size; k++)
				tmp = tmp + A[i][k] * B[j][k];
			R[i][j] = tmp;
		}
	}

	HPCELO_END_TIMER;

	if(HIDE_TIMER!=1)
	{
		HPCELO_REPORT_TIMER;
		/*Temos que imprimir isso se não o compilador 
		não faz a multiplicação por não se justificar essa operação*/
		//printf("The last element is %.2f\n", R[size*size-1]);
	}else
	{
		printerOfMatrix(R,size);
	}
	/*Temos que imprimir isso se não o compilador 
	não faz a multiplicação por não se justificar essa operação*/
	
	//printf("The last element is %.2f\n", R[size-1][size-1]);

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
			 printf("%f\t", R[i][j]);
	    printf("\n");
	}
}

void transpose(double **B, int size)
{
	register int i,j;
	double tmp=0;

	for(i = 0; i < size; i++)
	{
		for(j=i+1; j < size; j++)
		{
			tmp = B[i][j];
			B[i][j] = B[j][i];
			B[j][i] = tmp;
		}
	}
}
