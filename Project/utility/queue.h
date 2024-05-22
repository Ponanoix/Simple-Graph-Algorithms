//
// Created by Ponanoix on 02.06.2023.
//

#ifndef SDIZO2_QUEUE_H
#define SDIZO2_QUEUE_H

// This is used to implement a simple queue
class Queue{
private:
    int *arr = nullptr;                         // Array storing data

    int size = 0;                               // Current size of the array
public:
    Queue() = default;                          // Constructor

    void push(int val);                         // Pushes the specified element into the queue

    int shift();                                // Removes the first element from the queue

    [[nodiscard]] bool isEmpty() const;         // Checks if the queue is empty, returns true or false
};

#endif //SDIZO2_QUEUE_H
