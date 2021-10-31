#include<stdio.h>
#include<stdlib.h>

#include"utils/graph.h"
#include"utils/fileread.h"
#include"utils/disjoint_set.h"

typedef struct edge_tuple {
    int src;
    int dest;
    int cost;
} Edge;

void dfs(Graph *g, int *visited, int v) {
    visited[v] = 1;

    int *adj = getAdjacencyList(g, v);
    int deg = countDegree(g, v);

    for (register int i = 0; i < deg; i++)
        if (!visited[adj[i]])
            dfs(g, visited, adj[i]);
}

int isConnected(Graph *g) {
    int *visited = (int *) malloc(sizeof(int) * g->num_vertices);
    for (register int i = 0; i < g->num_vertices; i++)
        visited[i] = 0;

    dfs(g, visited, 0);

    for (register int i = 0; i < g->num_vertices; i++)
        if (visited[i] == 0)
            return 0;

    return 1;
}

void swap(Edge *arr, int i, int j) {
    Edge temp;

    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void ssort(Edge *arr, int sz) {
    register int i, j;
    int min_pointer;

    for (i = 0; i < (sz-1); i++) {
        min_pointer = i;
        for (j = min_pointer + 1; j < sz; j++)
            if (arr[j].cost > arr[min_pointer].cost)
                min_pointer = j;


        if (min_pointer != i)
            swap(arr, min_pointer, i);
    }
}


Graph *reverseDeleteMST(Graph *g) {
    Graph *mst = (Graph *) malloc(sizeof(Graph));
    mst->num_vertices = g->num_vertices;
    mst->vertices = (int **) malloc(sizeof(int *) * mst->num_vertices);

    for (register int i = 0; i < mst->num_vertices; i++) 
        mst->vertices[i] = (int *) malloc(sizeof(int) * mst->num_vertices);

    for (register int i = 0; i < mst->num_vertices; i++) 
        for (register int j = 0; j < mst->num_vertices; j++)
            mst->vertices[i][j] = g->vertices[i][j]; 

    int edge_count = countEdges(g);
    Edge *edges = (Edge *) malloc(sizeof(Edge) * edge_count);

    int temp = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        for (register int j = 0; j < g->num_vertices; j++)
            if (g->vertices[i][j]) {
                edges[temp].cost = g->vertices[i][j];
                edges[temp].src = i;
                edges[temp].dest = j;

                temp++;
            }

    ssort(edges, edge_count);

    int c1, c2;
    for (register int i = 0; i < edge_count; i++) {
        c1 = edges[i].src;
        c2 = edges[i].dest;

        deleteUndirectedGraphEdge(mst, c1, c2);

        if (!isConnected(mst))
            addWeightedUndirectedGraphEdge(mst, c1, c2, edges[i].cost);
    }

    return mst;
}

int main() {
    Graph *g = readFile("../inputs/graph_mst.txt");

    Graph *mst = reverseDeleteMST(g);

    for (int i = 0; i < mst->num_vertices; i++) {
        for (int j = 0; j < mst->num_vertices; j++)
            printf("%d ", mst->vertices[i][j]); 
        printf("\n");
    }

    destroyGraph(mst);

    destroyGraph(g);
    return 0;
}