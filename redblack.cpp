#include "redblack.h"
#include <iostream>
#include <cstring>

using namespace std;

Node::Node(int value) {
  data = value;
  node = nullptr;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  color = red;
}

//constructor
redblack::redblack() {
  root = nullptr;
}

//destructor
redblack::~redblack() {

}

//update root
void redblack::insert(int value) {
  root = insert(root, value);
}

//code for inserting a number into the tree
Node* redblack::insert(Node* root, int value) {
  if (root == nullptr) {
    return new Node(value);
  }
  if (value < root->data) {
    root->left = insert(root->left, value);
    root->left->parent = root;
  }
  else if (value > root->data) {
    root->right = insert(root->right, value);
    root->right->parent = root;
  }
  return root;
}

//fixes the tree after inserting
//help from copilot
void redblack::fixInsert(Node* node) {
  //only if the parent is red
  while (node->parent != nullptr && node->parent->color == red) {
    Node* grandparent = node->parent->parent;
    Node* uncle = nullptr;
    //case for if the uncle is on the right
    if (node->parent == grandparent->right) {
      Node* uncle = grandparent->left;
      //case 1
      if (uncle != nullptr && uncle->color == red) {
	node->parent->color = black;
	uncle->color = black;
	grandparent->color = red;
	node = grandparent;
      }
      else {
	//case 2
	if (node == node->parent->left) {
	  node = node->parent;
	  rotateRight(node);
	}
	//case 3
	node->parent->color = black;
	grandparent->color = red;
	rotateLeft(grandparent);
      }
    //uncle is on left
    else {
      Node* uncle = grandparent->right;
      //case 1
      if (uncle != nullptr && uncle->color == red){
        node->parent->color = black;
	uncle->color = black;
	grandparent->color = red;
	node = grandparent;
      }
      else {
	//case 2
	if (node == node->parent->right) {
	  node = node->parent;
	  rotateLeft(node);
	}
	//case 3
	node->parent->color = black;
	grandparent->color = red;
	rotateRight(grandparent);
      }
    }
  }
}

//update function
//copilot used to understand need for const
bool redblack::search(int value) const {
  return search(root, value);
}

//code for finding a number in the tree
bool redblack::search(Node* root, int value) const {
  if (root == nullptr) {
    return false;
  }
  //not found
  if (value == root->data) {
    return true;
  }
  //found
  if (value < root->data) {
    return search(root->left, value);
  }
  else {
    return search(root->right, value);
  }
}

//update root
void redblack::remove(int value) {
  root = remove(root, value);
}

//code for removing a number in the tree
//help from copilot used
Node* redblack::remove(Node* root, int value) {
  //no number found
  if (root == nullptr) {
    return nullptr;
  }
  if (value < root->data) {
    root->left = remove(root->left, value);
  }
  else if (value > root->data) {
    root->right = remove(root->right, value);
  }
  else {
    //no child
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      return nullptr;
    }
    //one child on the right
    if (root->left == nullptr) {
      Node* temp = root->right;
      delete root;
      return temp;
    }
    //one child on the left
    if (root->right == nullptr) {
      Node* temp = root->left;
      delete root;
      return temp;
    }
    //two children. Has to find a node to inherit its spot
    Node* inherit = root->right;
    while (inherit->left != nullptr) {
      inherit = inherit->left;
    }
    root->data = inherit->data;
    //delete the node
    root->right = remove(root->right, inherit->data);
  }
  return root;
}

//public tree print
void redblack::tree() const {
  tree(root, 0);
}

//tree printing code
void redblack::tree(Node* root, int depth) const {
  if (root == nullptr) {
    return;
  }
  //right subtree
  tree(root->right, depth + 1);
  //indent if needed
  for (int i = 0; i < depth; i++){
    cout << "\t";
  }
  cout << root->data << endl;
  tree(root->left, depth + 1);
}
