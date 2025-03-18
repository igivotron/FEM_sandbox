#include "cg.h"

int conjugateGradient(double **A, double *b, int n){
    // Initialisation des variables
    double *r = (double *)malloc(n*sizeof(double));
    double *p = (double *)malloc(n*sizeof(double));

    double alpha;
    double beta;
    double rtr;
    double new_rtr;
    double *Ap = (double *)malloc(n*sizeof(double));
    double pAp;

    // On stock la solution dans b
    for (int i = 0; i<n; i++){
        r[i] = b[i];
        p[i] = b[i];
        b[i] = 0;
    }

    // Gradient conjugué
    // Je calcul rtr une fois par boucle au lieu de trois fois
    // TODO : Arrêter la boucle si le résidu est suffisament petit
    rtr = 0;
    for (int i=0; i<n; i++) rtr += r[i]*r[i];

    for (int i=0; i<MAX_ITER; i++){
        // A p
        for (int j=0; j<n; j++){
            Ap[j] = 0;
            for (int k=0; k<n; k++){
                Ap[j] += A[j][k]*p[k];}}

        // p^T A p
        pAp = 0;
        for (int j=0; j<n; j++) pAp += p[j]*Ap[j];
        // Longueur du pas
        alpha = rtr/pAp;

        // Solution approximative
        for (int j=0; j<n; j++) b[j] += alpha*p[j];

        // Résidu
        for (int j=0; j<n; j++) r[j] -= alpha*Ap[j];

        // Amélioration du pas
        new_rtr = 0;
        for (int j=0; j<n; j++) new_rtr += r[j]*r[j];
        beta = new_rtr/rtr;
        rtr = new_rtr;

        // Nouvelle direction
        for (int j=0; j<n; j++) p[j] = r[j] + beta*p[j];
    }
    free(r);
    free(p);
    free(Ap);
    return 0;
}

// Pas testé
int diagonalScaling(double **A, double *b, int n){
    for (int i=0; i<n; i++){
        b[i] /= A[i][i];
        for (int j=0; j<n; j++){
            A[i][j] /= A[i][i];
        }
    }
    return 0;
}