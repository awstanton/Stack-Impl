
#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>

template <typename T> class Stack {
public:
    // constructor
    Stack(int capacity);

    // copy constructor
    Stack(const Stack<T>&);

    // assignment operator
    Stack<T>& operator=(const Stack<T>&);

    // destructor
    ~Stack();

    // stack operations
    void push(T);
    T& pop();
    T& peek() const;
    bool isEmpty() const;
    size_t getSize() const;
    size_t getCapacity() const;

private:
    size_t capacity;
    size_t stackSize;
    T* data;

};

#include "Stack.tpp"

#endif /* STACK_H */
