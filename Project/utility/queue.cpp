//
// Created by Ponanoix on 02.06.2023.
//

#include"queue.h"
#include<iostream>

void Queue::push(int val) {
    if(size == 0){
        this -> arr = new int[1];
        this -> size++;
        this -> arr[0] = val;
        return;
    }
    else{
        int *temp = new int[this -> size + 1];
        for(int i = 0; i < this -> size; i++){
            temp[i] = this -> arr[i];
        }
        temp[this -> size] = val;
        delete this -> arr;
        this -> arr = temp;
        this -> size++;
    }
}

int Queue::shift() {
    if(size == 0) throw std::logic_error("Queue is empty");
    int data = this -> arr[0];
    int *temp = new int[this -> size - 1];
    for(int i = 1; i < this -> size; i++){
        temp[i - 1] = this -> arr[i];
    }
    delete this -> arr;
    this -> arr = temp;
    this -> size--;
    return data;
}

bool Queue::isEmpty() const {
    return this -> size == 0;
}
