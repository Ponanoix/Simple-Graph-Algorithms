//
// Created by Ponanoix on 04.06.2023.
//

#include<climits>
#include<iostream>
#include"bellman-ford-matrix.h"
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;

void BellmanFordMatrix::assignVertices(int startVert) {
    startVertex = startVert;
    if(startVertex < 0 || startVertex >= vertexSize){
        throw invalid_argument("The entered vertex is invalid");
    }
}

void BellmanFordMatrix::start() {
    int *shortestPath = new int[vertexSize];
    int *parent = new int[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        shortestPath[i] = INT_MAX;
        parent[i] = INT_MAX;
    }
    parent[startVertex] = -1;
    shortestPath[startVertex] = 0;
    bool wasRelaxation = false;
    for(int i = 0; i < vertexSize - 1; i++){
        wasRelaxation = false;
        for(int j = 0; j < vertexSize; j++){
            int edge = incidenceMatrix[i][j];
            if(edge != 0 && shortestPath[i] != INT_MAX && shortestPath[i] + edge < shortestPath[j]){
                shortestPath[j] = shortestPath[i] + edge;
                parent[j] = i;
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
        for(int j = 0; j < vertexSize; j++){
            int edge = incidenceMatrix[i][j];
            if(shortestPath[j] == INT_MAX) continue;
            if(edge != 0 && shortestPath[i] != INT_MAX && shortestPath[i] + edge < shortestPath[j]){
                if(isPrintOut) cout<<"Graph has negative cycles, stopping algorithm..."<<endl;
                return;
            }
        }
    }
    if(isPrintOut) printResult(parent, shortestPath);
    delete[] shortestPath;
    delete[] parent;
}

void BellmanFordMatrix::printResult(int *parent, int *shortestPath) {
    cout << "Matrix representation: " << endl << endl;
    for(int i = 1; i < vertexSize; i++){
        if(parent[i] != INT_MAX){
            int *begin = new int[edgeSize];
            int *end = new int[edgeSize];
            cout << i << " | " << shortestPath[i] << " | ";
            printPath(parent, i, begin, end, shortestPath);
            delete[] begin;
            delete[] end;
        }
    }
}

void BellmanFordMatrix::printPath(const int *parent, int vert, int *begin, int *end, const int *shortestPath) {
    int i = 0;
    int curr = vert;
    cout << curr;
    if(shortestPath[curr] == 0){
        begin[i] = curr;
        end[i] = curr;
    }
    else {
        begin[i] = parent[curr];
        end[i] = curr;
        i++;
        curr = parent[curr];

        while (curr != -1) {
            cout << " <- " << curr;
            begin[i] = parent[curr];
            end[i] = curr;
            i++;
            curr = parent[curr];
        }
    }
    cout<<endl;
    compare(begin, end);
}

void BellmanFordMatrix::compare(const int *begin, const int *end) {
    int *adjustedBegins = new int[edgeSize];
    int *adjustedEnds = new int[edgeSize];
    std::memset(adjustedBegins, 255, (edgeSize) * sizeof(int));
    std::memset(adjustedEnds, 255, (edgeSize) * sizeof(int));
    int *begins = new int[edgeSize];
    int *ends = new int[edgeSize];
    ifstream inputFile("graph.txt");
    string line;
    getline(inputFile, line);
    if(begin[0] == end[0]){
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