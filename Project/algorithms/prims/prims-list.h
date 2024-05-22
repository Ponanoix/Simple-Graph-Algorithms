//
// Created by Ponanoix on 19.05.2023.
//

#ifndef SDIZO2_PRIMS_LIST_H
#define SDIZO2_PRIMS_LIST_H

#include "../../graph-representations/list-representation.h"

class PrimsList: public ListRepresentation{                         // Prims graph algorithm (list)

    int findMin(const int pathCost[], const bool isIncluded[]);     // Finds next vertex with min value

public:

    PrimsList(int vertexSize, int edgeSize) : ListRepresentation(vertexSize, edgeSize, 0, 0, false){};  // Creates new graph

    void start() override;                                          // Starts Prims algorithm

    void seekErrors();                                              // Searches for any pre-existing obstacles

};

#endif //SDIZO2_PRIMS_LIST_H
