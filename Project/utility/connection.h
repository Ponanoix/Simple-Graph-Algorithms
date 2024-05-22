//
// Created by Ponanoix on 19.05.2023.
//

#ifndef SDIZO2_CONNECTION_H
#define SDIZO2_CONNECTION_H

class Connection {
public:
    int edge;                                                           // This variable represents the graph's edge.

    int vertex;                                                         // This variable represents the graph's vertex.

    Connection(int vertex, int edge): edge(edge), vertex(vertex){};     // This function connects the graph's elements.

    Connection() = default;                                             // This is the default constructor for the method.

    void setEdge(int weight){                                           // These two functions set values for individual edges and vertices.
        edge = weight;
    }

    void setVert(int vert){                                             // These two functions set values for individual edges and vertices.
        vertex = vert;
    }
};

#endif //SDIZO2_CONNECTION_H
