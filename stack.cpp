#include "stack.h"

Stack::Stack(const int64_t size) {
    this->arr = new int64_t[size];
    this->capacity = size;
    this->top = -1;
}

Stack::~Stack() {
    while (this->top != -1)
        this->pop();
    this->top = NULL;
    this->capacity = NULL;
    delete[] this->arr;
}

bool Stack::isEmpty() {
    return this->top == -1;
}


bool Stack::isFull() {
    return this->top == this->capacity - 1;
}
int64_t Stack::peek() {
    if (this->isEmpty()) {
        std::cerr << "                      \n"
                     ">> Stack is empty!    \n"
                     ">> Program terminated!\n";
        exit(EXIT_FAILURE);
    } else
        return this->arr[this->top];
}

int64_t Stack::pop() {
    if (this->isEmpty()) {
        std::cerr << "                      \n"
                     ">> Stack underflow!   \n"
                     ">> Program terminated!\n";
        exit(EXIT_FAILURE);
    }
    return this->arr[this->top--];
}

void Stack::push(const int64_t value) {
    if (this->isFull()) {
        std::cerr << "                      \n"
                     ">> Stack overflow!    \n"
                     ">> Program terminated!\n";
        exit(EXIT_FAILURE);
    }
    this->arr[++this->top] = value;
}

int64_t Stack::getSize(){
    return this->top + 1;
}

int64_t Stack::getCapacity(){
    return this->capacity;
}

void Stack::softResize(const int64_t new_size) {
    if (new_size == getSize())
        return;

    if (new_size < getSize()) {
        std::cerr << "                      \n"
                     ">> Can't resize object\n"
                     ">> Program terminated!\n";
        exit(EXIT_FAILURE);
    }

    auto *new_arr = new int64_t[new_size];

    memcpy(new_arr, this->arr, this->getCapacity() * sizeof(int64_t));

    this->capacity = new_size;
    delete[] this->arr;
    this->arr = new_arr;
}

void Stack::bruteResize(const int64_t new_size) {
    if (new_size == this->getSize())
        return;

    if (new_size > this->getSize()) {
        auto *new_arr = new int64_t[new_size];
        memcpy(new_arr, this->arr, this->getCapacity() * sizeof(int64_t));

        this->capacity = new_size;
        delete[] this->arr;
        this->arr = new_arr;
    } else {
        auto *new_arr = new int64_t[new_size];
        memcpy(new_arr, this->arr, new_size * sizeof(int64_t));

        this->capacity = new_size;
        this->top = new_size - 1;
        delete[]this->arr;
        this->arr = new_arr;
    }
}
