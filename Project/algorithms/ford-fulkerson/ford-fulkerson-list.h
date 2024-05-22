//
// Created by Ponanoix on 03.06.2023.
//

#ifndef SDIZO2_FORD_FULKERSON_LIST_H
#define SDIZO2_FORD_FULKERSON_LIST_H

#include "../../graph-representations/list-representation.h"

class FordFulkersonList: public ListRepresentation{
private:
    bool bfs(int *parent);                                      // Uses BFS algorithm to find path from s to t

    AdjacentList **residualGraph;                               // A pointer to a 2D array of objects, which represents the residual graph
public:
    FordFulkersonList(int vertexSize, int edgeSize, int startVertex, int endVertex) : ListRepresentation(vertexSize, edgeSize, startVertex, endVertex, true){};         // Creates a new graph

    void start() override;                                      // Starts the Ford-Fulkerson algorithm

    void seekErrors();                                          // Searches for any pre-existing obstacles

    void assignVertices(int startVertex, int endVertex);        // Assigns entered vertices their roles

};

#endif //SDIZO2_FORD_FULKERSON_LIST_H
