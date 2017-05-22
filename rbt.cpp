//cpp file for rbt deletion class, C++ Period 07, Colin Aslett 
#include <iostream>
#include "rbt.h"
#include <cstring>
#include <cmath>

using namespace std;

//initialization of Tree
RBT::RBT(){
  root = new Node();
}
//destruction of the RBT
RBT::~RBT(){
  root->deleteTree();//goes through all of its children and its their children through the deleteTree function
  delete root;
}
//adding a number to the tree
RBT::add(int x){
  preserveProp(first(root,x));//first adding through BST, then checking for tree properties
}
//checking whether the RBT is empty
bool RBT::empty(){
  return root->isSentinel();//if it sentinel then it has no children
}
//preserving the Tree properties
void RBT::preserveProp(Node* current){
  //if it doesnt have a parent then it is the Root and it should always be black
  if(current->parent == 0){
    current->paintBlack();
    return;
  }
  else if(current->parent->black){//everything is fine, nothing needs to be changed
    return;
  }
  else if(current->isrchild() && current->parent->islchild()){
    
  }
  else if(current->uncle()->Red()){

  }
  else if(current->islchild() && current->parent->isrchild()){
    
  }
}

