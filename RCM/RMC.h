#ifndef RMC_H
#define RMC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

# include "../utils/queue.h"

#define TOL 1e-6
#define INT_MAX 2147483647

int RCM(double *A, int n, int *perm);


#endif