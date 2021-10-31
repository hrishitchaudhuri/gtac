typedef struct disjoint_set {
    int parent;
    int cost;
} Set;

int disjointSetFind(Set *subsets, int i);
void disjointSetUnion(Set *subsets, int v1, int v2);
