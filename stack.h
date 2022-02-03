#ifndef C_U_M_S_STACK_H
#define C_U_M_S_STACK_H

#include <iostream>
#include <cinttypes>
#include <cstdlib>
#include <cstring>

#define SIZE 5


class Stack {
private:
    int64_t* arr;
    int64_t top = NULL;
    int64_t capacity = NULL;

public:
    explicit Stack(int64_t size = SIZE);
    ~Stack();

    bool isFull();
    bool isEmpty();

    int64_t peek();
    int64_t pop();
    void push(int64_t value);

    int64_t getSize();
    int64_t getCapacity();

    void softResize(int64_t new_size);
    void bruteResize(int64_t new_size);
};


#endif //C_U_M_S_STACK_H
