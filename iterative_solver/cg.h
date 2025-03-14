#ifndef CG_H
#define CG_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-10
#define MAX_ITER 1000

int conjugateGradient(double **A, double *b, int n);



# endif