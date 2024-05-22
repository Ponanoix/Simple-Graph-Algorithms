//
// Created by Ponanoix on 19.05.2023.
//

#include<stdexcept>
#include<iostream>
#include "adjacency-list.h"
#include<string>

AdjacentList::AdjacentList(Connection startValue){
    head = new ListNode();
    head -> data = startValue;
}

ListNode *AdjacentList::getLastElement() {
    ListNode *current = head;
    if(head == nullptr) return nullptr;
    while(current -> next != nullptr){
        current = current -> next;
    }
    return current;
}

void AdjacentList::add(Connection x) {
    if(head == nullptr){
        head = new ListNode();
        head -> data = x;
        return;
    }
    ListNode *node = findNodeWithVertex(x);
    if(node != nullptr){
        node -> data.edge = x.edge;
        node -> data.vertex = x.vertex;
        return;
    }
    auto *newNode = new ListNode();
    getLastElement() -> next = newNode;
    newNode -> data = x;
}

ListNode *AdjacentList::findNode(Connection x) {
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    ListNode *curr = this -> head;
    while(curr -> next != nullptr && (curr -> data.vertex != x.vertex && curr -> data.edge != x.edge)){
        curr = curr -> next;
    }
    if((curr -> data.vertex != x.vertex && curr -> data.edge != x.edge)) return nullptr;
    return curr;
}

ListNode *AdjacentList::findNodeWithVertex(Connection x) {
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    ListNode *curr = this -> head;
    while(curr -> next != nullptr && (curr -> data.vertex != x.vertex)){
        curr = curr -> next;
    }
    if((curr -> data.vertex != x.vertex)) return nullptr;
    return curr;
}

ListNode *AdjacentList::getAtIndex(int i) {
    ListNode *curr = head;
    int in = 0;
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    while(curr -> next != nullptr && in < i){
        curr = curr -> next;
        in++;
    }
    if(curr -> next == nullptr && in < i) throw std::logic_error("Too high index (index = "+std::to_string(i)+").");
    return curr;
}

Connection AdjacentList::pop() {
    ListNode *curr = head;
    ListNode *lastElement = getLastElement();
    if(lastElement == nullptr) throw std::logic_error("AdjacentList is empty");
    if(lastElement == head){
        Connection x = head -> data;
        delete head;
        head = nullptr;
        return x;
    }
    while(curr -> next != nullptr && curr -> next != lastElement){
        curr = curr -> next;
    }
    if(curr -> next == nullptr) throw std::logic_error("Unknown exception");
    curr -> next = nullptr;
    Connection x = lastElement -> data;
    delete lastElement;
    return x;
}

Connection AdjacentList::shift() {
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    Connection x = head -> data;
    ListNode* newHead = head -> next;
    delete head;
    head = newHead;
    return x;
}

Connection AdjacentList::get(int i) {
    return getAtIndex(i) -> data;
}

int AdjacentList::indexOf(Connection x) {
    int in = 0;
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    ListNode *curr = head;
    while(curr -> next != nullptr && (curr -> data.vertex != x.vertex && curr -> data.edge != x.edge)){
        curr = curr -> next;
        in++;
    }
    if(curr -> next == nullptr && (curr -> data.vertex != x.vertex && curr -> data.edge != x.edge)) throw std::logic_error("AdjacentList does not contain this value.");
    return in;
}

void AdjacentList::remove(int i) {
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    if(i == 0){
        shift();
        return;
    }
    ListNode *prev = getAtIndex(i - 1);
    ListNode *toDelete = prev -> next;
    prev -> next = toDelete -> next;
    delete toDelete;
}

void AdjacentList::print(){
    ListNode *node = head;
    if(head == nullptr) return;
    while(node -> next != nullptr){
        std::cout<<"Vertex: "<<node -> data.vertex<<" "<<"Edge: "<<node -> data.edge<<std::endl;
        node = node -> next;
    }
    std::cout<<"Vertex: "<<node -> data.vertex<<" "<<"Edge: "<<node -> data.edge<<std::endl;
}

bool AdjacentList::containsVertex(int v) {
    bool contains = false;
    if(head == nullptr) return false;
    ListNode *curr = head;
    while(curr -> next != nullptr && (curr -> data.vertex != v)){
        curr = curr -> next;
    }
    if(curr -> next == nullptr && (curr -> data.vertex != v)) return false;
    return true;
}

Connection &AdjacentList::getByVertex(int v) {
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    ListNode *curr = head;
    while(curr -> next != nullptr && (curr -> data.vertex != v)){
        curr = curr -> next;
    }
    if(curr -> next == nullptr && (curr -> data.vertex != v)) throw std::logic_error("This vertex is not a part of list");
    return curr -> data;
}

void AdjacentList::deleteVertex(int v) {
    if(head == nullptr) throw std::logic_error("AdjacentList is empty");
    ListNode *curr = head;
    if(head -> data.vertex == v){
        shift();
        return;
    }
    while(curr -> next != nullptr && (curr -> next -> data.vertex != v)){
        curr = curr -> next;
    }
    if(curr -> next == nullptr && (curr -> next -> data.vertex != v)) throw std::logic_error("AdjacentList does not have this element");
    ListNode *toDel = curr -> next;
    curr -> next = toDel -> next;
    delete toDel;
}

int AdjacentList::getSize() {
    int i = 0;
    ListNode *curr = head;
    if(head == nullptr) return 0;
    while(curr -> next != nullptr){
        curr = curr -> next;
        i++;
    }
    return i + 1;
}

void AdjacentList::setEdge(int vertex, int weight) {
    if(!containsVertex(vertex)) return;
    else{
        getByVertex(vertex).setEdge(weight);
        if(weight == 0){
            deleteVertex(vertex);
        }
    }
}
