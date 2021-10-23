#include<stdio.h>
#include<stdlib.h>

#include"graph.h"

int isNotBridge(Graph *g, int v, int u) {
    int pre_connections, post_connections;
    int *visited = (int *) malloc(sizeof(int) * g->num_vertices);

    deleteUndirectedGraphEdge(g, v, u);
    for (register int i = 0; i < g->num_vertices; i++)
        visited[i] = 0;
    post_connections = countConnectedComponents(g, u, visited);

    addUnweightedUndirectedGraphEdge(g, v, u);
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
            deleteUndirectedGraphEdge(g, v, v_new);
            getEulerCircuit(g, v_new);
            return;
        }
    }

    int *adj_list = getAdjacencyList(g, v);

    for (register int i = 0; i < degree; i++) {
        if (isNotBridge(g, v, adj_list[i])) {
            deleteUndirectedGraphEdge(g, v, adj_list[i]);
            getEulerCircuit(g, adj_list[i]);

            free(adj_list);
            return;
        }
    }
}

void getEuler(Graph *g) {
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
    g->vertices = (int **) malloc(sizeof(int *) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        g->vertices[i] = (int *) malloc(sizeof(int) * g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) 
        for (int j = 0; j < g->num_vertices; j++)
            g->vertices[i][j] = 0; 

    addUnweightedUndirectedGraphEdge(g, 0, 1);
    addUnweightedUndirectedGraphEdge(g, 0, 2);
    addUnweightedUndirectedGraphEdge(g, 0, 3);
    addUnweightedUndirectedGraphEdge(g, 0, 5);
    addUnweightedUndirectedGraphEdge(g, 1, 2);
    addUnweightedUndirectedGraphEdge(g, 1, 4);
    addUnweightedUndirectedGraphEdge(g, 1, 6);
    addUnweightedUndirectedGraphEdge(g, 4, 5);
    addUnweightedUndirectedGraphEdge(g, 5, 6);

    getEuler(g);

    for (int i = 0; i < g->num_vertices; i++) 
        free(g->vertices[i]);

    free(g->vertices);
    free(g);

    return 0;
}