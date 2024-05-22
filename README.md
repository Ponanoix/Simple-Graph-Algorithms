# Simple-Graph-Algorithms
Five algorithms used to compute three basic graph problems

The program is capable of solving three graph problems (problem - algorithms)
1. Minimum Spanning Tree Problem (MST):
- Prim's algorithm
- Kruskal's algorithm
2. Shortest Path Problem
- Dijkstra's algorithm
- Bellman-Ford's algorithm
3. Maximum Flow Problem
- Ford-Fulkerson's algorithm

The program has two options:
- Start benchmarking based on a command in main.cpp and save results to a .csv file
- Load data from a .txt file and let the user choose one of the algorithms to solve the adequate problem

The program shows the graph in two ways:
- A list
- An adjacency matrix

The data file needs to be written in the following format:
[Number of edges] [Number of vertices]
[Starting vertex] [Ending Vertex] [Weight]
[...]

For example:

10 7
0 1 4
0 3 8
1 2 8
1 3 11
2 4 2
2 5 4
3 4 7
3 6 8
4 6 6
5 6 2

The program is also capable of generating a random graph
