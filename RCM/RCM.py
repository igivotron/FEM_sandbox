import numpy as np
import matplotlib.pyplot as plt


def generate_sym_matrix(N):
    A = np.random.randint(0, 2, (N, N))
    # Make it symetrical
    for i in range(N):
        for j in range(i):
            A[j, i] = A[i, j]
    return A

def degree(A):
    return np.sum(A != 0, axis=1)

def find_start_node(A):
    deg = degree(A)
    return np.argmin(deg)  # Noeud avec le degré minimum

def cuthill_mckee(A):
    n = A.shape[0]
    degrees = degree(A)
    visited = [False] * n
    R = []
    
    start_node = find_start_node(A)
    queue = [start_node]
    visited[start_node] = True
    
    while queue:
        node = queue.pop(0)
        R.append(node)
        
        neighbors = np.where(A[node] != 0)[0]
        neighbors = [v for v in neighbors if not visited[v]]
        neighbors.sort(key=lambda x: degrees[x])
        
        for v in neighbors:
            visited[v] = True
            queue.append(v)

    # reverse R
    R = R[::-1]

    return R

def reorder(A, R):
    B = np.zeros_like(A)
    for i in range(len(R)):
        for j in range(A.shape[1]):
            B[i, j] = A[R[i], R[j]]
    return B

def show_fillin(A):
    plt.spy(A)
    plt.show()

A = generate_sym_matrix(10)

R = cuthill_mckee(A)
B = reorder(A, R)

print(R)

show_fillin(A)
show_fillin(B)


