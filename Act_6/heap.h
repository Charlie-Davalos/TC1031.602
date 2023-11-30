/*
 * heap.h
 *
 *  Created on: 10/10/2023
 *      Author: Carlos Davalos
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template<class T>
class Heap {
private:
    vector<T> data;
    int max_size;

    void heapify(int current_index);
    void swap(int i1, int i2);

public:
    Heap();
    Heap(int _max);

    void push(T val);
    void pop();
    T top();
    bool empty();
    int size();
    string toString() const;
};

template<class T>
Heap<T>::Heap() {
    max_size = 0; // Set max_size to 0
    T null_obj = T();
    push(null_obj);
}

template<class T>
Heap<T>::Heap(int _max) {
    max_size = _max;
    T null_obj = T();
    push(null_obj);
}

template<class T>
void Heap<T>::swap(int i1, int i2) {
    T temp = data[i1];
    data[i1] = data[i2];
    data[i2] = temp;
}

template<class T>
void Heap<T>::heapify(int current_index) {
    int compare_index = static_cast<int>(current_index / 2);
    bool exit = false;
    while (!exit) {
        if (data[current_index] < data[compare_index]) {
            swap(current_index, compare_index);
            current_index = compare_index;
            compare_index = static_cast<int>(current_index / 2);
        }
        else {
            exit = true;
        }
    }
}

template<class T>
void Heap<T>::push(T val) {
    if (data.size() >= max_size) return;
    data.push_back(val);
    heapify(data.size() - 1);
}

template<class T>
void Heap<T>::pop() {
    if (data.size() < 2) return;
    data[1] = data[data.size() - 1];
    data.pop_back();
    int parent_index = 1;
    bool exit = false;
    while (!exit) {
        int child_selected = parent_index * 2;
        int child1 = child_selected;
        int* child2_ptr = &child1;
        int child2 = child_selected + 1;
        if (child1 >= data.size()) child1 = parent_index;
        if (child2 >= data.size()) child2 = *child2_ptr;
        if (data[child2] < data[child1]) child_selected += 1;
        if (data[child_selected] < data[parent_index]) {
            swap(child_selected, parent_index);
        }
        else {
            exit = true;
        }
        parent_index = child_selected;
        if (parent_index >= data.size() - 1) exit = true;
    }
}

template<class T>
T Heap<T>::top() {
    return data[1];
}

template<class T>
bool Heap<T>::empty() {
    if (data.size() >= 2) return false;
    return true;
}

template<class T>
int Heap<T>::size() {
    return data.size() - 1;
}

template <class T>
string Heap<T>::toString() const {
    stringstream aux;
    aux << "[";
    for (unsigned int i = 1; i < data.size(); i++) {
        if (i != 1) {
            aux << " ";
        }
        aux << data[i];
    }
    aux << "]";
    return aux.str();
}
