/*
 *  dlist.h
 *
 *  Created on: 26/09/2023
 *  Author: Carlos Davalos
 */

#include <iostream>
#include <string>
using namespace std;

template <class T> class Node {
private:
  T val;
  Node<T> *next = 0;
  Node<T> *previous = 0;

  Node(T val_) { val = val_; }

  int search(T _val, int counter) {
    if (val == _val) {
      return counter;
    } else {
      if (next == 0) {
        return -1;
      }
      return next->search(_val, counter + 1);
    }
  }

  void update(int index, T _val) {
    if (index == 0) {
      val = _val;
    } else {
      next->update(index - 1, _val);
    }
  }

  T deleteAt(int index) {
    T val;
    if (index == 0) {
      val = next->val;
      Node<T> *temp = next->next;
      delete (next);
      temp->previous = this;
      next = temp;
    } else {
      val = next->deleteAt(index - 1);
    }
    return val;
  }

  template <class> friend class DList;
};

template <class T> class DList {
private:
  Node<T> *root = 0;
  Node<T> *tail = 0;
  int length = 0;

public:
  DList() {}
  DList(T value) {
    root->val = value;
    length++;
  }

  string toStringForward() const;
  string toStringBackward() const;

  void insertion(T val);
  int search(T val);
  void update(int index, T val);
  T deleteAt(int index);
};

template <class T>
// Agrega nuevo nodo a dlist
void DList<T>::insertion(T val) {
  Node<T> *new_node = new Node<T>(val);
  if (tail == 0) {
    tail = new_node;
    root = new_node;
  } else {
    tail->next = new_node;
    new_node->previous = tail;
    tail = new_node;
  }
  length++;
}

template <class T>
// Encuentra un valor
int DList<T>::search(T val) {
  int answer;
  if (root != 0) {
    answer = root->search(val, 0);
  }
  return answer;
}

template <class T>
// Actualiza el elemento de Dlist
void DList<T>::update(int index, T val) {
  if (root != 0) {
    root->update(index, val);
  }
}

template <class T>
// Elimina elementos del string
T DList<T>::deleteAt(int index) {
  T val;
  bool ans = index == length - 1;
  if (index == 0) {
    if (length == 1) {
      delete (root);
      tail = 0;
      root = 0;
    } else {
      val = root->val;
      Node<T> *temp = root->next;
      delete (root);
      temp->previous = 0;
      root = temp;
    }
  } else if (index == length - 1) {
    Node<T> *temp_tail = tail->previous;
    val = tail->val;
    temp_tail->next = 0;
    delete (tail);
    tail = temp_tail;
  } else {
    val = root->deleteAt(index - 1);
  }
  length--;
  return val;
}

template <class T> string DList<T>::toStringForward() const {
  stringstream aux;
  Node<T> *p;

  p = root;
  aux << "[";
  while (p != 0) {
    aux << p->val;
    if (p->next != 0) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}

template <class T> string DList<T>::toStringBackward() const {
  stringstream aux;
  Node<T> *p;

  p = tail;
  aux << "[";
  while (p != 0) {
    aux << p->val;
    if (p->previous != 0) {
      aux << ", ";
    }
    p = p->previous;
  }
  aux << "]";
  return aux.str();
}