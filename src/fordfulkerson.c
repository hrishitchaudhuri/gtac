#include<stdio.h>
#include<stdlib.h>

#include"utils/graph.h"
#include"utils/fileread.h"

int getMaxMatchings(int *matches, int n) {
    int count = 0;
    for (register int i = 0; i < n; i++)
        if (matches[i] != -1)
            count++;

    return count;
}

int maxMatching(Graph *g, int v, int M, int N, int *visited, int *matches) {
    for (register int i = M; i < (M + N); i++) {
        if (g->vertices[v][i] && !visited[i - M]) {
            visited[i - M] = 1;

            if ((matches[i - M] == -1) || (maxMatching(g, matches[i - M], M, N, visited, matches))) {
                matches[i - M] = v;
                return 1;
            }
        }
    }

    return 0;
}

int *returnMatchings(Graph *g, int M, int N) {
    int *visited = (int *) malloc(sizeof(int) * N);
    int *matches = (int *) malloc(sizeof(int) * N);

    for (register int i = 0; i < N; i++)
        matches[i] = -1;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            visited[j] = 0;
        maxMatching(g, i, M, N, visited, matches);
    }
    return matches;
}

int main() {
    FILE *fptr = fopen("../inputs/graph_bipartite.txt", "r");
    int bpm, bpn;

    fscanf(fptr, "%d %d\n", &bpm, &bpn);
    fclose(fptr);

    Graph *g = readBipartiteFile("../inputs/graph_bipartite.txt");

    int *matches = returnMatchings(g, bpm, bpn);

    for (register int i = bpm; i < bpm + bpn; i++)
        if (matches[i - bpm] != -1)
            printf("<%d -> %d>\n", i, matches[i - bpm]);


    printf("Total number of assignments: %d\n", getMaxMatchings(matches, bpn));

    return 0;
}