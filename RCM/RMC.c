# include "RMC.h"

int compare(void *deg, const void *a, const void *b) {
    return ((int*)deg)[*(int*)a] - ((int*)deg)[*(int*)b];
}

int RCM(double *A, int n, int *perm) {
    int *degree = (int*)calloc(n, sizeof(int));
    int *visited = (int*)calloc(n, sizeof(int));

    // Calcul des degrés des sommets
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i * n + j] != 0) degree[i]++;
        }
    }

    int perm_index = 0;
    Queue *queue = createQueue(n);

    // Trouver le sommet de degré minimum pour commencer
    int min_deg = INT_MAX, start = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && degree[i] < min_deg) {
            min_deg = degree[i];
            start = i;
        }
    }

    // BFS modifié
    enqueue(queue, start);
    visited[start] = 1;

    while (!isEmpty(queue)) {
        int u = dequeue(queue);
        perm[perm_index++] = u;

        // Récupérer les voisins de u
        int *neighbors = (int*)malloc(n * sizeof(int));
        int count = 0;
        for (int v = 0; v < n; v++) {
            if (A[u * n + v] != 0 && !visited[v]) {
                neighbors[count++] = v;
            }
        }

        // Trier les voisins par ordre croissant de degré
        qsort_r(neighbors, count, sizeof(int), compare, (void *)degree);

        // Ajouter les voisins triés à la file
        for (int i = 0; i < count; i++) {
            enqueue(queue, neighbors[i]);
            visited[neighbors[i]] = 1;
        }

        free(neighbors);
    }

    // Inverser l'ordre du tableau de permutation
    for (int i = 0; i < n / 2; i++) {
        int temp = perm[i];
        perm[i] = perm[n - 1 - i];
        perm[n - 1 - i] = temp;
    }

    // Nettoyage mémoire
    free(degree);
    free(visited);
    free(queue->items);
    free(queue);
    
    return 0;
}
