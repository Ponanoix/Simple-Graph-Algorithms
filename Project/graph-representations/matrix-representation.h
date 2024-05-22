//
// Created by Ponanoix on 02.06.2023.
//

#ifndef SDIZO2_MATRIX_REPRESENTATION_H
#define SDIZO2_MATRIX_REPRESENTATION_H

class MatrixRepresentation{
protected:
    int **incidenceMatrix;      // Incidence matrix

    int vertexSize;             // Number of vertices in the graph

    int edgeSize;               // Number of edges in the graph

    int startVertex;            // Graph's starting vertex

    int endVertex;              // Graph's ending vertex

    int currentEdgeSize = 0;    // Current number of edges in the graph

    bool isDirected;            // Checks whether the matrix is directed
public:
    MatrixRepresentation(int vertexSize, int edgeSize, int startVertex, int endVertex, bool isDirected);        // Constructor

    bool isPrintOut = true;                                                                                     // Should the results be printed on the screen

    virtual void addConnection(int begin, int end, int weight);                                                 // Adds new connection/edge to the graph

    int **getIncidenceMatrix();                                                                                 // Returns incidence matrix

    void print(const int *begin, const int *end) const;                                                         // Displays the whole matrix representation of this graph

    virtual void start(){};                                                                                     // Starts algorithm for derived classes

    void setStartingVertex(int v);                                                                              // Sets starting vertex of the graph

    void setEndingVertex(int v);                                                                                // Sets ending vertex of the graph

    void setVertexSize(int n);                                                                                  // Sets vertex size of the graph. COMPLETELY CLEARS GRAPH DATA

    void setEdgeSize(int n);                                                                                    // Sets edge size of the graph

    void clone(MatrixRepresentation *representation);                                                           // Clones the graph's data

    [[nodiscard]] bool getIsDirected() const {return isDirected;};                                              // Gets the value of isDirected function
};

#endif //SDIZO2_MATRIX_REPRESENTATION_H
