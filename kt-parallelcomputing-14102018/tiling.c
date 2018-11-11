/*###########################
 *Autor: Gabriel B Moro
 *---------------------------
 *Programa parallel: 
 *Multiplicação de Matrizes
 *###########################
 */

#include <stdlib.h>
#include <stdio.h>
#include "hpcelo.h"
#include <omp.h>

#define HIDE_TIMER 0

void multiply(double **, double **, double **, int, int);

int getBlock(int);

int min(int, int);

void printerOfMatrix(double **, int);

int main(int argc, char *argv[]) 
{
	/*Inicializacao de variaveis*/
	int size=10,block;
	double **A, **B, **R;

	if (argc > 1){
	  size = atoi(argv[1]);
	}

	block = getBlock(size);

	/*Inicialização das matrizes*/
	A = hpcelo_create_matrix (size);
	B = hpcelo_create_matrix (size);
	R = hpcelo_create_matrix (size);

	HPCELO_DECLARE_TIMER;
	HPCELO_START_TIMER;

	
	multiply(A ,B ,R ,size ,block);
	

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

	hpcelo_free_matrix(A,size);
	hpcelo_free_matrix(B,size);
	hpcelo_free_matrix(R,size);
	
	return 0;

}

int getBlock(int size)
{
	int block= size / 2;
	
	if(block > 450)
		return 512;
	else if(block > 250 && block < 450)
		return 256;
	else if(block > 100 && block < 250)
		return 64;
	else if(block > 25 && block < 100)
		return 32;
	else
		return 16;
}

int min(int x, int y)
{
	if(x<y)
		return x;
	else
		return y;
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


void multiply(double **A, double **B, double **R, int size, int block)
{
	register int jj,kk,i,j,k;
	double tmp=0;

	for(jj=0;jj < size; jj=jj+block)
	{
		for(kk=0; kk < size; kk=kk+block)
		{
			#pragma omp parallel for private(i,j,k) schedule(static)
			for(i=0; i < size; i++)
			{
				for(j=jj; j < min(jj+block, size); j++)
				{
					tmp=0;
					for(k=kk; k < min(kk+block,size); k++)
					{
						tmp = tmp + A[i][k] * B[k][j];
					}
					R[i][j] = tmp;
				}
			}
		}
	}
}
