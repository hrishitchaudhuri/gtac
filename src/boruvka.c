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


int main() {
    Graph *g = readFile("../inputs/graph_mst.txt");

    Graph *mst = BoruvkaMST(g);

    for (int i = 0; i < mst->num_vertices; i++) {
        for (int j = 0; j < mst->num_vertices; j++)
            printf("%d ", mst->vertices[i][j]); 
        printf("\n");
    }

    destroyGraph(mst);

    destroyGraph(g);
    return 0;
}