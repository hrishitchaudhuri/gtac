#include<stdio.h>
#include<stdlib.h>

#include"disjoint_set.h"

int disjointSetFind(Set *subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = disjointSetFind(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void disjointSetUnion(Set *subsets, int v1, int v2) {
    int root1 = disjointSetFind(subsets, v1);
    int root2 = disjointSetFind(subsets, v2);

    if (subsets[root1].cost < subsets[root2].cost)
        subsets[root1].parent = root2;

    else if (subsets[root1].cost > subsets[root2].cost) 
        subsets[root2].parent = root1;

    else {
        subsets[root2].parent = root1;
        subsets[root1].cost++;
    }
}