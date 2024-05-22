//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_FORD_FULKERSON_MATRIX_H
#define SDIZO2_FORD_FULKERSON_MATRIX_H

#include "../../graph-representations/matrix-representation.h"

class FordFulkersonMatrix: public MatrixRepresentation{
private:
    bool bfs(int *parent);                                              // Uses BFS algorithm to find path from s to t

    int **residualGraph;                                                // A pointer to a 2D array of objects, which represents the residual graph
public:
    FordFulkersonMatrix(int vertexSize, int edgeSize, int startVertex, int endVertex) : MatrixRepresentation(vertexSize, edgeSize, startVertex, endVertex, true) {};    // Creates a new graph

    void start() override;                                              // Starts the Ford-Fulkerson algorithm

    void assignVertices(int startVertex, int endVertex);                // Assigns entered vertices their roles

    void compare(const int *begin, const int *end);                     // Compares found edges with graph's edges

    void print(int *begin, const int *end);                             // Prints Ford-Fulkerson's graph

};

#endif //SDIZO2_FORD_FULKERSON_MATRIX_H
