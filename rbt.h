//header file for the RBT class, C++ Period 07 Colin Aslett
#include <iostream>
#pragma once
struct Node{
  int data;//value of the node
  Node* left;//left child of the node
  Node* right;//right child of the node
  Node* parent;//parent of the node
  bool black;//true represents node is black, false means node is red
  //changing value for Node
  Node(int newdata, bool newblack = false) : left(0), right(0), parent(0){
    data = newdata;
    black = newblack;
  }
  //New node creation/Sential node creation
  Node() : left(0), right(0), parent(0){
    data = 0;
    black = true;
  }
  //if it has no children then it is sentinel and returns true
  bool isSentinel(){
    return left == 0 && right == 0;
  }
  //returns whether node is red
  bool Red(){
    return !black;
  }
  //change the Nodes value to black
  void paintBlack(){
    black = true;
  }
  //change the Nodes value to red
  void paintRed(){
    black = false;
  }
  //returning the grandparent of the Node
  Node* grandparent(){
    return parent == 0 ? 0 : parent->parent;
  }
  //returning the uncle of the Node
  Node* uncle(){
    Node* current = grandparent();
    if(current == 0){//not possible to have a uncle if there is no grandparent
      return 0;
    }
    return current->left == parent ? current->right : current->right;
  }
  //returing the sibling of the Node
  Node* sibling(){
    if(parent == 0){
      return 0;
    }
    return parent->left == this ? parent->right : parent->left;
  }
  void changeToSentinel(){
    deleteTree();
    left = 0;
    right = 0;
    paintBlack();
    data = 0;
  }
  //the node that has no children now has children
  void addSentinelNode(){
    setLeft(new Node());
    setRight(new Node());
  }
  //setting the Nodes left child
  void setLeft(Node* current){
    left = current;
    if(current != 0){
      current->parent = this;//setting the new nodes parent to the original node
    }
  }
  //setting the Nodes right child
  void setRight(Node* currentx){
    right = currentx;
    if(currentx != 0){
      currentx->parent = this;//setting the new nodes parent to the original node
    }
  }
  //returning true/false depending on it is the left/right child of parent
  bool islchild(){
    return parent->left == this;
  }
  bool isrchild(){
    return parent->right == this;
  }
  //if one returns false then it points to a non-sentinel child, if both are true then it returns a sentinal child
  Node* nonChild(){
    return left->isSentinel() ? right : left;
  }
  //deleting the tree below the node
  void deleteTree(){
    if(left != 0){
      left->deleteTree();
    }
    if(right != 0){
      right->deleteTree();
    }
    delete left;
    delete right;
  }
  //Node deconstructor
  ~Node(){
  }
};
class RBT{
 public:
  RBT();
  ~RBT();
  void add(int x);//adding a number/node to the tree
  bool remove(int x);//removing a certain node, have to know the value first, true means it was able to, false means it couldnt find the number
  void print();//print out tree
  bool empty();//returns whether the tree is empty or not
  bool inTree(int x);//returns whether the number is in tree
 private:
  Node* root;//top of the tree
  Node* first(Node* current, int x);//inserting BST way first
  int level(Node* root, int lvl);//returning number of levels in tree
  void populate(int* &array,int x, Node* current);
  void preserveProp(Node* current);//preserving the RBT properties
  Node* search(Node* current, int x);//looking to see if a certain node is in the tree
  void leftRotation(Node* current);
  void rightRotation(Node* current);
  Node** parentptr(Node* current);
  void replace(Node* current);
  Node* deltx(Node* current);//deleting a node
};
