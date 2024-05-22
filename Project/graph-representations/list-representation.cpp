//
// Created by Ponanoix on 02.06.2023.
//

#include<stdexcept>
#include<iostream>
#include "list-representation.h"

using namespace std;

ListRepresentation::ListRepresentation(int vertexSize, int edgeSize, int startVertex, int endVertex, bool isDirected) : vertexSize(vertexSize), edgeSize(edgeSize), startVertex(startVertex), endVertex(endVertex), isDirected(isDirected){
    adjacentLists = new AdjacentList *[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        adjacentLists[i] = new AdjacentList();
    }
}

void ListRepresentation::addConnection(int begin, int end, int weight) {
    if(isDirected){
        if(begin < 0 || begin > vertexSize || end < 0 || end > vertexSize) throw std::invalid_argument("Invalid vertices were passed");
        if((!adjacentLists[begin] -> containsVertex(end) && weight != 0 && currentEdgeSize + 1 > edgeSize)) throw std::logic_error("Graph is already completed. Cannot add more edges");
        if(!adjacentLists[begin] -> containsVertex(end) && weight != 0){
            adjacentLists[begin] -> add(Connection(end, weight));
            currentEdgeSize++;
        }
        else if(adjacentLists[begin] -> containsVertex(end) && weight == 0){
            adjacentLists[begin] -> deleteVertex(end);
            currentEdgeSize--;
        }
        else{
            adjacentLists[begin] -> findNodeWithVertex(Connection(end, weight)) -> data.edge = weight;
        }
    }
    else{
        if(begin < 0 || begin > vertexSize || end < 0 || end > vertexSize) throw std::invalid_argument("Invalid vertices were passed");
        if((!adjacentLists[begin] -> containsVertex(end) && weight != 0 && currentEdgeSize + 1 > edgeSize)) throw std::logic_error("Graph is already completed. Cannot add more edges");
        if(!adjacentLists[begin] -> containsVertex(end) && weight != 0){
            adjacentLists[begin] -> add(Connection(end, weight));
            adjacentLists[end] -> add(Connection(begin, weight));
            currentEdgeSize++;
        }
        else if(adjacentLists[begin] -> containsVertex(end) && weight == 0){
            adjacentLists[begin] -> deleteVertex(end);
            adjacentLists[end] -> deleteVertex(begin);
            currentEdgeSize--;
        }
        else{
            adjacentLists[begin] -> findNodeWithVertex(Connection(end, weight)) -> data.edge = weight;
            adjacentLists[end] -> findNodeWithVertex(Connection(begin, weight)) -> data.edge = weight;
        }
    }
}

AdjacentList **ListRepresentation::getAdjacentLists(){
    return this -> adjacentLists;
}

void ListRepresentation::setEdgeSize(int n) {
    this -> currentEdgeSize = 0;
    this -> edgeSize = n;
}

void ListRepresentation::setVertexSize(int n) {
    for(int i = 0; i < vertexSize; i++){
        delete adjacentLists[i];
    }
    this -> vertexSize = n;
    adjacentLists = new AdjacentList *[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        adjacentLists[i] = new AdjacentList();
    }
}

void ListRepresentation::setEndingVertex(int v) {
    this -> endVertex = v;
}

void ListRepresentation::setStartingVertex(int v) {
    this -> startVertex = v;
}

void ListRepresentation::print() {
    cout<<endl;
    for(int i = 0; i < vertexSize; i++){
        cout<<"From "<<i<<":\n";
        if(adjacentLists[i] -> getSize() == 0) cout<<"\tNone"<<endl;
        else for(int j = 0; j < adjacentLists[i] -> getSize(); j++){
            cout<<"\tTo: "<<adjacentLists[i] -> get(j).vertex<<", weight: "<<adjacentLists[i] -> get(j).edge<<endl;
        }
    }
}

void ListRepresentation::clone(ListRepresentation *representation) {
    this -> startVertex = representation -> startVertex;
    this -> endVertex = representation -> endVertex;
    this -> setVertexSize(representation -> vertexSize);
    this -> setEdgeSize(representation -> edgeSize);
    if (isDirected) {
        for (int i = 0; i < representation -> vertexSize; i++) {
            for (int j = 0; j < representation -> adjacentLists[i] -> getSize(); j++) {
                addConnection(i, representation -> adjacentLists[i] -> get(j).vertex,
                              representation -> adjacentLists[i] -> get(j).edge);
            }
        }
    }
    else{
        for(int i = 0; i < representation -> vertexSize; i++){
            for(int j = 0; j < representation -> adjacentLists[i] -> getSize(); j++){
                addConnection(i, representation -> adjacentLists[i] -> get(j).vertex, representation -> adjacentLists[i] -> get(j).edge);
            }
        }
    }
}

bool ListRepresentation::hasNegativeWeights() {
    for(int i = 0; i < vertexSize; i++){
        for(int j = 0; j < adjacentLists[i] -> getSize(); j++){
            if(adjacentLists[i] -> get(j).edge < 0) return true;
        }
    }
    return false;
}
