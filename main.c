# include "RCM/RMC.h"
# include "solver/cholevsky.h"
# include "iterative_solver/cg.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

int get_sym_matrix(double *A, int n){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<=i; j++){
            A[i*n+j] = rand()%10;
            A[j*n+i] = A[i*n+j];
        }
    }
    return 0;
}

double **get_array(double *A, int n){
    double **array = (double **)malloc(n*sizeof(double *));
    for (int i = 0; i<n; i++){
        array[i] = (double *)malloc(n*sizeof(double));
        for (int j = 0; j<n; j++){
            array[i][j] = A[i*n+j];
        }
    }
    return array;
}

void print_matrix(double *A, int n){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            printf("%f ", A[i*n+j]);
        }
        printf("\n");
    }
}

void save2file(double *A, int n, char *filename){
    FILE *file = fopen(filename, "w");
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            fprintf(file, "%f ", A[i*n+j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main(void){
    int n = 10;
    double *A = (double *)malloc(n*n*sizeof(double));
    int *perm = (int *)malloc(n*sizeof(int));

    get_sym_matrix(A, n);
    print_matrix(A, n);


    free(A);
    free(perm);

    return 0;

}