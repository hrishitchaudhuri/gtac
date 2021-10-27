#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"dijkstra_mod.h"
#include"graph.h"
#include"dijkstra.h"


typedef struct pair {
    int v1;
    int v2;
} Pair;

int *getOddVertices(Graph *g) {
    int *isOdd = (int *) malloc(sizeof(int) * g->num_vertices);
    int oddCount = 0;

    for (register int i = 0; i < g->num_vertices; i++) {
        isOdd[i] = 0;
        if (countDegree(g, i) % 2) {
            isOdd[i] = 1;
            oddCount++;
        }
    }

    int *oddVertices = (int *) malloc(sizeof(int) * oddCount);
    int curr = 0;

    for (register int i = 0; i < g->num_vertices; i++)
        if (isOdd[i]) {
            oddVertices[curr] = i;
            curr++;
        }

    free(isOdd);
    return oddVertices;
}

int getLength(Graph *g, int *route, int src) {
    int sum = 0;
    int pred = src;
    for (register int i = 1; i <= route[0]; i++) {
        sum += g->vertices[pred][i];
        pred = i;
    }

    return sum;
}

int *getPostmanRoute(Graph *g) {
    int *oddVertices = getOddVertices(g);
    int oddCount = 0;

    for (register int i = 0; i < g->num_vertices; i++)
        if (countDegree(g, i) % 2)
            oddCount++;

    /*int pairCount = pow(2, oddCount);

    Pair *pairings = (Pair *) malloc(sizeof(Pair) * pairCount);

    int pc = 0;
    for (register int i = 0; i < oddCount; i++)
        for (register int j = 0; j < oddCount; j++) {
            pairings[pc].v1 = oddVertices[i];
            pairings[pc].v2 = oddVertices[j];

            pc++;
        }*/

    // gNode **ls = convertToAdjList(g);
    // display(ls, g->num_vertices);
    int *route;

    int min = 99999999, curr;
    int v1 = -1, v2 = -1;

    int pred, v;

    for (register int i = 0; i < oddCount; i++) {
        for (register int j = 0; j < oddCount; j++) {
            route = dijkstra_new(g, oddVertices[i], oddVertices[j]);
            printf("<%d, %d> : ", oddVertices[i], oddVertices[j]);
            for (register int k = 0; k < g->num_vertices; k++) 
                printf("%d ", route[k]);
            printf("\n");

            v = oddVertices[j];
            curr = 0;
            pred = route[oddVertices[j]];
            while (pred != -1) {
                curr += g->vertices[v][pred];
                v = pred;
                pred = route[v];
            }
            printf("LEN: %d\n", curr);
            
            if ((curr > 0) && (curr < min)) {
                min = curr;
                v1 = oddVertices[i];
                v2 = oddVertices[j];
            }
        }
    }

    printf("%d %d\n", v1, v2);
    route = dijkstra_new(g, v1, v2);
    return route;
}

int main() {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->num_vertices = 8;
    g->vertices = (int **) malloc(sizeof(int *) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        g->vertices[i] = (int *) malloc(sizeof(int) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        for (int j = 0; j < g->num_vertices; j++)
            g->vertices[i][j] = 0; 

    addWeightedUndirectedGraphEdge(g, 0, 1, 5);
    addWeightedUndirectedGraphEdge(g, 0, 2, 6);
    addWeightedUndirectedGraphEdge(g, 1, 3, 7);
    addWeightedUndirectedGraphEdge(g, 1, 4, 8);
    addWeightedUndirectedGraphEdge(g, 2, 3, 5);
    addWeightedUndirectedGraphEdge(g, 2, 4, 6);
    addWeightedUndirectedGraphEdge(g, 3, 5, 8);
    addWeightedUndirectedGraphEdge(g, 3, 6, 9);
    addWeightedUndirectedGraphEdge(g, 4, 5, 6);
    addWeightedUndirectedGraphEdge(g, 4, 6, 7);
    addWeightedUndirectedGraphEdge(g, 5, 7, 13);
    addWeightedUndirectedGraphEdge(g, 6, 7, 11);

    int *postman = getPostmanRoute(g);

    return 0;
}