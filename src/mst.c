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

Graph *BoruvkaMST(Graph *g) {
    Graph *mst = (Graph *) malloc(sizeof(Graph));
    mst->num_vertices = g->num_vertices;
    mst->vertices = (int **) malloc(sizeof(int *) * mst->num_vertices);

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

    int *min_edges = (int *) malloc(sizeof(int) * mst->num_vertices);

    for (register int i = 0; i < mst->num_vertices; i++) 
        mst->vertices[i] = (int *) malloc(sizeof(int) * mst->num_vertices);

    for (register int i = 0; i < mst->num_vertices; i++) 
        for (register int j = 0; j < mst->num_vertices; j++)
            mst->vertices[i][j] = 0; 

    int connected_components = mst->num_vertices;
    Set *subsets = (Set *) malloc(sizeof(Set) * mst->num_vertices);

    for (register int i = 0; i < mst->num_vertices; i++) {
        subsets[i].parent = i;
        subsets[i].cost = 0;
        min_edges[i] = -1;
    }

    int c1, c2;

    while (connected_components > 1) {
        for (register int i = 0; i < mst->num_vertices; i++) 
            min_edges[i] = -1;

        for (register int i = 0; i < edge_count; i++) {
            c1 = disjointSetFind(subsets, edges[i].src);
            c2 = disjointSetFind(subsets, edges[i].dest);

            if (c1 != c2) {
                if ((min_edges[c1] == -1) || (edges[min_edges[c1]].cost > edges[i].cost))
                    min_edges[c1] = i;

                if ((min_edges[c1] == -1) || (edges[min_edges[c2]].cost > edges[i].cost))
                    min_edges[c2] = i;
            }
        }

        /*for (register int i = 0; i < mst->num_vertices; i++) {
            if (min_edges[i] != -1) {
                c1 = disjointSetFind(subsets, edges[min_edges[i]].src);
                c2 = disjointSetFind(subsets, edges[min_edges[i]].dest);

                if (c1 != c2) {
                    addWeightedUndirectedGraphEdge(mst, edges[min_edges[i]].src, edges[min_edges[i]].dest, edges[min_edges[i]].cost);
                    disjointSetUnion(subsets, c1, c2);

                    connected_components--;
                }
            }
        }*/

        for (register int i = 0; i < edge_count; i++) {
            c1 = disjointSetFind(subsets, edges[i].src);
            c2 = disjointSetFind(subsets, edges[i].dest);

            if ((c1 != c2) && (min_edges[c1] == i || min_edges[c2] == i)) {
                addWeightedUndirectedGraphEdge(mst, edges[i].src, edges[i].dest, edges[i].cost);
                disjointSetUnion(subsets, c1, c2);

                connected_components--;
            }
        }
    }

    return mst;
}

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
    Graph *g = readFile("inputs/graph_mst.txt");

    Graph *mst = reverseDeleteMST(g);

    for (int i = 0; i < mst->num_vertices; i++) {
        for (int j = 0; j < mst->num_vertices; j++)
            printf("%d ", mst->vertices[i][j]); 
        printf("\n");
    }

    destroyGraph(mst);

    /*Graph *mst = BoruvkaMST(g);

    for (int i = 0; i < mst->num_vertices; i++) {
        for (int j = 0; j < mst->num_vertices; j++)
            printf("%d ", mst->vertices[i][j]); 
        printf("\n");
    }

    destroyGraph(mst);*/

    destroyGraph(g);
    return 0;
}