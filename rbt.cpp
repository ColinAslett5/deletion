//Colin Aslett, C++ period 07, CPP file for the header file, contains all the main functions
#include <iostream>
#include "rbt.h"
#include <cmath>
#include <cstring>

using namespace std;

RedBlackTree::RedBlackTree(){//initializing the RBT
    root = new Node();
}

RedBlackTree::~RedBlackTree(){//destroying the tree below root, which is basically everything
    root->deleteSubtrees();
    delete root;
}
//returns whether RBT is empty or not
bool RedBlackTree::isEmpty(){
    return root->isSentinel();
}
//inserting via from the title.cpp file, so it has to go through BST and then the properties of RBT
void RedBlackTree::insert(int num){
    preserveTreeProperties(insertInitial(root, num));
}

void RedBlackTree::preserveTreeProperties(Node * inserted){
  //it is the root, if it has no parents
    if(inserted->parent == 0){
        inserted->paintBlack();
        return;
    }
    else if(inserted->parent->black){//Nothing needs to change
      return;
    }
    else if(inserted->uncle()->isRed()){
        inserted->parent->paintBlack();
        inserted->uncle()->paintBlack();
        inserted->grandparent()->paintRed();
        preserveTreeProperties(inserted->grandparent());
        return;
    }
    if(inserted->isRightChild() && inserted->parent->isLeftChild()){
        leftRotation(inserted);
        inserted = inserted->left;
    }
    else if(inserted->isLeftChild() && inserted->parent->isRightChild()){
        rightRotation(inserted);
        inserted = inserted->right;
    }
    inserted->grandparent()->paintRed();
    inserted->parent->paintBlack();
    if(inserted->isLeftChild()){
        rightRotation(inserted->parent);
    }
    else{
        leftRotation(inserted->parent);
    }
}
//revmoing based on the CPP file in title.cpp, still has to go through the private functions
bool RedBlackTree::remove(int num){
    Node* toRemove = find(root, num);
    if(toRemove == 0){//the node was not found
        return false;
    }
    if(!toRemove->left->isSentinel() && !toRemove->right->isSentinel()){
        Node* successor = toRemove->right;
        while(!successor->left->isSentinel()){
            successor = successor->left;
        }
        toRemove->value = successor->value;
        toRemove = successor;
    }
    removeSingleNode(toRemove);
    return true;//it was able to succesfully find the node and removal can continue in removesingklenode
}

