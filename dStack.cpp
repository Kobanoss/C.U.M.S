#include "dStack.h"

dStack::dStack() {
    top = nullptr;
    capacity = 0;
}

void dStack::push(int64_t data) {
    auto tmp = new Node;
    tmp->data = data;
    tmp->next = this->top;
    this->top = tmp;
    this->capacity++;
}

int64_t dStack::peek() {
    if (this->top == nullptr) {
        std::cerr << "                      \n"
                     ">> Stack underflow!   \n"
                     ">> Program terminated!\n";
        exit(EXIT_FAILURE);
    }
    return this->top->data;
}

int64_t dStack::pop() {
    if (this->top == nullptr) {
        std::cerr << "                      \n"
                     ">> Stack underflow!   \n"
                     ">> Program terminated!\n";
        exit(EXIT_FAILURE);
    }
    auto tmp = this->top;
    this->top = this->top->next;
    auto res = tmp->data;
    delete tmp;
    this->capacity--;
    return res;
}

dStack::~dStack() {
    while(top != nullptr) {
        auto tmp = this->top;
        this->top = this->top->next;
        delete tmp;
    }
}


