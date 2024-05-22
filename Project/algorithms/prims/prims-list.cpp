//
// Created by Ponanoix on 02.06.2023.
//

#include<climits>
#include<iostream>
#include"prims-list.h"

using namespace std;

void PrimsList::seekErrors() {
    for(int i = 0; i < vertexSize; i++){
        if(adjacentLists[i] -> getSize() == 0){
            throw logic_error("The graph is not connected");
        }
    }
    if(isDirected){
        throw logic_error("The graph cannot be directed");
    }
}

void PrimsList::start() {
    int *parent = new int[vertexSize];
    bool *isIncluded = new bool[vertexSize];
    int *pathCost = new int[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        pathCost[i] = INT_MAX;
        isIncluded[i] = false;
    }
    pathCost[0] = 0;
    parent[0] = -1;
    int minCost = 0;
    for(int i = 0; i < vertexSize - 1; i++){
        int currentVertex = findMin(pathCost, isIncluded);
        isIncluded[currentVertex] = true;
        for(int j = 0; j < adjacentLists[currentVertex] -> getSize(); j++){
            auto vert = adjacentLists[currentVertex] -> get(j);
            if(vert.edge && !isIncluded[vert.vertex] && vert.edge < pathCost[vert.vertex]){
                parent[vert.vertex] = currentVertex;
                pathCost[vert.vertex] = vert.edge;
            }
        }
    }
    if(isPrintOut){
        cout << "List representation: " << endl << endl;
        cout<<" Edge\t |    Weight"<<endl<<"---------|-------------"<<endl;
        for(int i = 1; i < vertexSize; i++) {
            if(parent[i] != INT_MAX) {
                cout << "(" << parent[i] << ", " << i << ")\t |\t" << adjacentLists[parent[i]] -> getByVertex(i).edge << endl;
                minCost += pathCost[i];
            }
        }
        cout<<"MST = "<<minCost<<endl<<endl;
    }
    delete[] parent;
    delete[] isIncluded;
    delete[] pathCost;
}

int PrimsList::findMin(const int *pathCost, const bool *isIncluded) {
    int min = INT_MAX;
    int minIndex;
    for(int i = 0; i < vertexSize; i++){
        if(!isIncluded[i] && pathCost[i] < min){
            min = pathCost[i];
            minIndex = i;
        }
    }
    return minIndex;
}
