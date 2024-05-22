//
// Created by Ponanoix on 02.06.2023.
//

#include<stdexcept>
#include<iostream>
#include "matrix-representation.h"

using namespace std;

MatrixRepresentation::MatrixRepresentation(int vertexSize, int edgeSize, int startVertex, int endVertex,
                                           bool isDirected) : vertexSize(vertexSize), edgeSize(edgeSize), startVertex(startVertex), endVertex(endVertex), isDirected(isDirected) {
    incidenceMatrix = new int *[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        incidenceMatrix[i] = new int[vertexSize];
        for(int j = 0; j < vertexSize; j++){
            incidenceMatrix[i][j] = 0;
        }
    }
}

void MatrixRepresentation::addConnection(int begin, int end, int weight) {
    if (isDirected) {
        if (begin < 0 || begin > vertexSize || end < 0 || end > vertexSize)
            throw std::invalid_argument("Invalid vertices were passed");
        if ((incidenceMatrix[begin][end] == 0 && weight != 0 && currentEdgeSize + 1 > edgeSize))
            throw std::logic_error("Graph is already completed. Cannot add more edges");
        if (incidenceMatrix[begin][end] == 0 && weight != 0) {
            currentEdgeSize++;
        }
        if (incidenceMatrix[begin][end] != 0 && weight == 0) currentEdgeSize--;
        incidenceMatrix[begin][end] = weight;
    } else {
        if (begin < 0 || begin > vertexSize || end < 0 || end > vertexSize)
            throw std::invalid_argument("Invalid vertices were passed");
        if (incidenceMatrix[begin][end] == 0 && weight != 0 && currentEdgeSize + 1 > edgeSize)
            throw std::logic_error("Graph is already completed. Cannot add more edges.");
        if (incidenceMatrix[begin][end] == 0 && weight != 0) currentEdgeSize++;
        if (incidenceMatrix[begin][end] != 0 && weight == 0) currentEdgeSize--;
        incidenceMatrix[begin][end] = weight;
        incidenceMatrix[end][begin] = weight;
    }
}

int **MatrixRepresentation::getIncidenceMatrix() {
    if(currentEdgeSize < edgeSize) throw std::logic_error("Graph was not fully created. Waiting for more edges");
    return this -> incidenceMatrix;
}

void MatrixRepresentation::setEdgeSize(int n) {
    this -> currentEdgeSize = 0;
    this -> edgeSize = n;
}

void MatrixRepresentation::setVertexSize(int n) {
    for (int i = 0; i < vertexSize; i++) {
        delete[] this -> incidenceMatrix[i];
    }
    delete[] this -> incidenceMatrix;
    this -> vertexSize = n;
    incidenceMatrix = new int *[vertexSize];
    for (int i = 0; i < vertexSize; i++) {
        incidenceMatrix[i] = new int[vertexSize];
        for (int j = 0; j < vertexSize; j++) {
            incidenceMatrix[i][j] = 0;
        }
    }
}

void MatrixRepresentation::setEndingVertex(int v) {
    this -> endVertex = v;
}

void MatrixRepresentation::setStartingVertex(int v) {
    this -> startVertex = v;
}

void MatrixRepresentation::print(const int *begin, const int *end) const {
    std::cout<<std::endl;
    std::cout<<"V\\E | ";
    for(int v = 0; v < edgeSize; v++){
        std::cout<<"\t"<<v;
    }
    std::cout<<std::endl;
    std::cout<<"----|-------";
    for(int v2 = 0; v2 < edgeSize; v2++){
        std::cout<<"-------";
    }
    std::cout<<std::endl;
    for(int i = 0; i < vertexSize; i++) {
        std::cout<<" "<<i<<"  |";
        for (int j = 0; j < edgeSize; j++) {
            if(isDirected){
                if(begin[0] == end[0] && begin[0] != -1 && end[0] != -1 && begin[1] == -1 && end[1] == -1){
                    if(begin[0] == i) std::cout <<"\tX";
                    else std::cout << "\t0";
                } else {
                    if (begin[j] == i) std::cout << "\t-1";
                    else if (end[j] == i) std::cout << "\t1";
                    else std::cout << "\t0";
                }
            }
            if(!isDirected){
                if(begin[j] == i || end[j] == i) std::cout << "\t1";
                else std::cout << "\t0";
            }
        }
        std::cout << std::endl;
    }
    if(begin[0] == end[0] && begin[0] != -1 && end[0] != -1 && begin[1] == -1 && end[1] == -1) cout<<"(Single vertex graph. Vertex -> "<<begin[0]<<")";
    std::cout<<std::endl;
    std::cout<<std::endl;
}

void MatrixRepresentation::clone(MatrixRepresentation *representation) {
    setVertexSize(representation -> vertexSize);
    setEdgeSize(representation -> edgeSize);
    startVertex = representation -> startVertex;
    endVertex = representation -> endVertex;
    if (isDirected) {
        for (int i = 0; i < representation -> vertexSize; i++) {
            for (int j = 0; j < representation -> vertexSize; j++) {
                if (representation -> incidenceMatrix[i][j] != 0) {
                    addConnection(i, j, representation -> incidenceMatrix[i][j]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < representation -> vertexSize; i++) {
            for (int j = 0; j < representation -> vertexSize; j++) {
                if (representation -> incidenceMatrix[j][i] != 0) {
                    addConnection(j, i, representation -> incidenceMatrix[j][i]);
                }
            }
        }
    }
}
