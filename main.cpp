#include "redblack.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(){
  redblack tree;
  char input[50];
  while (true) {
    cout << "what do you want" << endl;
    cout << "commands: insert, remove, search, tree, quit" << endl;
    cin >> input;
    //put number into tree
    if (strcmp(input, "insert") == 0) {
      int value;
      cout << "insert number: " << endl;
      cin >> value;
      tree.insert(value);
    }
    //remove number from tree
    else if (strcmp(input, "remove") == 0) {
      int value;
      cout << "remove number: " << endl;
      cin >> value;
      tree.remove(value);
    }
    //find a number in tree
    else if (strcmp(input, "search") == 0) {
      int value;
      cout << "what number?: " << endl;
      cin >> value;
      if (tree.search(value)) {
	cout << "found it" << endl;
      }
      else {
	cout << "didn't find it" << endl;
      }
    }
    //print tree
    else if (strcmp(input, "tree") == 0) {
      tree.tree();
    }
    //quit
    else if (strcmp(input, "quit") == 0) {
      break;
    }
  }
}
