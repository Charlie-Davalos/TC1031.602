/*
 *  list.h
 *
 *  Created on: 25/09/2023
 *  Author: Carlos Davalos 
 */
#include<iostream>
#include<string>
using namespace std;


template<class T>
class Node{
private:
	T val;
	Node<T>* next=0;

	Node(T val_){
		val = val_;
	}

	void insertion(Node<T>* node){
		if (next == 0){
			next = node;
		}
		else{
			next->insertion(node);
		}
	}

	int search(T _val, int counter){
		if (val == _val){
			return counter;
		} else {
			if (next == 0){
				return -1;
			}
			return next->search(_val, counter+1);
		}
	}

	void update(int index, T _val){
		if (index == 0){
			val = _val;
		} else {
			next->update(index-1, _val);
		}
	}

	T deleteAt(int index){
		T val;
		if (index == 0){
			val = next->val;
			Node<T>* temp = next->next;
			delete(next);
			next = temp;
		} else {
			val = next->deleteAt(index-1);
		}
		return val;
	}

	template <class> friend class List;
};


template<class T>
class List{
private:
	Node<T>* root=0;
	int length=0;

public:
	List(){}
	List(T value){
		root->val = value;
		length++;
	}
	
	string toString() const;

	void insertion(T val);
	int search(T val);
	void update(int index, T val);
	T deleteAt(int index);
	
};


template<class T>
void List<T>::insertion(T val){
	if (root == 0){
		Node<T>* new_node = new Node<T>(val);
		root = new_node;
		length++;
	}
	else {
		Node<T>* new_node = new Node<T>(val);
		root->insertion(new_node);
		length++;
	}
}

template<class T>
int List<T>::search(T val){
	int answer;
	if (root != 0){
		answer = root->search(val, 0);
	}
	return answer;
}

template<class T>
void List<T>::update(int index, T val){
	if (root != 0){
		root->update(index, val);
	}
}

template<class T>
T List<T>::deleteAt(int index){
	T val;
	if (index == 0){
		val = root->val;
		Node<T>* temp = root->next;
		delete(root);
		root = temp;
	} else {
		val = root->deleteAt(index-1);
	}
	length--;
	return val;
}

template<class T>
string List<T>::toString() const {
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