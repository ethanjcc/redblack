#include "redblack.h"
#include <iostream>
#include <cstring>

using namespace std;

Node::Node(int value) {
  data = value;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  Color = red;
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
