#include<stdio.h>
#include<stdlib.h>

#include "graph.h"

void getDFSTree(Graph *g, int *visited, int v, int *discovered, int *low, int *time, int pt, int *isArticulation) {
    visited[v] = 1;

    int count_children = 0;

    discovered[v] = *time;
    low[v] = *time;
    (*time)++;

    int *adj = getAdjacencyList(g, v);
    int deg = countDegree(g, v);

    for (register int i = 0; i < deg; i++) {
        if (visited[adj[i]] == 0) {
            count_children++;
            getDFSTree(g, visited, adj[i], discovered, low, time, v, isArticulation);

            low[v] = (low[v] < low[adj[i]]) ? low[v] : low[adj[i]];

            if ((pt != -1) && (low[adj[i]] >= discovered[v]))
                isArticulation[v] = 1;
        }

        else if (adj[i] != pt)
            low[v] = (low[v] > discovered[adj[i]]) ? discovered[adj[i]] : low[v];
    }

    if ((pt == -1) && (count_children > 1))
        isArticulation[v] = 1;

    free(adj);
}

int *Tarjan(Graph *g) {
    int *discovered = (int *) malloc(sizeof(int) * g->num_vertices);
    int *low = (int *) malloc(sizeof(int) * g->num_vertices);
    int *visited = (int *) malloc(sizeof(int) * g->num_vertices);
    int *isArticulation = (int *) malloc(sizeof(int) * g->num_vertices);

    for (register int i = 0; i < g->num_vertices; i++) {
        discovered[i] = 0;
        visited[i] = 0;
        isArticulation[i] = 0;
    }

    int time = 0;
    int pt = -1;

    for (int i = 0; i < g->num_vertices; i++)
        if (visited[i] == 0)
            getDFSTree(g, visited, i, discovered, low, &time, pt, isArticulation);

    free(discovered);
    free(low);
    free(visited);

    return isArticulation;
}


int main() {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->num_vertices = 5;
    g->vertices = (int **) malloc(sizeof(int *) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        g->vertices[i] = (int *) malloc(sizeof(int) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        for (int j = 0; j < g->num_vertices; j++)
            g->vertices[i][j] = 0; 

    addUnweightedUndirectedGraphEdge(g, 1, 0);
    addUnweightedUndirectedGraphEdge(g, 0, 2);
    addUnweightedUndirectedGraphEdge(g, 2, 1);
    addUnweightedUndirectedGraphEdge(g, 0, 3);
    addUnweightedUndirectedGraphEdge(g, 3, 4);

    int *tarjan = Tarjan(g);

    for (register int i = 0; i < g->num_vertices; i++)
        if (tarjan[i])
            printf("%d ", i);
    printf("\n");

    for (int i = 0; i < g->num_vertices; i++) 
        free(g->vertices[i]);

    free(g->vertices);
    free(g);
    free(tarjan);

    return 0;
}