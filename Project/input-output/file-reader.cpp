//
// Created by Ponanoix on 04.06.2023.
//

#include "file-reader.h"
#include <iostream>
#include <vector>

int FileReader::readNextVal() {
    int nextVal;
    if(input.is_open()){
        input >> nextVal;
        if(input.fail()){
            throw runtime_error("File error - stopping program");
        }
        if(input.eof()){
            input.close();
        }
        return nextVal;
    }
    throw runtime_error("File not opened - perhaps it was already closed?");
}

void FileReader::showData() const {
    cout<<"Edges: "<<edgeSize<<", Vertices: "<<vertexSize<<endl;
}

FileReader::FileReader(const string &fileName) : fileName(fileName), input(fileName){
    input >> edgeSize;
    input >> vertexSize;
    if(!input.is_open()){
        throw runtime_error("Could not read the file");
    }
}

int FileReader::getStructureSize() const {
    return edgeSize;
}

void FileReader::readToAdjList(ListRepresentation *graph) {
    graph -> setEdgeSize(edgeSize);
    graph -> setVertexSize(vertexSize);
    int from, to, weight;
    for(int i = 0; i < edgeSize; i++){
        from = readNextVal();
        to = readNextVal();
        weight = readNextVal();
        graph -> addConnection(from, to, weight);
    }
    graph -> print();
}

void FileReader::readToIncMatrix(MatrixRepresentation *graph) {
    graph -> setEdgeSize(edgeSize);
    graph -> setVertexSize(vertexSize);
    int from, to, weight;
    int *begins = new int[edgeSize];
    int *ends = new int[edgeSize];
    for(int i = 0; i < edgeSize; i++){
        from = readNextVal();
        to = readNextVal();
        weight = readNextVal();
        graph -> addConnection(from, to, weight);
        begins[i] = from;
        ends[i] = to;
    }
    graph -> print(begins, ends);
    delete[] begins;
    delete[] ends;
}
