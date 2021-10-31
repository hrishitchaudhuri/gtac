#include<stdio.h>
#include<stdlib.h>

#include"utils/graph.h"
#include"utils/fileread.h"

int isUncoloured(int *colours, int n) {
    for (register int i = 0; i < n; i++)
        if (colours[i] == -1)
            return 1;
    return 0;
}

int inList(int *ls, int v, int n) {
    for (register int i = 0; i < n; i++)
        if (ls[i] == v) 
            return 1;

    return 0;
}

void colourIndependentVertices(Graph *g, int v, int colour, int *colours) {
    colours[v] = colour;

    int *adj = getAdjacencyList(g, v);
    int *adj_temp;
    int deg = countDegree(g, v);

    for (register int i = 0; i < g->num_vertices; i++)
        if ((colours[i] == -1) && (!inList(adj, i, deg))) {
            colours[i] = colour;

            adj = (int *) realloc(adj, sizeof(int) * (deg + countDegree(g, i)));

            adj_temp = getAdjacencyList(g, i);

            for (register int j = 0; j < countDegree(g, i); j++)
                adj[j + deg] = adj_temp[j];

            deg += countDegree(g, i);
            free(adj_temp);
        }

    free(adj);
}

int *WelshPowellColouring(Graph *g) {
    int *colours = (int *) malloc(sizeof(int) * g->num_vertices);
    for (register int i = 0; i < g->num_vertices; i++)
        colours[i] = -1; 

    int *degrees = (int *) malloc(sizeof(int) * g->num_vertices);
    for (register int i = 0; i < g->num_vertices; i++)
        degrees[i] = countDegree(g, i); 

    int max, curr, colour = 0;
    while (isUncoloured(colours, g->num_vertices)) {
        max = -1;
        for (register int i = 0; i < g->num_vertices; i++)
            if ((degrees[i] > max) && (colours[i] == -1)) {
                max = degrees[i];
                curr = i;
            }
        
        degrees[curr] = -1;

        colourIndependentVertices(g, curr, colour, colours);
        colour++;
    }

    free(degrees);

    return colours;
}

int main() {
    Graph *g = readFile("../inputs/graph_wpc.txt");

    int *colours = WelshPowellColouring(g);

    for (int i = 0; i < g->num_vertices; i++) 
        printf("%d ", colours[i]);

    printf("\n");

    for (int i = 0; i < g->num_vertices; i++) 
        free(g->vertices[i]);

    free(g->vertices);
    free(colours);
    free(g);

    return 0;
}