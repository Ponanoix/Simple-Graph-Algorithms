//
// Created by Ponanoix on 02.06.2023.
//

#ifndef SDIZO2_KRUSKAL_LIST_H
#define SDIZO2_KRUSKAL_LIST_H

#include "../../graph-representations/list-representation.h"

class KruskalList: public ListRepresentation{                       // Kruskal algorithm adjacency list implementation
private:

    static int find(int i, const int *parent);                      // Finds parent of input vertex

    static void unionVertex(int i, int j, int *parent);             // Connects two groups into one

public:

    KruskalList(int vertexSize, int edgeSize) : ListRepresentation(vertexSize, edgeSize, 0, 0, false){};        // Creates a new graph

    void start() override;                                          // Starts Kruskal algorithm

    void seekErrors();                                              // Searches for any pre-existing obstacles

};

#endif //SDIZO2_KRUSKAL_LIST_H
