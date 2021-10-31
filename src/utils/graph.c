#include<stdio.h>
#include<stdlib.h>

#include"graph.h"

Graph *initGraph(int n) {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->num_vertices = n;
    g->vertices = (int **) malloc(sizeof(int *) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        g->vertices[i] = (int *) malloc(sizeof(int) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        for (int j = 0; j < g->num_vertices; j++)
            g->vertices[i][j] = 0;
            
    return g;
}

void addUnweightedUndirectedGraphEdge(Graph *g, int v1, int v2) {
    g->vertices[v1][v2] = 1;
    g->vertices[v2][v1] = 1;
}

void addWeightedUndirectedGraphEdge(Graph *g, int v1, int v2, int cost) {
    g->vertices[v1][v2] = cost;
    g->vertices[v2][v1] = cost;
}

void addUnweightedDirectedGraphEdge(Graph *g, int v1, int v2) {
    g->vertices[v1][v2] = 1;
}

void addUnweightedUndirectedMultigraphEdge(Graph *g, int v, int u) {
    g->vertices[v][u]++;
    g->vertices[u][v]++;
}

void deleteUndirectedGraphEdge(Graph *g, int v1, int v2) {
    g->vertices[v1][v2] = 0;
    g->vertices[v2][v1] = 0;
}

void deleteUndirectedMultigraphEdge(Graph *g, int v, int u) {
    g->vertices[v][u]--;
    g->vertices[u][v]--;
}

int countDegree(Graph *g, int v) {
    int count = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        if (g->vertices[v][i] != 0)
            count++;
    
    return count;
}

int countMultigraphDegree(Graph *g, int v) {
    int count = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        if (g->vertices[v][i] != 0)
            count += g->vertices[v][i];
    
    return count;
}

int countUndirectedEdges(Graph *g) {
    int count = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        for (register int j = 0; j < g->num_vertices; j++)
            if (g->vertices[i][j])
                count++;

    return count;
}

int countEdges(Graph *g) {
    int count = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        for (register int j = 0; j < g->num_vertices; j++)
            if (g->vertices[i][j])
                count++;

    return count;
}

int getSolitaryVertex(Graph *g, int v) {
    for (register int i = 0; i < g->num_vertices; i++)
        if (g->vertices[v][i] == 1)
            return i;
    return -1;
}

int *getAdjacencyList(Graph *g, int v) {
    int *vertices = (int *) malloc(sizeof(int) * countDegree(g, v));

    int curr = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        if (g->vertices[v][i] != 0) {
            vertices[curr] = i;
            curr++;
        }

    return vertices;
}

int countConnectedComponents(Graph *g, int u, int *visited) {
    visited[u] = 1;

    int count = 1;
    int *adj = getAdjacencyList(g, u);

    for (register int i = 0; i < countDegree(g, u); i++)
        if (visited[adj[i]] == 0)
            count += countConnectedComponents(g, adj[i], visited);
        
    free(adj);
    return count;
}

void destroyGraph(Graph *g) {
    for (int i = 0; i < g->num_vertices; i++) 
        free(g->vertices[i]);

    free(g->vertices);
    free(g);
}