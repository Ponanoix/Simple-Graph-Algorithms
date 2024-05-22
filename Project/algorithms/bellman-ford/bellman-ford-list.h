//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_BELLMAN_FORD_LIST_H
#define SDIZO2_BELLMAN_FORD_LIST_H

#include "../../graph-representations/list-representation.h"

class BellmanFordList: public ListRepresentation{
private:

    static void printPath(const int *parent, int vert);     // Traverses and prints the path

    void printResult(int *parent, int *shortestPath);       // Prints the algorithm's results

public:

    BellmanFordList(int vertexSize, int edgeSize, int startVertex) : ListRepresentation(vertexSize, edgeSize, startVertex, 0, true){};

    void start() override;                                  // Starts Bellman-Ford algorithm

    void assignVertices(int startVertex);                   // Assigns entered vertices their roles

};

#endif //SDIZO2_BELLMAN_FORD_LIST_H