void RedBlackTree::removeSingleNode(Node* toRemove){
    //Removal of a node that has at most one non-sentinel child.
    if(toRemove->isRed()){
        toRemove->makeSentinel();
        return;
    }
    Node* child = toRemove->nonSentinelChild();
    if(child->isRed()){
        replaceParentOf(child);
        child->paintBlack();
        return;
    }
    toRemove->makeSentinel();
    rebalance(toRemove);
}
//Rebalancing the RBT, based on the deletions from removesinglenode
void RedBlackTree::rebalance(Node* node){
  //Node is the root if its parent == null
    if(node->parent == 0){
        return;
    }
    Node* sibling = node->sibling();
    if(sibling->isRed()){
        node->parent->paintRed();
        sibling->paintBlack();
        if(node->isLeftChild()){
            leftRotation(sibling);
        }
        else{
            rightRotation(sibling);
        }
    }
    sibling = node->sibling();
    if(node->parent->black && sibling->black && sibling->left->black && sibling->right->black){
        sibling->paintRed();
        rebalance(node->parent);
        return;
    }
    if(node->parent->isRed() && sibling->black && sibling->left->black && sibling->right->black){
        sibling->paintRed();
        node->parent->paintBlack();
        return;
    }
    //sibling must be black.
    if(node->isLeftChild() && sibling->right->black){//Then sibling->left is red since sibling's both children aren't black
        //Exchange colors of sibling and its left child, then rotate right through sibling.
        sibling->left->paintBlack();
        sibling->paintRed();
        rightRotation(sibling->left);
    }
    else if(node->isRightChild() && sibling->left->black){// sibling->right is red.
        sibling->right->paintBlack();
        sibling->paintRed();
        leftRotation(sibling->right);
        //Do not return.
    }
    sibling = node->sibling();
    //Exchange colors of sibling and parent (parent can be either color but sibling is black):
    sibling->black = node->parent->black;
    node->parent->paintBlack();
    if(node->isLeftChild()){
        sibling->right->paintBlack();
        leftRotation(sibling);
    }
    else{//node is right child and sibling->left is red
        sibling->left->paintBlack();
        rightRotation(sibling);
    }
}
//printing out the tree
void RedBlackTree::print(){
    int numLevels = getNumLevels(root, 0);
    //This is the same print method as the one that I had in insertion and in projects before that
    int nodes[(int)(pow(2, numLevels)) - 1];
    int* arrPtr = nodes;
    memset(nodes, 0, sizeof(nodes));
    populateArray(arrPtr, 0, root);
    
    int index = 0;
    for(int l=1; l <= numLevels; l++){
        for(int i=0; i < pow(2, numLevels-l)-1; i++){
            cout << ' ';
        }
        //Nodes:
        for(int n=0; n < pow(2, l-1); n++){
            if(nodes[index] > 0){
                cout << nodes[index] << 'B';
            }
            else if(nodes[index] < 0){
                cout << -nodes[index] << 'R';
            }
            else{
                cout << ' ';
            }
            index++;
            for(int i=0; i < pow(2, numLevels - l + 1) - 1; i++){
                cout << ' ';
            }
	}
        cout << endl;
    }
}
//initially insert, through the BST method
Node* RedBlackTree::insertInitial(Node * child, int num){
  //addign via BST method, before it is checked through the RBT properties
    if(child->isSentinel()){
      child->value = num;
      child->paintRed();
        child->addSentinelLeafs();
        return child;
    }
    if(num < child->value){
        return insertInitial(child->left, num);
    }
    else{
        return insertInitial(child->right, num);
    }
}
//returns the levels that the tree has
int RedBlackTree::getNumLevels(Node* currentRoot, int level = 0){
    if(currentRoot == 0){
        return level;
    }
    //has to find the max level on either the right or left side
    return max(getNumLevels(currentRoot->left, level + 1), getNumLevels(currentRoot->right, level + 1));
}
//creating an array with all of the information of the nodes
void RedBlackTree::populateArray(int *& array, int index, Node* node){
    if(node == 0){
        return;
    }
    array[index] = node->black ? node->value : -node->value;//information that is stored in the array
    populateArray(array, index*2+1, node->left);
    populateArray(array, index*2+2, node->right);
}
//finding a specific node in the RBT
Node* RedBlackTree::find(Node * currentRoot, int num){
    if(currentRoot->isSentinel()){//Return null if no such node
        return 0;
    }
    if(currentRoot->value == num){
        return currentRoot;
    }
    else if(num > currentRoot->value){
        return find(currentRoot->right, num);
    }
    else{
        return find(currentRoot->left, num);
    }
}
//finds if a node is in the tree, first step is by looking at users inputted number
bool RedBlackTree::isInTree(int num){
    return find(root, num) != 0;
}
//left rotation, same as RBT insertion
void RedBlackTree::leftRotation(Node* formerChild){
    Node* formerParent = formerChild->parent;
    *parentPtrTo(formerParent) = formerChild;
    formerChild->parent = formerChild->grandparent();
    formerParent->setRight(formerChild->left);
    formerChild->setLeft(formerParent);
}
//right rotation, smae as RBT deletion
void RedBlackTree::rightRotation(Node* formerChild){
    Node* formerParent = formerChild->parent;
    *parentPtrTo(formerParent) = formerChild;
    formerChild->parent = formerChild->grandparent();
    formerParent->setLeft(formerChild->right);
    formerChild->setRight(formerParent);
}

Node** RedBlackTree::parentPtrTo(Node* child){
    Node** ptr;
    if(child->parent == 0){
        ptr = &root;
    }
    else if(child == child->parent->left){
        ptr = &(child->parent->left);
    }
    else{
        ptr = &(child->parent->right);
    }
    return ptr;
}

void RedBlackTree::replaceParentOf(Node* child){
    Node* parent = child->parent;
    Node** childPtr = parentPtrTo(child);
    child->parent = child->grandparent();
    (*parentPtrTo(parent)) = child;
    *childPtr = 0;
    parent->deleteSubtrees();
    delete parent;
}
