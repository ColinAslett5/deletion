//Colin Aslett, C++ peroid 07, RBT deletion, WITH LOADS OF HELP FROM ARTUR, SO MUCH IM GONNA CITE HIM AS A SOURCE
#include <iostream>
#pragma once

struct Node{
  int value;//number held by numb
  Node* left, *right, *parent;
  bool black;
  Node(int newValue, bool newBlack = false) : left(0), right(0), parent(0){
    value = newValue;
    black = newBlack;
  }
  Node() : left(0), right(0), parent(0){
    value = 0;
    black = true;
  }//checking whether the node has any children
  bool isSentinel(){
    return left == 0 && right == 0;
  }
  //returns whether the node is opposite of black being true
  bool isRed(){
    return !black;
  }
  //paitning the node black
  void paintBlack(){
    black = true;
  }
  //paitning the node red
  void paintRed(){
    black = false;
  }
  //turning the node sentinel, No children
  void makeSentinel(){
    deleteSubtrees();
    left = 0;
    right = 0;
    paintBlack();
    value = 0;
  }//adding sentinel leafs to a node
  void addSentinelLeafs(){
    setLeft(new Node());
    setRight(new Node());
  }
  //returning the grandparent of the node
  Node* grandparent(){
    return parent == 0 ? 0 : parent->parent;
  }
  //returning the uncle of the node
  Node* uncle(){
    Node* gp = grandparent();
    if(gp == 0){
      return 0;
    }
    return gp->left == parent ? gp->right : gp->left;
  }
  //returning if node is the sibling of something
  Node* sibling(){
    if(parent == 0){
      return 0;
    }
    return parent->left == this ? parent->right : parent->left;
  }
  //setting nodes left to a new node
  void setLeft(Node* node){
    left = node;
    if(node!=0){
      node->parent = this;
    }
  }
  //setting nodes right to a new node
  void setRight(Node* node){
    right = node;
    if(node!=0){
      node->parent = this;
    }
  }
  Node* nonSentinelChild(){
    return left->isSentinel() ? right : left;
  }
  //checking to see if node is the lchild of something
  bool isLeftChild(){
    return parent->left == this;
  }
  //checking to see if node is the rchild of something
  bool isRightChild(){
    return parent->right == this;
  }
  //deleting the subtree of the node, everything below it
  void deleteSubtrees(){
    if(left!=0){
      left->deleteSubtrees();
    }
    if(right!=0){
      right->deleteSubtrees();
    }
    delete left;
    delete right;
  }
  ~Node(){}
};

class RedBlackTree{
  public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(int num);
    bool isInTree(int num);
    bool remove(int num);
    bool isEmpty();
    void print();
  private:
    Node* root;
    Node* insertInitial(Node * node, int num);
    void preserveTreeProperties(Node * inserted);
    int getNumLevels(Node* root, int level);
    void populateArray(int *& array, int index, Node* node);
    Node* find(Node * node, int num);
    void removeSingleNode(Node* toRemove);
    void leftRotation(Node* formerChild);
    void rightRotation(Node* formerChild);
    Node** parentPtrTo(Node* child);
    void replaceParentOf(Node* child);
    void rebalance(Node* node);
};
