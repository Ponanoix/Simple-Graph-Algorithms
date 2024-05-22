//
// Created by Ponanoix on 04.06.2023.
//

#include<climits>
#include<iostream>
#include"dijkstra-matrix.h"
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;

void DijkstraMatrix::assignVertices(int startVert, int endVert) {
    startVertex = startVert;
    endVertex = endVert;
}

void DijkstraMatrix::start() {
    int *parent = new int[vertexSize];
    int *begin = new int[edgeSize];
    int *end = new int[edgeSize];
    bool *isIncluded = new bool[vertexSize];    // Array storing bool values; vertex included in spt -> true
    int *shortestPath = new int[vertexSize];    // Stores the shortest path from start to given node
    for(int i = 0; i < vertexSize; i++){
        isIncluded[i] = false;
        shortestPath[i] = INT_MAX;
        parent[i] = INT_MAX;
    }
    parent[startVertex] = -1;
    shortestPath[startVertex] = 0;
    for(int i = 0; i < vertexSize - 1; i++){
        int minV = findMin(shortestPath, isIncluded);
        isIncluded[minV] = true;
        for(int adj = 0; adj < vertexSize; adj++){
            if(!isIncluded[adj] && incidenceMatrix[minV][adj] != 0 && shortestPath[minV] != INT_MAX && shortestPath[minV] + incidenceMatrix[minV][adj] < shortestPath[adj]){
                shortestPath[adj] = shortestPath[minV] + incidenceMatrix[minV][adj];
                parent[adj] = minV;
            }
        }
    }
    if(isPrintOut){
        cout << endl << "Matrix representation: " << endl;
        int i = endVertex;
        if(i == startVertex){
            begin[0] = i;
            end[0] = i;
            for(int j = 1; j < edgeSize; j++){
                begin[j] = -1;
                end[j] = -1;
            }
        } else {
            for (int k = 0; k < edgeSize; k++) {
                for (int j = 0; j < vertexSize; j++) {
                    if (j == parent[i]) {
                        begin[k] = j;
                        end[k] = i;
                        int temp;
                        temp = j;
                        j = parent[j];
                        i = temp;
                    }
                }
            }
        }
        compare(begin, end);
    }
    delete[] isIncluded;
    delete[] shortestPath;
    delete[] parent;
    delete[] begin;
    delete[] end;
}

void DijkstraMatrix::compare(const int *begin, const int *end) {
    int *adjustedBegins = new int[edgeSize];
    int *adjustedEnds = new int[edgeSize];
    std::memset(adjustedBegins, 255, (edgeSize) * sizeof(int));
    std::memset(adjustedEnds, 255, (edgeSize) * sizeof(int));
    int *begins = new int[edgeSize];
    int *ends = new int[edgeSize];
    ifstream inputFile("graph.txt");
    string line;
    getline(inputFile, line);
    if(begin[0] == end[0] && begin[1] == -1 && end[1] == -1){
        adjustedBegins[0] = begin[0];
        adjustedEnds[0] = end[0];
    }
    else {
        for (int i = 0; i < edgeSize && getline(inputFile, line); i++) {
            istringstream iss(line);
            int firstString, secondString;
            iss >> firstString;
            begins[i] = firstString;
            iss >> secondString;
            ends[i] = secondString;
        }
        for (int i = 0; i < edgeSize; i++) {
            for (int j = 0; j < edgeSize; j++) {
                if (begin[j] == begins[i] && end[j] == ends[i]) {
                    adjustedBegins[i] = begin[j];
                    adjustedEnds[i] = end[j];
                }
            }
        }
    }
    print(adjustedBegins, adjustedEnds);
    delete[] adjustedBegins;
    delete[] adjustedEnds;
    delete[] begins;
    delete[] ends;
}

int DijkstraMatrix::findMin(const int *shortestPath, const bool *isIncluded) {
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
