//
// Created by Ponanoix on 04.06.2023.
//

#ifndef SDIZO2_FILE_READER_H
#define SDIZO2_FILE_READER_H

#include<fstream>
#include<iostream>
#include "../graph-representations/matrix-representation.h"
#include "../algorithms/prims/prims-list.h"
#include "../algorithms/prims/prims-matrix.h"
#include "../algorithms/kruskal/kruskal-list.h"
#include "../algorithms/kruskal/kruskal-matrix.h"
#include "../algorithms/ford-fulkerson/ford-fulkerson-list.h"
#include "../algorithms/ford-fulkerson/ford-fulkerson-matrix.h"
#include "../algorithms/dijkstra/dijkstra-list.h"
#include "../algorithms/dijkstra/dijkstra-matrix.h"
#include "../algorithms/bellman-ford/bellman-ford-list.h"
#include "../algorithms/bellman-ford/bellman-ford-matrix.h"

using namespace std;

class FileReader{           // This class helps to read int data from files and creating graphs from them
private:
    string fileName;        // Name of the input file

    ifstream input;         // File input stream

    int edgeSize = 0;       // Number of edges the graph has

    int vertexSize = 0;     // Number of vertices this graph has

    int startVertex = 0;    // Graph's starting vertex

    int endVertex = 0;      // Graph's ending vertex

    int readNextVal();      // Returns the next value from the file
public:
    explicit FileReader(const string &fileName);        // Creates new instance of this class with name of the file to read from

    void readToAdjList(ListRepresentation *graph);      // Reads data to a graph structure

    void readToIncMatrix(MatrixRepresentation *graph);  // Loads data and prints the matrix representation

    void showData() const;                                    // Shows data of the graph

    int getStructureSize() const;                       // Returns the number of items stored in input file
};

#endif //SDIZO2_FILE_READER_H
