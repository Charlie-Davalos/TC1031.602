#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class SplayTree;

template<class T>
class Node{
private:
  T value;
  Node *left, *right, *parent;

  Node<T>* succesor();
  Node<T>* rot_right(Node<T>*);
  Node<T>* rot_left(Node<T>*);

public:
  Node(T);
  Node(T,Node<T>*,Node<T>*,Node<T>*);
  Node<T>*add(T);
  Node<T>*find(T);
  Node<T>*remove(T);
  void removeChilds();
  void inorder(std::stringstream&) const;
  void print_tree(std::stringstream&) const;
  void preorder(std::stringstream&) const;
  Node<T>* splay(Node<T>*,Node<T>*);

  friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val): value(val),left(0),right(0),parent(0) {}

template <class T>
Node<T>::Node(T val,Node<T> *le,Node<T> *ri,Node<T> *p) 
: value(val),left(le),right(ri),parent(p){}

template <class T>
Node<T>* Node<T>::add(T val){
  if(val<value){
    if(left!=0){
      return left->add(val);
    } else{
      left=new Node<T>(val);
      left->parent =this;
      return left;
    }
  }else{
    if(right !=0){
      return right->add(val);
    }else{
      right=new Node<T>(val);
      right->parent=this;
      return right;
    }
  }
}

template<class T>
Node<T>* Node<T>::find(T val){
  if(val==value){
    return this;
  }else if (val<value){
    if(left!=0)
      return left->find(val);
    else
      return this;
  }else if (val>value){
    if(right!=0)
      return right->find(val);
    else
      return this;
  }
  return 0;
}	

template<class T>
Node<T>* Node<T>::succesor(){
  Node<T> *le,*ri;

  le=left;
  ri=right;

  if(right==0){
    if(left !=0){
      left=0;
    }
    if(le)
      le->parent=0;
    return le;
  }

  if(right->left==0){
    right=right->right;
    if(right)
      right->parent =parent;
    if(ri){
      ri->right=0;
      ri->parent=0;
    }
    return ri;
  }

  Node<T> *p,*c;
  p=right;
  c=right->left;
  while(c->left !=0){
    p=c;
    c=c->left;
  }
  p->left=c->right;
  if(p->left !=0)
    p->left->parent=p;
  c->right=0;
  return c;
}

template<class T>
Node<T>* Node<T>::remove(T val){
  Node<T> *succ,*old;
  if(val<value){
    if(left!=0){
      if(left->value==val){
        old=left;
        succ=left->succesor();
        if(succ !=0){
          succ->left=old->left;
          succ->right=old->right;
          succ->parent=old->parent;
          if(succ->left)
            succ->left->parent=succ;
          if(succ->right)
            succ->right->parent=succ;
        }
        left=succ;
        delete old;
        return this;
      }else{
        return left->remove(val);
      }
    }
  }else if (val >value){
    if(right!=0){
      if(right->value==val){
        old=right;
        succ=right->succesor();
        if(succ!=0){
          succ->left=old->left;
          succ->right=old->right;
          succ->parent=old->parent;
          if(succ->left)
            succ->left->parent=succ;
          if(succ->right)
            succ->right->parent=succ;
        }
        right=succ;
        delete old;
        return this;
      }else{
        return right->remove(val);
      }
    }
  }
  return 0;
}

template<class T>
void Node<T>::removeChilds(){
  if(left !=0){
    left->removeChilds();
    delete left;
    left=0;
  }
  if(right !=0){
    right->removeChilds();
    delete right;
    right=0;
  }
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
  Node<T> *y=x->left;
  x->left = y->right;
  if(y->right)
    y->right->parent =x;
  y->right=x;

  y->parent=x->parent;
  x->parent=y;

  if(y->parent){
    if(y->parent->left && y->parent->left->value==x->value)
      y->parent->left=y;
    else
      y->parent->right=y;
  }
  return y;
}

template<class T>
Node<T>* Node<T>::rot_left(Node<T>*x){
  Node<T> *y=x->right;
  x->right=y->left;
  if(y->left)
    y->left->parent=x;
  y->left=x;

  y->parent=x->parent;
  x->parent=y;

  if(y->parent){
    if(y->parent->left && y->parent->left->value==x->value)
      y->parent->left=y;
    else
      y->parent->right=y;
  }
  return y;
}

