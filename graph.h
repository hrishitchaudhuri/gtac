typedef struct Graph {
    int **vertices;
    int num_vertices;
} Graph;

void addUnweightedUndirectedGraphEdge(Graph *g, int v1, int v2);
void addWeightedUndirectedGraphEdge(Graph *g, int v1, int v2, int cost);
void deleteUndirectedGraphEdge(Graph *g, int v1, int v2);

int countDegree(Graph *g, int v);
int countEdges(Graph *g);
int getSolitaryVertex(Graph *g, int v);
int *getAdjacencyList(Graph *g, int v);
int countConnectedComponents(Graph *g, int u, int *visited);
