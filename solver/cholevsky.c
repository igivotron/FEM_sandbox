#include "solver/cholevsky.h"

int cholevsky(double **A, double *B, int n, int band){
    for (int k=0; k<band; k++){
        if (fabs(A[k][k]) < EPS) return 1;
        int border = MIN(n, k+band);
        for (int i = k+1; i<border; i++){
            double factor = A[k][i]/A[k][k];
            for (int j=i; j<border; j++){
                A[i][j] -= factor*A[k][j];
            }
            B[i] -= factor*B[k];
        }
    }
    return 0;
}

int back_substitution(double **A, double *B, int n, int band){
    for (int i=n-1; i>=0; i--){
        double sum = 0;
        int border = MIN(n, i+band);
        for (int j=i+1; j<border; j++){
            sum += A[i][j]*B[j];
        }
        B[i] = (B[i] - sum)/A[i][i];
    }
    return 0;
}

int solve(double **A, double *B, int n, int band){
    if (cholevsky(A, B, n, band)) return 1;
    if (back_substitution(A, B, n, band)) return 1;
    return 0;
}
