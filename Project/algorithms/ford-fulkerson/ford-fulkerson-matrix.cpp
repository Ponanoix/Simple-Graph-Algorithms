//
// Created by Ponanoix on 04.06.2023.
//

#include<climits>
#include<iostream>
#include "ford-fulkerson-matrix.h"
#include "../../utility/queue.h"
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;

void FordFulkersonMatrix::assignVertices(int startVert, int endVert) {
    startVertex = startVert;
    endVertex = endVert;
    if(startVertex < 0 || startVertex >= vertexSize || endVertex < 0 || endVertex >= vertexSize){
        throw invalid_argument("One of the entered vertices is invalid");
    }
}

bool FordFulkersonMatrix::bfs(int parent[]) {
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
            if(residualGraph[curr][i] != 0 && !visited[i]){
                if(i == endVertex){
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

void FordFulkersonMatrix::start() {
    int *begin = new int[edgeSize];
    int *end = new int[edgeSize];
    residualGraph = new int *[vertexSize];
    // Initialise residual matrix
    for (int i = 0; i < vertexSize; i++) {
        residualGraph[i] = new int[vertexSize];
        for (int j = 0; j < vertexSize; j++) {
            residualGraph[i][j] = incidenceMatrix[i][j];
        }
    }
    int flow = 0;
    int *parent = new int[vertexSize];
    while (bfs(parent)) {
        // Finding min path
        int minFlow = INT_MAX;
        for (int i = endVertex; i != startVertex; i = parent[i]) {
            int from = parent[i];
            if (residualGraph[from][i] < minFlow) {
                minFlow = residualGraph[from][i];
            }
        }
        flow += minFlow;
        for (int i = endVertex; i != startVertex; i = parent[i]) {
            int from = parent[i];
            residualGraph[from][i] -= minFlow;
            residualGraph[i][from] += minFlow;
        }
    }
    if (isPrintOut) {
        cout << endl << endl << "Matrix representation: " << endl << endl;
        if(startVertex == endVertex) {
            begin[0] = startVertex;
            end[0] = endVertex;
        } else {
            for (int k = 0; k < edgeSize;) {
                for (int i = 0; i < vertexSize; i++) {
                    for (int j = 0; j < vertexSize; j++) {
                        if (incidenceMatrix[i][j] != 0) {
                            if (residualGraph[j][i] != 0) {
                                begin[k] = i;
                                end[k] = j;
                                k++;
                            }
                        }
                    }
                }
            }
        }
        compare(begin, end);
    }
    delete[] parent;
    delete[] begin;
    delete[] end;
}

void FordFulkersonMatrix::compare(const int *begin, const int *end) {
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

void FordFulkersonMatrix::print(int *begin, const int *end){
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
            if(begin[0] == end[0] && begin[0] != -1 && end[0] != -1 && begin[1] == -1 && end[1] == -1){
                if(begin[0] == i) std::cout <<"\tX";
                else std::cout << "\t0";
            } else {
                if (begin[j] == i) std::cout << "\t-"<<residualGraph[end[j]][begin[j]];
                else if (end[j] == i) std::cout << "\t"<<residualGraph[end[j]][begin[j]];
                else std::cout << "\t0";
            }
        }
        std::cout << std::endl;
    }
    if(begin[0] == end[0] && begin[0] != -1 && end[0] != -1 && begin[1] == -1 && end[1] == -1) cout<<"(Single vertex graph. Vertex -> " << begin[0] << ")";
    std::cout<<std::endl;
    std::cout<<std::endl;
}
