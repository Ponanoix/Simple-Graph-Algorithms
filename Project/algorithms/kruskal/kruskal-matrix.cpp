//
// Created by Ponanoix on 03.06.2023.
//

#include<climits>
#include<iostream>
#include"kruskal-matrix.h"
#include<fstream>
#include<vector>
#include<sstream>
#include<cstring>

using namespace std;

void KruskalMatrix::start() {
    int *begin = new int[edgeSize];
    int *end = new int[edgeSize];
    int *parent = new int[vertexSize];
    for (int i = 0; i < vertexSize; i++) {
        parent[i] = i;
    }
    if (isPrintOut) cout << endl << "Matrix representation: " << endl;
    for (int i = 0; i < vertexSize - 1; i++) {
        int minV1, minV2, min = INT_MAX;
        for (int x = 0; x < vertexSize; x++) {
            for (int y = 0; y < vertexSize; y++) {
                if (find(x, parent) != find(y, parent) && incidenceMatrix[x][y] < min && incidenceMatrix[x][y] != 0) {
                    min = incidenceMatrix[x][y];
                    minV1 = x;
                    minV2 = y;
                }
            }
        }
        begin[i] = minV1;
        end[i] = minV2;
        unionVertex(minV1, minV2, parent);
    }
    if(isPrintOut) compare(begin, end);
    delete[] parent;
    delete[] begin;
    delete[] end;
}

void KruskalMatrix::compare(const int *begin, const int *end) {
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


int KruskalMatrix::find(int i, const int *parent) {
    while (parent[i] != i) i = parent[i];
    return i;
}

void KruskalMatrix::unionVertex(int i, int j, int *parent) {
    parent[find(i, parent)] = find(j, parent);
}
