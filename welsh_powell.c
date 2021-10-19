#include<stdio.h>
#include<stdlib.h>

typedef struct Graph {
    int **vertices;
    int num_vertices;
} Graph;

void addGraphEdge(Graph *g, int v1, int v2) {
    g->vertices[v1][v2] = 1;
    g->vertices[v2][v1] = 1;
}

void deleteGraphEdge(Graph *g, int v1, int v2) {
    g->vertices[v1][v2] = 0;
    g->vertices[v2][v1] = 0;
}

int countDegree(Graph *g, int v) {
    int count = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        if (g->vertices[v][i] == 1)
            count++;
    
    return count;
}

int isUncoloured(int *colours, int n) {
    for (register int i = 0; i < n; i++)
        if (colours[i] == -1)
            return 1;
    return 0;
}

int *getAdjacencyList(Graph *g, int v) {
    int *vertices = (int *) malloc(sizeof(int) * countDegree(g, v));

    int curr = 0;
    for (register int i = 0; i < g->num_vertices; i++)
        if (g->vertices[v][i] == 1) {
            vertices[curr] = i;
            curr++;
        }

    return vertices;
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
    // WPC returns an array of ints representing unique colours

    int *colours = (int *) malloc(sizeof(int) * g->num_vertices);
    for (register int i = 0; i < g->num_vertices; i++)
        colours[i] = -1; // Initialization of colour vector

    int *degrees = (int *) malloc(sizeof(int) * g->num_vertices);
    for (register int i = 0; i < g->num_vertices; i++)
        degrees[i] = countDegree(g, i); // Initialization of degree vector

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
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->num_vertices = 11;
    g->vertices = (int **) malloc(sizeof(int *) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        g->vertices[i] = (int *) malloc(sizeof(int) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        for (int j = 0; j < g->num_vertices; j++)
            g->vertices[i][j] = 0; 

    addGraphEdge(g, 0, 1);
    addGraphEdge(g, 0, 7);
    addGraphEdge(g, 1, 3);
    addGraphEdge(g, 2, 3);
    addGraphEdge(g, 3, 8);
    addGraphEdge(g, 3, 10);
    addGraphEdge(g, 4, 5);
    addGraphEdge(g, 4, 10);
    addGraphEdge(g, 5, 6);
    addGraphEdge(g, 6, 7);
    addGraphEdge(g, 6, 10);
    addGraphEdge(g, 7, 8);
    addGraphEdge(g, 7, 9);
    addGraphEdge(g, 7, 10);
    addGraphEdge(g, 8, 9);
    addGraphEdge(g, 9, 10);

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