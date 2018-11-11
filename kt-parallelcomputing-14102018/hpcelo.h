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
#ifndef __HPCELO_H_
#define __HPCELO_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define HPCELO_DECLARE_TIMER double hpcelo_t1, hpcelo_t2;
#define HPCELO_START_TIMER  hpcelo_t1 = hpcelo_gettime();
#define HPCELO_END_TIMER    hpcelo_t2 = hpcelo_gettime();
#define HPCELO_REPORT_TIMER {printf("HPCELO:%f\n", hpcelo_t2-hpcelo_t1);}

/* 
 * hpcelo_gettime: this function returns the current time in seconds
 * with a microsecond resolution. It uses =gettimeofday= call. 
 */
double hpcelo_gettime (void);

/* 
 * hpcelo_create_matrix: this function dynamically allocates a matrix
 * with size*size, considering the argument size. After this, it
 * initializes the matrix using a pseudo-random number generator known
 * as linear congruential generator (see wikipedia for details).
 */
double *hpcelo_create_matrixC (unsigned long long size);


/*
 * hpcelo_free_matrix: this function frees the allocated matrix.
 */
void hpcelo_free_matrixC (double *matrix);

/* 
 * hpcelo_create_matrix: this function dynamically allocates a matrix
 * with size*size, considering the argument size. After this, it
 * initializes the matrix using a pseudo-random number generator known
 * as linear congruential generator (see wikipedia for details).
 */
double **hpcelo_create_matrix (unsigned long long size);


/*
 * hpcelo_free_matrix: this function frees the allocated matrix.
 */
void hpcelo_free_matrix (double **matrix, unsigned long long size);


#endif
