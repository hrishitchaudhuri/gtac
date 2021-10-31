typedef struct Graph {
    int **vertices;
    int num_vertices;
} Graph;

Graph *initGraph(int n);

void addUnweightedUndirectedGraphEdge(Graph *g, int v1, int v2);
void addWeightedUndirectedGraphEdge(Graph *g, int v1, int v2, int cost);
void addUnweightedDirectedGraphEdge(Graph *g, int v1, int v2);
void addUnweightedUndirectedMultigraphEdge(Graph *g, int v, int u);
void deleteUndirectedGraphEdge(Graph *g, int v1, int v2);
void deleteUndirectedMultigraphEdge(Graph *g, int v, int u);

int countDegree(Graph *g, int v);
int countMultigraphDegree(Graph *g, int v);
int countUndirectedEdges(Graph *g);
int countEdges(Graph *g);
int getSolitaryVertex(Graph *g, int v);
int *getAdjacencyList(Graph *g, int v);
int countConnectedComponents(Graph *g, int u, int *visited);

void destroyGraph(Graph *g);
