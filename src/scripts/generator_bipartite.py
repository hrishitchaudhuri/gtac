import sys

if len(sys.argv) < 2:
    print("Error: Filename not specified.")
    sys.exit(0)

else:
    fname = sys.argv[1]

import networkx

M = 50
N = 50

G = networkx.algorithms.bipartite.generators.random_graph(N, M, 0.4)
A = networkx.linalg.graphmatrix.adjacency_matrix(G).toarray()

x, y = A.shape

fptr = open(fname, "w")

ret = str(N) + " " + str(M) +  "\n"

for i in range(x):
    for j in range(y):
        if j == y-1:
            ret += str(A[i][j]) + "\n"
        else:
            ret += str(A[i][j]) + " "

fptr.write(ret)

fptr.close()