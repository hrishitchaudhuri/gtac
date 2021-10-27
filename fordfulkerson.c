#include<stdio.h>
#include<stdlib.h>

int fordFulkerson(Graph *g int src, int sink) {
    int inc, max_flow = 0;

    int *pred = (int *) malloc(sizeof(int) * g->num_vertices);

    int **flow = (int **) malloc(sizeof(int *) * g->num_vertices);
    for (register int i = 0; i < g->num_vertices; i++)  
        flow[i] = (int *) malloc(sizeof(int *) * g->num_vertices);

    for (register int i = 0; i < g->num_vertices; i++)
        for (register int j = 0; j < g->num_vertices; j++)
            flow[i][j] = 0;

    while (bfs(src, sink, pred)) {
        inc = 0;

        for (register int i = g->num_vertices - 1; pred[i] >= 0; i = pred[i])
            inc = (inc < g->vertices[pred[i]][i] - flow[pred[i]][i]) ? inc : g->vertices[pred[i]][i] - flow[pred[i]][i];

        for (register int i = g->num_vertices - 1; pred[i] >= 0; i = pred[i]) {
            flow[pred[i]][i] += inc;
            flow[i][pred[i]] -= inc;
        }

        max_flow += inc;
    }

    return max_flow;
}