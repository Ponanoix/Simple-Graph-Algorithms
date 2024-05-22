//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_DIJKSTRA_MATRIX_H
#define SDIZO2_DIJKSTRA_MATRIX_H

#include "../../graph-representations/matrix-representation.h"

class DijkstraMatrix: public MatrixRepresentation{
private:

    int findMin(const int *shortestPath, const bool *isIncluded);       // Finds next min vertex from not yet processed nodes.

public:

    DijkstraMatrix(int vertexSize, int edgeSize, int startVertex) : MatrixRepresentation(vertexSize, edgeSize, startVertex, 0, true){};     // Creates a new graph

    void start() override;                                              // Starts Dijkstra algorithm

    void compare(const int *begin, const int *end);                     // Compares found edges with graph's edges

    void assignVertices(int startVertex, int endVertex);                // Assigns entered vertices their roles
};

#endif //SDIZO2_DIJKSTRA_MATRIX_H
