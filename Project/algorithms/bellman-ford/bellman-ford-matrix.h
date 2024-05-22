//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_BELLMAN_FORD_MATRIX_H
#define SDIZO2_BELLMAN_FORD_MATRIX_H

#include "../../graph-representations//matrix-representation.h"

class BellmanFordMatrix: public MatrixRepresentation{
private:

    void printPath(const int *parent, int vert, int *begin, int *end, const int *shortestPath);     // Traverses and prints path

    void printResult(int *parent, int *shortestPath);                                               // Prints algorithm's results

public:

    BellmanFordMatrix(int vertexSize, int edgeSize, int startVertex) : MatrixRepresentation(vertexSize, edgeSize, startVertex, 0, true){};  // Creates a new graph

    void start() override;                                                                          // Starts Bellman-Ford algorithm

    void assignVertices(int startVertex);                                                           // Assigns entered vertices their roles

    void compare(const int *begin, const int *end);                                                 // Compares found edges with graph's edges

};

#endif //SDIZO2_BELLMAN_FORD_MATRIX_H
