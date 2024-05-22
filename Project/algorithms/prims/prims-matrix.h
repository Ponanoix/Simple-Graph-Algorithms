//
// Created by Ponanoix on 02.06.2023.
//

#ifndef SDIZO2_PRIMS_MATRIX_H
#define SDIZO2_PRIMS_MATRIX_H

#include <vector>
#include "../../graph-representations/matrix-representation.h"

class PrimsMatrix: public MatrixRepresentation{                     // Prims algorithm incidence matrix implementation

    int findMin(const int pathCost[], const bool isIncluded[]);     // Finds next vertex with min value
public:
    PrimsMatrix(int vertexSize, int edgeSize) : MatrixRepresentation(vertexSize, edgeSize, 0, 0, false){};      // Creates a new graph

    void start() override;                                          // Starts Prims algorithm

    void compare(const int *begin, const int *end);                 // Compares found edges with graph's edges
};

#endif //SDIZO2_PRIMS_MATRIX_H
