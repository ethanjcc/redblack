struct Node {
  int data;
  Node* left;
  Node* right;
  Node(int value);
  Node* parent;
  color red;
  color black;
  Node* node;
};

class redblack {
 public:
  redblack();
  ~redblack();
  void insert(int value);
  void remove(int value);
  bool search(int value) const;
  void tree() const;
 private:
  Node* root;
  Node* insert(Node* root, int value);
  void fixInsert(Node* node);
  Node* remove(Node* root, int value);
  bool search(Node* root, int value) const;
  void tree(Node* root, int depth) const;
};
