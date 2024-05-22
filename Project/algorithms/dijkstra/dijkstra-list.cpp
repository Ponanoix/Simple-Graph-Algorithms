//
// Created by Ponanoix on 04.06.2023.
//

#include<climits>
#include<iostream>
#include"dijkstra-list.h"
#include<iomanip>

using namespace std;

void DijkstraList::seekErrors() {
    if(hasNegativeWeights()){
        throw logic_error("The graph has negative weights");
    }
    if(!isDirected){
        throw logic_error("The graph must be directed");
    }
}

void DijkstraList::assignVertices(int startVert, int endVert) {
    startVertex = startVert;
    endVertex = endVert;
    if(startVertex < 0 || startVertex >= vertexSize || endVertex < 0 || endVertex >= vertexSize){
        throw invalid_argument("One of the entered vertices is invalid");
    }
}

int DijkstraList::findMin(const int *shortestPath, const bool *isIncluded) {
    int min = INT_MAX;
    int minIndex;
    for(int i = 0; i < vertexSize; i++){
        if(!isIncluded[i] && shortestPath[i] < min){
            min = shortestPath[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void DijkstraList::start() {
    int *shortestPath = new int[vertexSize];
    bool *isIncluded = new bool[vertexSize];
    int *parent = new int[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        shortestPath[i] = INT_MAX;
        isIncluded[i] = false;
        parent[i] = INT_MAX;
    }
    parent[startVertex] = -1;
    shortestPath[startVertex] = 0;
    for(int i = 0; i < vertexSize - 1; i++){
        int minVert = findMin(shortestPath, isIncluded);
        isIncluded[minVert] = true;
        for(int j = 0; j < adjacentLists[minVert] -> getSize(); j++){
            int adj = adjacentLists[minVert] -> get(j).vertex;
            if(!isIncluded[adj] && shortestPath[minVert] != INT_MAX && shortestPath[minVert] + adjacentLists[minVert] -> get(j).edge < shortestPath[adj]) {
                shortestPath[adj] = shortestPath[minVert] + adjacentLists[minVert] -> get(j).edge;
                parent[adj] = minVert;
            }
        }
    }
    if(shortestPath[endVertex] == INT_MAX){
        throw logic_error("No possible path between the vertices");
    }
    if(isPrintOut){
        cout<<endl<<endl<< "List representation: " << endl << endl;
        cout<<" Start = " << startVertex << setw(3) << "|";
        cout<<"   End = "<< endVertex << endl;
        cout<<"------------|---------------"<<endl;
        cout<<"  Distance  |    Path"<<endl;
        cout<<"            |            "<<endl;
        cout<<setw(7)<<shortestPath[endVertex]<<setw(6)<<"|"<<setw(3);
        printPath(parent, endVertex);
        cout<<endl;
    }
    delete[] shortestPath;
    delete[] isIncluded;
    delete[] parent;
}

void DijkstraList::printPath(const int *parent, int vertex) {
    int curr = vertex;
    cout<<curr;
    curr = parent[curr];
    while(curr != -1){
        cout<<" <- "<<curr;
        curr = parent[curr];
    }
    cout<<endl;
}
