# Graph Theory Assignment 1

```
@author: Hrishit Chaudhuri (PES1UG19CS187)
```

To generate the executables, please run `make`. The input files will be read automatically by each executable when running them.  

### Repository Structure
```
|--bin
|--src
    |--broken
    |--scripts
    |--utils
|--inputs
|--outputs
```

### Binary Executables
A total of six binary executables will be generated on running `make`. The executables will print output onto `STDOUT`, which can be redirected only using the UNIX `>` operator. To modify input to the algorithms, the input file corresponding to the algorithm must be edited.   
  
The binary executables generated are `fleury` (which runs Fleury's algorithm for detecting Euler paths), `boruvka` (which runs Boruvka's minimum-spanning tree algorithm), `wpc` (which runs Welsh-Powell colouring), `revdel` (which runs the reverse-delete algorithm for minimum-spanning trees), `fordfulk` (which runs maximum matching on bipartite graphs), and `tarjan` (which runs Tarjan's algorithm for finding articulation points).  
  
`fleury` outputs a vector denoting the vertices in the corresponding Euler path.  
`boruvka` and `revdel` output an adjacency matrix corresponding to the minimum spanning tree.  
`wpc` outputs a vector denoting the colours assigned to each vertex.  
`fordfulk` outputs a set of tuples denoting assignments, as well as the total number of maximum assignments.  
`tarjan` outputs a vector denoting all vertices which are articulation points of the graph.  


### Inputs and Outputs
Inputs are provided via the corresponding input file for each algorithm. 
```
graph_fleury.txt => fleury
graph_mst.txt => boruvka, revdel
graph_tarjan.txt => tarjan
graph_wpc.txt => wpc
graph_bipartite.txt => fordfulk
```
The input file format is as follows: for non-bipartite graphs, the first line denotes `N`, the number of vertices, followed by the adjacency matrix representation of the graph. For bipartite graphs, the first line is of the form `M N`, where M and N denote the cardinality of each of the vertex partitions. This is also followed by the adjacency matrix representation of the graph.  
  
The sample inputs provided have been recorded as outputs in the `outputs` folder using a similar naming scheme. 

### Source Code
The `broken` folder contains code for the unsuccessful implementation of the Chinese postman problem. This should largely be ignored.  
  
The `utils` folder contains helper functions and useful data structures. The `graph.h` header file contains relevant graph functions, such as functions for inserting edges, counting degree, and counting connected componens. Similarly, the `disjoint_set.h` header file defines useful functions on the disjoint set data structure such as union-find algorithms, while the `fileread.h` header file contains useful information for parsing the input files. 

Finally, the following six algorithms have been implemented in their respective source files. They have been provided along with their function signatures below:
```
fleury.c: Implements Fleury's algorithm 
  void getEuler(Graph *g); // Prints the Euler path to the given graph onto STDOUT
  
welsh_powell.c: Implements Welsh-Powell colouring
  int *WelshPowellColouring(Graph *g); // Returns colour array for given graph's vertices
  
tarjan.c: Implements Tarjan's algorithm for detecting articulation points
  int *Tarjan(Graph *g); // Returns Boolean array of vertices denoting whether each vertex is an AP or not
  
fordfulkerson.c: Implements maximum bipartite matching
  int *returnMatchings(Graph *g, int M, int N); // Returns array of vertices where each entry corresponds to assignment
  
reverse_delete.c: Implements the reverse-delete algorithm
  Graph *reverseDeleteMST(Graph *g); // Returns graph corresponding to MST of input graph
  
boruvka.c: Implements Boruvka's algorithm
  Graph *BoruvkaMST(Graph *g); // Returns graph corresponding to MST of input graph
```


### Scripts
Finally, the `src/scripts` folder contains the generator scripts for the sample input files. The graphs have been generated using the `networkx` library in Python. The unweighted undirected graph used to demonstrate Welsh-Powell colouring was generated using the Barabasi-Albert model for scale-free networks using an initial number of 2 nodes. The weighted undirected graph used by the MST algorithms was generated by first generating a Barabasi-Albert graph and then randomly choosing weights between 1 and 10 for each of its edges. For Fleury's algorithm, a Barabasi-Albert graph was Eulerized and represented as a multigraph. The bipartite graph was generated randomly, with each edge being given a probability of 0.4 for existing. Finally, Tarjan's algorithm was verified using a special barbell graph, since articulation points must be a contiguous path of verties within a barbell graph. 
