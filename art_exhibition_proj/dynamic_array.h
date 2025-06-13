#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <iostream>
using namespace std;
template <typename T>
class Dynamic_array {
    T* arr;
    int len, cap;
public:
    Dynamic_array();
    Dynamic_array(int count, T value);
    Dynamic_array(const Dynamic_array& other);
    ~Dynamic_array();
    Dynamic_array& operator=(const Dynamic_array& other);
    void push(T value);
    void pop();
    void double_capacity();
    void display() const;
    int getLength() const;
    T& operator[](int index);
    const T& operator[](int index) const;
	//void clear();
};

template <typename T>
Dynamic_array<T>::Dynamic_array() {
    len = 0;
    cap = 1;
    arr = new T[cap];
}


template <typename T>
Dynamic_array<T>::Dynamic_array(int count, T value) {
    len = count;
    cap = count;
    arr = new T[cap];
    for (int i = 0; i < len; i++) {
        arr[i] = value;
    }
}

template <typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array& other) {
    len = other.len;
    cap = other.cap;
    arr = new T[cap];
    for (int i = 0; i < len; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Dynamic_array<T>::~Dynamic_array() {
    delete[] arr;
    arr = nullptr;
}

template <typename T>
Dynamic_array<T>& Dynamic_array<T>::operator=(const Dynamic_array& other) {
    if (this != &other) {
        len = other.len;
        cap = other.cap;
        delete[] arr;
        arr = new T[cap];
        for (int i = 0; i < len; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template <typename T>
void Dynamic_array<T>::double_capacity() {
    T* temp = new T[cap * 2];
    for (int i = 0; i < len; i++) {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    cap *= 2;
}
template <typename T>
void Dynamic_array<T>::push(T value) {
    if (len == cap) {
        double_capacity();
    }
    arr[len++] = value;
}
//template <typename T>
//void Dynamic_array<T>::clear() {
//
//
//    }
template <typename T>
void Dynamic_array<T>::pop() {
    if (len > 0) len--;
}

template <typename T>
void Dynamic_array<T>::display() const {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
template <typename T>
int Dynamic_array<T>::getLength() const {
    return len;
}

template <typename T>
T& Dynamic_array<T>::operator[](int index) {
    if (index >= 0 && index < len) {
        return arr[index];
    }
    throw out_of_range("Index out of range");
}

template <typename T>
const T& Dynamic_array<T>::operator[](int index) const {
    if (index >= 0 && index < len) {
        return arr[index];
    }
    throw out_of_range("Index out of range");
}

#endif