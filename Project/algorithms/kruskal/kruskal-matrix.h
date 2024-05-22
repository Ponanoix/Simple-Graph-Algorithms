//
// Created by Ponanoix on 02.06.2023.
//

#ifndef SDIZO2_KRUSKAL_MATRIX_H
#define SDIZO2_KRUSKAL_MATRIX_H

#include "../../graph-representations/matrix-representation.h"

class KruskalMatrix: public MatrixRepresentation{               // Kruskal algorithm incidence matrix implementation
private:
    static int find(int i, const int *parent);                  // Find parent of the input vertex

    static void unionVertex(int i, int j, int *parent);         // Connect two groups into one
public:
    KruskalMatrix(int vertexSize, int edgeSize) : MatrixRepresentation(vertexSize, edgeSize, 0, 0, false){};     // Creates a new graph

    void start() override;                                      // Starts Kruskal algorithm

    void compare(const int *begin, const int *end);             // Compares found edges with graph's edges

};

#endif //SDIZO2_KRUSKAL_MATRIX_H
