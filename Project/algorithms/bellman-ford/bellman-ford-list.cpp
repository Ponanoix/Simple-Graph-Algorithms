//
// Created by Ponanoix on 04.06.2023.
//

#include<climits>
#include<iostream>
#include"bellman-ford-list.h"

using namespace std;

void BellmanFordList::assignVertices(int startVert) {
    startVertex = startVert;
    if(startVertex < 0 || startVertex >= vertexSize){
        throw invalid_argument("The entered vertex is invalid");
    }
    if(!isDirected){
        throw logic_error("The graph must be directed");
    }
}

void BellmanFordList::start() {
    int *shortestPath = new int[vertexSize];
    int *parent = new int[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        shortestPath[i] = INT_MAX;
        parent[i] = INT_MAX;
    }
    shortestPath[startVertex] = 0;
    parent[startVertex] = -1;
    bool wasRelaxation = false;
    for(int i = 0; i < vertexSize - 1; i++){
        wasRelaxation = false;
        for(int j = 0; j < adjacentLists[i] -> getSize(); j++){
            int dest = adjacentLists[i] -> get(j).vertex;
            int edge = adjacentLists[i] -> get(j).edge;
            if(shortestPath[i] != INT_MAX && shortestPath[i] + edge < shortestPath[dest]){
                shortestPath[dest] = shortestPath[i] + edge;
                parent[dest] = i;
                wasRelaxation = true;
            }
        }
    }
    if(!wasRelaxation){
        if(isPrintOut) printResult(parent, shortestPath);
        return;
    }
    // Fixing negative weight cycles
    for(int i = 0; i < vertexSize; i++){
        for(int j = 0; j < adjacentLists[i] -> getSize(); j++){
            int dest = adjacentLists[i] -> get(j).vertex;
            int edge = adjacentLists[i] -> get(j).edge;
            if(shortestPath[j] == INT_MAX) continue;
            if(shortestPath[i] != INT_MAX && shortestPath[i] + edge < shortestPath[dest]){
                if(isPrintOut) cout<<"Graph has negative cycles, stopping the algorithm..."<<endl;
                return;
            }
        }
    }
    if(isPrintOut) printResult(parent, shortestPath);
    delete[] shortestPath;
    delete[] parent;
}

void BellmanFordList::printPath(const int *parent, int vert) {
    int curr = vert;
    cout << curr;
    curr = parent[curr];
    while(curr != -1){
        cout << " <- " << curr;
        curr = parent[curr];
    }
    cout<<endl;
}

void BellmanFordList::printResult(int *parent, int *shortestPath) {
    cout << endl << endl << "\t\tStarting Vertex = " << startVertex << "" << endl << endl;
    cout << "List representation: " << endl << endl;
    cout<<"----------------|---------------|----------------"<<endl;
    cout << "  Destination\t|   Distance\t|\tPath" << endl;
    cout << "----------------|---------------|----------------" << endl;
    for(int i = 0; i < vertexSize; i++){
        if(parent[i] != INT_MAX){
            cout << "\t" << i << "\t|\t" << shortestPath[i] << "\t| ";
            printPath(parent, i);
        }
    }
    cout<<endl<<endl;
}
