/*
 * bst.h
 *
 *  Created on: 14/10/2023
 *      Author: Carlos Davalos 
 */

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <class T>
class Node;

template <class T>
class BST {
private:
    Node<T>* root = nullptr;
    int max_depth;

public:
    BST() {}
    BST(T val) {
        Node<T>* node = new Node<T>(val);
        root = node;
    }

    void add(T val);
    vector<T> level_traversal();
    string visit();
    int height();
    string ancestors(T val);
    int whatlevelamI(T val);
};

template <class T>
void BST<T>::add(T val) {
    if (root == nullptr) {
        Node<T>* new_node = new Node<T>(val, 0);
        root = new_node;
        max_depth = 0;
    } else {
        root->add(val, 0, max_depth);
    }
}

template <class T>
int BST<T>::whatlevelamI(T val) {
    if (root == nullptr) return -1;
    return root->level_at(val);
}

template <class T>
int BST<T>::height() {
    return max_depth + 1;
}

template <class T>
Node<T>* pop(vector<Node<T>*>& arr) {
    Node<T>* node = nullptr;
    if (arr.size() == 0) return node;
    node = arr[arr.size() - 1];
    arr.pop_back();
    return node;
}

template <class T>
vector<T> BST<T>::level_traversal() {
    vector<T> prints;
    vector<Node<T>*> queue;
    Node<T>* current = root;
    while (current != nullptr) {
        prints.push_back(current->val);
        if (current->left != nullptr) queue.insert(queue.begin(), current->left);
        if (current->right != nullptr) queue.insert(queue.begin(), current->right);
        if (queue.size() > 0) {
            current = pop(queue);
        } else {
            current = nullptr;
        }
    }

    return prints;
}

template <class T>
string BST<T>::visit() {
    if (root == nullptr) return "[]\n[]\n[]\n[]";

    stringstream answer;
    answer << "[";

    vector<int> preorder;
    vector<int> depth;
    root->visit(preorder, depth, 1);
    for (int i = 0; i < preorder.size(); i++) {
        answer << to_string(preorder[i]);
        if (i < preorder.size() - 1) answer << " ";
    }
    answer << "]\n[";

    vector<int> inorder;
    root->visit(inorder, depth, 2);
    for (int i = 0; i < inorder.size(); i++) {
        answer << to_string(inorder[i]);
        if (i < inorder.size() - 1) answer << " ";
    }
    answer << "]\n[";

    vector<int> postorder;
    root->visit(postorder, depth, 3);
    for (int i = 0; i < postorder.size(); i++) {
        answer << to_string(postorder[i]);
        if (i < postorder.size() - 1) answer << " ";
    }
    answer << "]\n[";

    vector<T> level = level_traversal();
    for (int i = 0; i < level.size(); i++) {
        answer << to_string(level[i]);
        if (i < level.size() - 1) answer << " ";
    }
    answer << "]";
    string answer2 = answer.str();
    return answer2;
}

template <class T>
string BST<T>::ancestors(T val) {
    if (root == nullptr) return "[]";
    string answer = "[";
    vector<T> ancestors_vec;
    root->ancestors(val, ancestors_vec);
    for (int i = 0; i < ancestors_vec.size(); i++) {
        answer = answer + to_string(ancestors_vec[i]);
        if (i < ancestors_vec.size() - 1) answer = answer + " ";
    }
    answer = answer + "]";
    return answer;
}

template <class T>
class Node {
private:
    T val;
    int level;
    Node* left;
    Node* right;

public:
    Node() {}
    Node(T _val, int _level) : val(_val), level(_level), left(nullptr), right(nullptr) {}

    int level_at(T _val);
    void add(T _val, int current_depth, int& max_depth);
    void visit(vector<int>& prints, vector<int>& depths, int check);
    void ancestors(T _val, vector<T>& ancestors_vec);

    friend class BST<T>;
};

template <class T>
void Node<T>::add(T _val, int current_depth, int& max_depth) {
    current_depth++;
    if (_val == val) {
        return;
    } else if (_val < val) {
        if (left != nullptr)
            left->add(_val, current_depth, max_depth);
        else {
            Node* new_node = new Node(_val, current_depth + 1);
            left = new_node;
            if (current_depth > max_depth) {
                max_depth = current_depth;
            }
        }
    } else {
        if (right != nullptr)
            right->add(_val, current_depth, max_depth);
        else {
            Node* new_node = new Node(_val, current_depth + 1);
            right = new_node;
            if (current_depth > max_depth) {
                max_depth = current_depth;
            }
        }
    }
}

template <class T>
void Node<T>::visit(vector<int>& prints, vector<int>& depths, int check) {
    int counter = 1;
    if (counter == check)
        prints.push_back(val);

    if (left != nullptr) {
        left->visit(prints, depths, check);
    }

    counter++;
    if (counter == check)
        prints.push_back(val);

    if (right != nullptr) {
        right->visit(prints, depths, check);
    }

    counter++;
    if (counter == check)
        prints.push_back(val);
}

template <class T>
int Node<T>::level_at(T _val) {
    if (_val == val) {
        return level;
    }
    if (left != nullptr) {
        if (_val < val) return left->level_at(_val);
    }
    if (right != nullptr) {
        if (_val > val) return right->level_at(_val);
    }
    return -1;
}

template <class T>
void Node<T>::ancestors(T _val, vector<T>& ancestors_vec) {
    if (_val == val) return;

    if ((_val > val) && (right != nullptr)) {
        ancestors_vec.push_back(val);
        right->ancestors(_val, ancestors_vec);
    } else {
        ancestors_vec = {};
    }
}
