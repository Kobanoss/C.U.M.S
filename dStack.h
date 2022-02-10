#ifndef C_U_M_S_DSTACK_H
#define C_U_M_S_DSTACK_H

#include <iostream>
#include <cinttypes>

typedef struct Node {
    int64_t data;
    Node* next;
} Node;

class dStack {
    Node* top;
    int64_t capacity;

public:
    dStack();
    void push(int64_t data);
    int64_t peek();
    int64_t pop();
    ~dStack();

};


#endif //C_U_M_S_DSTACK_H
