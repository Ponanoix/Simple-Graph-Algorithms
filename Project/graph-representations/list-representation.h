//
// Created by Ponanoix on 19.05.2023.
//

#ifndef SDIZO2_LIST_REPRESENTATION_H
#define SDIZO2_LIST_REPRESENTATION_H

#include "../utility/adjacency-list.h"

class ListRepresentation{
protected:
    AdjacentList **adjacentLists;       // Adjacent list of this representation

    int vertexSize;                     // Number of vertices in the graph

    int edgeSize;                       // Number of edges in this graph

    int startVertex;                    // Graph's starting vertex

    int endVertex;                      // Graph's ending vertex

    int currentEdgeSize = 0;            // Current number of edges in this graph (must be lower than edgeSize).

    bool isDirected;                    // Checks if the list is directed
public:
    ListRepresentation(int vertexSize, int edgeSize, int startVertex, int endVertex, bool isDirected);

    bool isPrintOut = true;                                                             // Should the results be printed on the screen

    void addConnection(int begin, int end, int weight);                                 // Adds a new connection/edge to this graph

    AdjacentList **getAdjacentLists();                                                  // Returns adjacent matrix

    virtual void start(){};                                                             // Starts algorithm for derived classes

    void setStartingVertex(int v);                                                      // Sets a starting vertex for this graph

    void setEndingVertex(int v);                                                        // Sets an ending vertex for this graph

    void setVertexSize(int n);                                                          // Sets vertex size. COMPLETELY CLEARS GRAPH DATA

    void setEdgeSize(int n);                                                            // Sets edge size of this graph.

    void print();                                                                       // Prints the graph

    void clone(ListRepresentation *representation);                                     // Clones the graph's data

    [[maybe_unused]] [[nodiscard]] bool getIsDirected() const{return isDirected;};      // Gets the value of isDirected function

    bool hasNegativeWeights();                                                          // Returns true if the graph contains negative weights
};

#endif //SDIZO2_LIST_REPRESENTATION_H
