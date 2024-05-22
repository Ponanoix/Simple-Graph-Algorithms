//
// Created by Ponanoix on 19.05.2023.
//

#ifndef SDIZO2_ADJACENCY_LIST_H
#define SDIZO2_ADJACENCY_LIST_H

#include "connection.h"

// This class represents the single, linked node in the list.
class ListNode{
public:
    ListNode() = default;                                                                                               // The constructor.

    Connection data;                                                                                                    // Connection data of this node.

    struct ListNode *next = nullptr;                                                                                    // Pointer to the next node.
};

// This class houses the different functions associated with the list type.
class AdjacentList{
private:
    ListNode *head = nullptr;                                                                                           // Head of the list.

    ListNode *getLastElement();                                                                                         // Returns the last element of the list.

    ListNode *findNode(Connection x);                                                                                   // Returns the node holding "x" value.

    ListNode *getAtIndex(int i);                                                                                        // Returns the node located at the "i" index.
public:
    explicit AdjacentList(Connection startValue);                                                                       // Initialises a new list with starting value.

    explicit AdjacentList() = default;                                                                                  // Used for creating arrays and empty lists.

    void add(Connection x);                                                                                             // Adds a new element to the list.

    void remove(int i);                                                                                                 // Removes element at the "i" index.

    Connection pop();                                                                                                   // Removes the last element of the list.

    Connection shift();                                                                                                 // Removes the first element of the list.

    Connection get(int i);                                                                                              // Returns the element located at the "i-th" position.

    void print();                                                                                                       // Prints the list.

    int indexOf(Connection x);                                                                                          // Returns the index of the element "x".

    ListNode *findNodeWithVertex(Connection x);                                                                         // Finds the node with the vertex.

    bool containsVertex(int v);                                                                                         // Checks if the list contains the specified vertex.

    void deleteVertex(int v);                                                                                           // Deletes the specified vertex from the list.

    int getSize();                                                                                                      // Returns the size of the list.

    Connection &getByVertex(int v);                                                                                     // Returns the connection which includes the specified vertex.

    void setEdge(int vertex, int weight);                                                                               // Sets the edge's weight of given vertex. If 0 -> the vertex gets deleted.
};

#endif //SDIZO2_ADJACENCY_LIST_H
