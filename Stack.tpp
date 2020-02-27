
#include "Stack.h"

// constructor
template <typename T>
Stack<T>::Stack(int capacity) : capacity(capacity), stackSize(0) {
    if (capacity != 0)
        data = new T[capacity];
    else
        data = NULL;
}

// copy constructor
template <typename T>
Stack<T>::Stack(const Stack<T>& s) : capacity(s.getCapacity()), stackSize(s.getSize()) {
    if (capacity > 0) {
        data = new T[capacity];

        if (!s.isEmpty()) {
            T* sData = &(s.peek());

            for (size_t i = 0; i < s.getSize(); ++i) {
                data[(s.getSize() - 1) - i] = sData[-i];
            }
        }
    }
    else {
        data = NULL;
    }
}

// assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& r) {
    if (&r != this) {
        if (capacity != 0) {
            delete[] data;
        }
        if (r.getCapacity() == 0) {
            if (capacity != 0) {
                data = NULL;
                capacity = 0;
                stackSize = 0; // stackSize should never be greater than capacity
            }
            // else nothing to do
        }
        else {
            capacity = r.getCapacity();
            stackSize = r.getSize();
            data = new T[capacity];
            if (!r.isEmpty()) {
                T* sData = &(r.peek());

                for (size_t i = 0; i < r.getSize(); ++i) {
                    data[(r.getSize() - 1) - i] = sData[-i];
                }
            }
        }
    }
    return *this;
}

// destructor
template <typename T>
Stack<T>::~Stack() {
    if (capacity != 0)
        delete[] data;
}

template <typename T>
void Stack<T>::push(T element) {
    // stack full
    if (stackSize + 1 > capacity) {
        int originalCapacity = capacity;

        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;

        T* tempData = new T[capacity];

        for (size_t i = 0; i < stackSize; ++i) {
            tempData[i] = data[i];
        }
        if (originalCapacity != 0) {
            delete[] data;
        }
        data = tempData;
    }
    // add new element and increment size
    data[stackSize++] = element;
}

template <typename T>
T& Stack<T>::pop() {
    if (!isEmpty())
        return data[--stackSize];
    else
        throw std::underflow_error("stack is already empty");
}

template <typename T>
T& Stack<T>::peek() const {
    if (!isEmpty())
        return data[stackSize - 1];
    else
        throw std::out_of_range("stack is currently empty");
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return stackSize == 0;
}

template <typename T>
size_t Stack<T>::getCapacity() const {
    return capacity;
}

template <typename T>
size_t Stack<T>::getSize() const {
    return stackSize;
}
