#include<stdio.h>

#include "graph.h"
#include "fileread.h"

Graph *readFile(const char *fname) {
    FILE *fptr = fopen(fname, "r");
    int n;

    fscanf(fptr, "%d\n", &n);

    Graph *g = initGraph(n);

    for (register int i = 0; i < n; i++) {
        for (register int j = 0; j < n-1; j++)
            fscanf(fptr, "%d ", &(g->vertices[i][j]));

        fscanf(fptr, "%d\n", &(g->vertices[i][n-1]));
    }

    return g; 
}

Graph *readBipartiteFile(const char *fname) {
    FILE *fptr = fopen(fname, "r");
    int n, m;

    fscanf(fptr, "%d %d\n", &n, &m);

    Graph *g = initGraph(n + m);

    for (register int i = 0; i < n + m; i++) {
        for (register int j = 0; j < n + m - 1; j++)
            fscanf(fptr, "%d ", &(g->vertices[i][j]));

        fscanf(fptr, "%d\n", &(g->vertices[i][n-1]));
    }

    return g; 
}
