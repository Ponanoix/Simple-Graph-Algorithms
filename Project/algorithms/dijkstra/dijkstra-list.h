//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_DIJKSTRA_LIST_H
#define SDIZO2_DIJKSTRA_LIST_H

#include "../../graph-representations/list-representation.h"

class DijkstraList: public ListRepresentation{
private:

    int findMin(const int *shortestPath, const bool *isIncluded);       // Finds next min vertex from not yet processed nodes

    static void printPath(const int *parent, int vertex);               // Traverses and prints the path

public:

    DijkstraList(int vertexSize, int edgeSize, int startVertex) : ListRepresentation(vertexSize, edgeSize, startVertex, 0, true){};     // Creates a new graph

    void start() override;                                              // Starts Dijkstra algorithm

    void seekErrors();                                                  // Searches for any pre-existing obstacles

    void assignVertices(int startVertex, int endVertex);                // Assigns entered vertices their roles

};

#endif //SDIZO2_DIJKSTRA_LIST_H
