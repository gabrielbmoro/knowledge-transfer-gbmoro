/*
    This file is part of libhpcelo

    libhpcelo is free software: you can redistribute it and/or modify
    it under the terms of the GNU Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libhpcelo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Public License for more details.

    You should have received a copy of the GNU Public License
    along with libhpcelo. If not, see <http://www.gnu.org/licenses/>.
*/
#include "hpcelo.h"

//next function has been found here:
//http://stackoverflow.com/questions/26237419/faster-than-rand
//all credits to the authors there
static unsigned int g_seed;
static inline int fastrand()
{
  g_seed = (214013*g_seed+2531011);
  return (g_seed>>16)&0x7FFF;
}

double hpcelo_gettime (void)
{
  struct timeval tr;
  gettimeofday(&tr, NULL);
  return (double)tr.tv_sec+(double)tr.tv_usec/1000000;
}

double *hpcelo_create_matrixC (unsigned long long size)
{
  double *matrix = malloc(size*size * sizeof(double));
  /* Error checking */
  unsigned long long i;
  for (i=0; i < size * size; i++){
        matrix[i] = (double) fastrand();
  }
  return matrix;
}


void hpcelo_free_matrixC (double *matrix)
{
  free(matrix);
  return;
}

double **hpcelo_create_matrix (unsigned long long size)
{
  double **matrix = malloc(size * sizeof(double*));
  /* Error checking */
  unsigned long long i, j;
  for (i=0; i < size; i++){
    matrix[i] = malloc(size * sizeof(double));
    for (j = 0; j < size; j++){
      matrix[i][j] = (double) fastrand();
    }
  }
  return matrix;
}

void hpcelo_free_matrix (double **matrix, unsigned long long size)
{
  unsigned long long i;
  for (i=0; i < size; i++){
    free(matrix[i]);
  }
  free(matrix);
  return;
}
