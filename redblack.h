//enum from copilot because it said red black and color were not defined
enum Color { red, black };

struct Node {
  int data;
  Node* left;
  Node* right;
  Node(int value);
  Node* parent;
  Color color;
  Node* node;
  Node* nextC;
  Node* db;
  Node* sibling;
};

class redblack {
 public:
  redblack();
  ~redblack();
  void insert(int value);
  void removeRoot(int value);
  bool search(int value) const;
  void tree() const;
  
 private:
  Node* root;
  Node* insert(Node* root, int value, Node*& inserted);
  void fixInsert(Node* node);
  void rotateLeft(Node* node);
  void rotateRight(Node* node);
  Node* remove(Node* node, Node* root, int value);
  void fixRemove(Node* &root, Node* node);
  bool search(Node* root, int value) const;
  void tree(Node* root, int depth) const;
};