template<class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x) {
  while (x->parent != 0) {
    if (x->parent->value == root->value) {
      if (x->parent->left && x->parent->left->value == x->value) {
        rot_right(x->parent);
      } else {
        rot_left(x->parent);
      }
    } else {
      Node<T>* p = x->parent;
      Node<T>* g = p->parent;
      if (g && p->left && g->left &&
          x->value == p->left->value && p->value == g->left->value) {
        rot_right(g);
        rot_right(p);
      } else if (g && p->right && g->right &&
                 x->value == p->right->value && p->value == g->right->value) {
        rot_left(g);
        rot_left(p);
      } else if (g && p->left && g->right &&
                 x->value == p->left->value && p->value == g->right->value) {
        rot_right(p);
        rot_left(g);
      } else if (g && p->right && g->left &&
                 x->value == p->right->value && p->value == g->left->value) {
        rot_left(p);
        rot_right(g);
      }
      // Update root if necessary
      if (g && g->parent == nullptr) {
        root = g;
      }
    }
  }

  return x;
}



template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
  if(left !=0){
    left->inorder(aux);
  }
  if(aux.tellp()!=1){
    aux<<" ";
  }
  aux<<value;
  if(right!=0){
    right->inorder(aux);
  }
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
  if (parent != 0){
    aux << "\n node " << value;
    aux << " parent " << parent->value;
  }else
    aux << "\n root " << value;
  if (left != 0)
    aux << " left " << left->value;
  if (right != 0)
    aux << " right " << right->value;
  aux << "\n";

  if (left != 0) {
    left->print_tree(aux);
  }
  if (right != 0) {
    right->print_tree(aux);
  }
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
  aux << value;
  if (left != 0) {
    aux << " ";
    left->preorder(aux);
  }
  if (right != 0) {
    aux << " ";
    right->preorder(aux);
  }
}

template <class T>
class SplayTree{
private:
  Node<T> *root;
  int length=0;

public:
  SplayTree();
  ~SplayTree();
  bool empty() const;
  void add(T);
  bool find(T);
  void remove(T);
  void removeAll();
  string inorder() const;
  string print_tree() const;
  string preorder() const;
  int size();
};

template <class T>	
SplayTree<T>::SplayTree():root(0) {}

template<class T>
SplayTree<T>::~SplayTree() {
  removeAll();
}

template<class T>
bool SplayTree<T>::empty() const{
  return (root==0);
}

template<class T>
void SplayTree<T>::add(T val){

  if(root !=0){
    Node<T>* added= root->add(val);
    root=root->splay(root,added);
  }else{
    root=new Node<T>(val);
  }
  length+=1;
}

template<class T>
void SplayTree<T>::remove(T val) {
  if (root != 0) {
    Node<T>* found = root->find(val);
    if (found != 0) {
      root = root->splay(root, found);
      if (val == root->value) {
        Node<T>* leftSubtree = root->left;
        Node<T>* rightSubtree = root->right;
        delete root;
        if (leftSubtree) {
          leftSubtree->parent = 0;
          root = leftSubtree;
          Node<T>* newMax = root;
          while (newMax->right) {
            newMax = newMax->right;
          }
          root = root->splay(root, newMax);
          root->right = rightSubtree;
          if (rightSubtree) {
            rightSubtree->parent = root;
          }
        } else {
          root = rightSubtree;
          if (root) {
            root->parent = 0;
          }
        }
      }
    }
    length -= 1;
  }
}

template<class T>
void SplayTree<T>::removeAll(){
  if(root !=0){
    root->removeChilds();
  }
  delete root;
  root=0;
  length=0;
}

template<class T>
bool SplayTree<T>::find(T val){
  if(root!=0){
    Node<T>* found=root->find(val);
    if (found == 0) return false;
    root=root->splay(root,found);
    return(root->value==val);
  }else{
    return false;
  }
}

template<class T>
string SplayTree<T>::inorder() const{
  stringstream aux;

  aux<<"[";
  if(!empty()){
    root->inorder(aux);
  }
  aux<<"]";
  return aux.str();
}

template<class T>
string SplayTree<T>::print_tree() const{
  stringstream aux;

  aux<<"\n ====================== ";
  if(!empty()){
    root->print_tree(aux);
  }
  aux<<" ==================== \n";
  return aux.str();
}

template<class T>
string SplayTree<T>::preorder() const{
  stringstream aux;

  aux<<"[";
  if(!empty()){
    root->preorder(aux);
  }
  aux<<"]";
  return aux.str();
}	

template<class T>
int SplayTree<T>::size(){
  return length;
}
