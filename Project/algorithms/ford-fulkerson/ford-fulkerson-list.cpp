//
// Created by Ponanoix on 03.06.2023.
//

#include<climits>
#include<iostream>
#include "ford-fulkerson-list.h"
#include "../../utility/queue.h"

using namespace std;

void FordFulkersonList::seekErrors() {
    for(int i = 0; i < vertexSize - 1; i++){
        if(adjacentLists[i] -> getSize() == 0){
            throw logic_error("The graph is not connected");
        }
    }
    if(hasNegativeWeights()){
        throw logic_error("The graph has negative weights");
    }
    if(!isDirected){
        throw logic_error("The graph must be directed");
    }
}

void FordFulkersonList::assignVertices(int startVert, int endVert) {
    startVertex = startVert;
    endVertex = endVert;
    if(startVertex < 0 || startVertex >= vertexSize || endVertex < 0 || endVertex >= vertexSize){
        throw invalid_argument("One of the entered vertices is invalid");
    }
}

bool FordFulkersonList::bfs(int parent[]) {
    bool *visited = new bool[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        visited[i] = false;
    }
    Queue queue;
    queue.push(startVertex);
    visited[startVertex] = true;
    parent[startVertex] = -1;
    while(!queue.isEmpty()){
        int curr = queue.shift();
        for(int i = 0; i < vertexSize; i++){
            if(!visited[i] && residualGraph[curr] -> containsVertex(i)){
                if(i == endVertex) {
                    parent[i] = curr;
                    delete[] visited;
                    return true;
                }
                parent[i] = curr;
                visited[i] = true;
                queue.push(i);
            }
        }
    }
    delete[] visited;
    return false;
}

void FordFulkersonList::start() {
    auto *list = new ListRepresentation(vertexSize, edgeSize, startVertex, endVertex, true);
    //Initialisation of the residual matrix
    for(int i = 0; i < vertexSize; i++){
        for(int j = 0; j < adjacentLists[i] -> getSize(); j++){
            list -> addConnection(i, adjacentLists[i] -> get(j).vertex, adjacentLists[i] -> get(j).edge);
        }
    }
    residualGraph = list->getAdjacentLists();
    int flow = 0;
    int *parent = new int[vertexSize];
    while(bfs(parent)){
        //Finding the minimal path
        int minFlow = INT_MAX;
        for(int i = endVertex; i != startVertex; i = parent[i]){
            int from = parent[i];
            if(residualGraph[from] -> containsVertex(i) && residualGraph[from] -> getByVertex(i).edge < minFlow){
                minFlow = residualGraph[from] -> getByVertex(i).edge;
            }
        }
        flow += minFlow;
        for(int i = endVertex; i != startVertex; i = parent[i]){
            int from = parent[i];
            residualGraph[from] -> setEdge(i, (residualGraph[from] -> getByVertex(i).edge - minFlow));
            if(!residualGraph[i] -> containsVertex(from)) residualGraph[i] -> add(Connection(from, minFlow));
            else residualGraph[i] -> setEdge(from, residualGraph[i] -> getByVertex(from).edge + minFlow);
        }
    }
    if(isPrintOut){
        cout<<endl<<endl<< "List representation: " << endl << endl;
        cout<<"Edge Flow (max/used)" << endl;
        for(int i = 0; i < vertexSize; i++){
            for(int j = 0; j < adjacentLists[i] -> getSize(); j++){
                int remaining = 0;
                if(residualGraph[adjacentLists[i] -> get(j).vertex] -> containsVertex(i)) remaining = residualGraph[adjacentLists[i] -> get(j).vertex] -> getByVertex(i).edge;
                cout<<"("<<i<<", "<<adjacentLists[i] -> get(j).vertex<<") "<<adjacentLists[i] -> get(j).edge<<" / "<<remaining<<endl;
            }
        }
        cout<<"MAX_FLOW = "<<flow<<endl;
    }
    delete[] parent;
}
