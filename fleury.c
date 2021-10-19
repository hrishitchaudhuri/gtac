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
        if (g->vertices[v][i] == 1) {
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
        
    return count;
}

int isNotBridge(Graph *g, int v, int u) {
    int pre_connections, post_connections;
    int *visited = (int *) malloc(sizeof(int) * g->num_vertices);

    deleteGraphEdge(g, v, u);
    for (register int i = 0; i < g->num_vertices; i++)
        visited[i] = 0;
    post_connections = countConnectedComponents(g, u, visited);

    addGraphEdge(g, v, u);
    for (register int i = 0; i < g->num_vertices; i++)
        visited[i] = 0;
    pre_connections = countConnectedComponents(g, u, visited);

    free(visited);
    if (pre_connections == post_connections)
        return 1;
    else return 0;
}

void getEulerCircuit(Graph *g, int v) {
    printf("%d\n", v);

    int degree = countDegree(g, v);

    if (degree == 0)
        return;

    if (degree == 1) {
        int v_new = getSolitaryVertex(g, v);
        if (v_new != -1) {
            deleteGraphEdge(g, v, v_new);
            getEulerCircuit(g, v_new);
            return;
        }
    }

    int *adj_list = getAdjacencyList(g, v);

    for (register int i = 0; i < degree; i++) {
        if (isNotBridge(g, v, adj_list[i])) {
            deleteGraphEdge(g, v, adj_list[i]);
            getEulerCircuit(g, adj_list[i]);
            return;
        }
    }
}

void runEuler(Graph *g) {
    int count_odd_del = 0;
    int odd_vertex = -1;

    for (register int i = 0; i < g->num_vertices; i++) {
        if (countDegree(g, i) % 2 == 1) {
            count_odd_del++;
            odd_vertex = i;
        }
    }

    if (count_odd_del == 0)
        getEulerCircuit(g, 0);

    else if (count_odd_del == 2)
        getEulerCircuit(g, odd_vertex);

    else printf("-1\n");
}

int main() {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->num_vertices = 7;
    g->vertices = (int **) malloc(sizeof(int *) * 7);

    for (int i = 0; i < 7; i++) 
        g->vertices[i] = (int *) malloc(sizeof(int) * 7);

    addGraphEdge(g, 0, 1);
    addGraphEdge(g, 0, 2);
    addGraphEdge(g, 0, 3);
    addGraphEdge(g, 0, 5);
    addGraphEdge(g, 1, 2);
    addGraphEdge(g, 1, 4);
    addGraphEdge(g, 1, 6);
    addGraphEdge(g, 4, 5);
    addGraphEdge(g, 5, 6);

    runEuler(g);

    return 0;
}