//
// Created by Ponanoix on 02.06.2023.
//

#include<climits>
#include<iostream>
#include"kruskal-list.h"

using namespace std;

void KruskalList::seekErrors() {
    for(int i = 0; i < vertexSize; i++){
        if(adjacentLists[i] -> getSize() == 0){
            throw logic_error("The graph is not connected");
        }
    }
    if(isDirected){
        throw logic_error("The graph cannot be directed");
    }
}

int KruskalList::find(int i, const int *parent) {
    while(parent[i] != i) i = parent[i];
    return i;
}

void KruskalList::unionVertex(int i, int j, int *parent) {
    parent[find(i, parent)] = find(j, parent);
}

void KruskalList::start() {
    int minCost = 0;
    int *parent = new int[vertexSize];
    for(int i = 0; i < vertexSize; i++) {
        parent[i] = i;
    }
    if(isPrintOut) cout<< "List representation: "<<endl<<endl;
    if(isPrintOut) cout<<" Edge\t |    Weight"<<endl<<"---------|-------------"<<endl;
    for(int i = 0; i < vertexSize - 1; i++){
        int min = INT_MAX;
        int vert1, vert2;
        for(int x = 0; x < vertexSize; x++){
            for(int y = 0; y < adjacentLists[x] -> getSize(); y++){
                Connection con = adjacentLists[x] -> get(y);
                if(find(con.vertex, parent) != find(x, parent) && con.edge < min){
                    min = con.edge;
                    vert1 = x;
                    vert2 = con.vertex;
                    }
                }
            }
        unionVertex(vert1, vert2, parent);
        if(isPrintOut) cout<<"("<<vert1<<", "<<vert2<<")\t "<<"|\t"<<min<<endl;
        minCost += min;
    }
    if(isPrintOut) cout<<"MST = "<<minCost<<endl<<endl;
    delete[] parent;
}
