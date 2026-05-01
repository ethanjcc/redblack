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
  db = nullptr;
  sibling = nullptr;
}

//constructor
redblack::redblack() {
  root = nullptr;
}

//destructor
redblack::~redblack() {

}

//update root
//help from copilot to update the inserted value from fixInsert
void redblack::insert(int value) {
  Node* inserted = nullptr;
  root = insert(root, value, inserted);
  fixInsert(inserted);
}

//code for inserting a number into the tree
Node* redblack::insert(Node* root, int value, Node*& inserted) {
  if (root == nullptr) {
    inserted = new Node(value);
    return inserted;
  }
  if (value < root->data) {
    root->left = insert(root->left, value, inserted);
    root->left->parent = root;
  }
  else if (value > root->data) {
    root->right = insert(root->right, value, inserted);
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
	cout << "case 1" << endl;
	node->parent->color = black;
	uncle->color = black;
	grandparent->color = red;
	node = grandparent;
      }
      else {
        //case 2
	if (node == node->parent->left) {
	  cout << "case 2" << endl;
	  node = node->parent;
	  rotateRight(node);
        }
        //case 3
	cout << "case 3" << endl;
        node->parent->color = black;
        grandparent->color = red;
        rotateLeft(grandparent);
      }
    //uncle is on left
    } else {
      Node* uncle = grandparent->right;
      //case 1
      if (uncle != nullptr && uncle->color == red){
	cout << "case 1" << endl;
	node->parent->color = black;
	uncle->color = black;
	grandparent->color = red;
	node = grandparent;
      }
      else {
	//case 2
	if (node == node->parent->right) {
	  cout << "case 2" << endl;
	  node = node->parent;
	  rotateLeft(node);
	}
	//case 3
	cout << "case 3" << endl;
	node->parent->color = black;
	grandparent->color = red;
	rotateRight(grandparent);
      }
    }
  }
  root->color = black;
}

void redblack::rotateLeft(Node* nextC) {
  //nextP is the child of nextC and will become the new parent after rotating
  Node* nextP = nextC->right;
  nextC->right = nextP->left;
  //if nothing on the left then the new parents left parent is the new child
  if (nextP->left != nullptr) {
    nextP->left->parent = nextC;
  }
  //link them
  nextP->parent = nextC->parent;
  //if the new child does not have a parent then the new parent is the root
  if (nextC->parent == nullptr) {
    root = nextP;
  }
  //if the new child's parent is on the left then that parent is the new parent
  else if (nextC == nextC->parent->left) {
    nextC->parent->left = nextP;
  }
  //if the new child's parent is on the right then that parent is the new parent
  else {
    nextC->parent->right = nextP;
  }
  //rotate them
  nextP->left = nextC;
  nextC->parent = nextP;
}

//same thing as above but right instead of left
void redblack::rotateRight(Node* nextC) {
  Node* nextP = nextC->left;
  nextC->left = nextP->right;
  if (nextP->right != nullptr) {
    nextP->right->parent = nextC;
  }
  nextP->parent = nextC->parent;
  if (nextC->parent == nullptr) {
    root = nextP;
  }
  else if (nextC == nextC->parent->right) {
    nextC->parent->right = nextP;
  }
  else {
    nextC->parent->left = nextP;
  }
  nextP->right = nextC;
  nextC->parent = nextP;
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

void redblack::fixRemove(Node* &root, Node* node) {
  //when its a double black
  while(node != root && node->color == black) {
    //if its on the left of the parent its sibling is on the right
    if (node == node->parent->left) {
      //left side case 1
      node* sibling = node->parent->right;
      if (sibling->color == red) {
	sibling->color = black;
	node->parent->color = red;
	rotateLeft(root, node->parent);
	sibling = node->parent->right;
      }
    }
    //if its on the right of the parent its sibling is on the left
    else {
      //right side case 1
      node* sibling = node->parent->left;
      if (sibling->color == red) {
	sibling->color = black;
	node->parent->color = red;
	rotateRight(root, node->parent);
	sibling = node->parent->left;
      }
    }
  }
  node->color = black;
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
  cout << root->data << " ";
  if (root->color == red) {
    cout << "r" << endl;
  }
  else {
    cout << "b" << endl;
  }
  tree(root->left, depth + 1);
}
