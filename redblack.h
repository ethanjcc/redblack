struct Node {
  int data;
  Node* left;
  Node* right;
  Node(int value);
  Node* parent;
  Color red;
  Color black;
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
  Node* remove(Node* root, int value);
  bool search(Node* root, int value) const;
  void tree(Node* root, int depth) const;
};
