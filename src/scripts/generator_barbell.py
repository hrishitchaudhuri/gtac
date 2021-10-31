import sys

if len(sys.argv) < 2:
    print("Error: Filename not specified.")
    sys.exit(0)

else:
    fname = sys.argv[1]

import networkx

M1 = 75
M2 = 25

G = networkx.generators.classic.barbell_graph(M1, M2)
A = networkx.linalg.graphmatrix.adjacency_matrix(G).toarray()

x, y = A.shape

fptr = open(fname, "w")

ret = str(M1 + M2) + "\n"

for i in range(x):
    for j in range(y):
        if j == y-1:
            ret += str(A[i][j]) + "\n"
        else:
            ret += str(A[i][j]) + " "

fptr.write(ret)

fptr.close()
