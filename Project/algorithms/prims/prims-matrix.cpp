//
// Created by Ponanoix on 02.06.2023.
//

#include<iostream>
#include"prims-matrix.h"
#include<fstream>
#include<sstream>
#include<cstring>

using namespace std;

void PrimsMatrix::start() {
    int *parent = new int[vertexSize];
    int *begin = new int[edgeSize];
    int *end = new int[edgeSize];
    bool *isIncluded = new bool[vertexSize];
    int *pathCost = new int[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        pathCost[i] = INT_MAX;
        isIncluded[i] = false;
        parent[i] = INT_MAX;
    }
    pathCost[0] = 0;
    parent[0] = -1;
    for(int i = 0; i < vertexSize; i++){
        int currentVertex = findMin(pathCost, isIncluded);
        isIncluded[currentVertex] = true;
        for(int j = 0; j < vertexSize; j++){
            if(incidenceMatrix[currentVertex][j] != 0 && !isIncluded[j] && incidenceMatrix[currentVertex][j] < pathCost[j]){
                parent[j] = currentVertex;
                pathCost[j] = incidenceMatrix[currentVertex][j];
            }
        }
    }
    if (isPrintOut) {
        cout << endl << "Matrix representation:" << endl;
        int i = 0;
        int j = 0;
        do{
            if(isIncluded[j] && isIncluded[parent[j]] && parent[j] != -1){
                begin[i] = parent[j];
                end[i] = j;
                i++;
                j++;
            } else {
                j++;
            }
        } while(i < edgeSize && j < vertexSize);
        compare(begin, end);
    }
    delete[] parent;
    delete[] isIncluded;
    delete[] pathCost;
    delete[] begin;
    delete[] end;
}

void PrimsMatrix::compare(const int *begin, const int *end) {
    int *adjustedBegins = new int[edgeSize];
    int *adjustedEnds = new int[edgeSize];
    std::memset(adjustedBegins, 255, (edgeSize) * sizeof(int));
    std::memset(adjustedEnds, 255, (edgeSize) * sizeof(int));
    int *begins = new int[edgeSize];
    int *ends = new int[edgeSize];
    ifstream inputFile("graph.txt");
    string line;
    getline(inputFile, line);
    for(int i = 0; i < edgeSize && getline(inputFile, line); i++) {
        istringstream iss(line);
        int firstString, secondString;
        iss >> firstString;
        begins[i] = firstString;
        iss >> secondString;
        ends[i] = secondString;
    }
    for(int i = 0; i < edgeSize; i++){
        for(int j = 0; j < vertexSize; j++){
            if(begin[j] == begins[i] && end[j] == ends[i] || begin[j] == ends[i] && end[j] == begins[i]){
                adjustedBegins[i] = begin[j];
                adjustedEnds[i] = end[j];
            }
            if(j == vertexSize - 1 && adjustedBegins[i] == -1 && adjustedEnds[i] == -1){
                adjustedBegins[i] = -1;
                adjustedEnds[i] = -1;
            }
        }
    }
    print(adjustedBegins, adjustedEnds);
    delete[] adjustedBegins;
    delete[] adjustedEnds;
    delete[] begins;
    delete[] ends;
}

int PrimsMatrix::findMin(const int *pathCost, const bool *isIncluded) {
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

