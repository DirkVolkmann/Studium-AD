typedef int bt_type;

class BtElement {
 public:
  bt_type value;
  BtElement *left;
  BtElement *right;
};

class BinaryTree {
 private:
  BtElement *root;
  void InsertAtPosition(BtElement *position, BtElement *element);
  void DeleteRecusive(BtElement *current_root);
 public:
 BinaryTree();
 ~BinaryTree();
  void Insert(bt_type);
  void Delete(bt_type);
  bool Conatins(bt_type);
  void Print();
};

BinaryTree::BinaryTree() {
  root = NULL;
}

BinaryTree::~BinaryTree() {
  DeleteRecusive(root);
}

void BinaryTree::InsertAtPosition(BtElement *position, BtElement *element) {

}

void BinaryTree::DeleteRecusive(BtElement *current_root) {
  if (root == NULL) return;
  if (root->left != NULL) DeleteRecusive(root->left);
  if (root->right != NULL) DeleteRecusive(root->right);
  delete root;
}

void BinaryTree::Insert(bt_type value) {
  BtElement *current = root;
  while (current != NULL) {
    if (current->value <= value) current = current->left;
    else current = current->right;
  }
  current->value = value;
}

void BinaryTree::Delete(bt_type value) {
  
}

bool BinaryTree::Conatins(bt_type value) {
  BtElement *current = root;
  while (current != NULL) {
    if (current->value == value) return true;
    if (current->value < value) current = current->left;
    else current = current->right;
  }
  return false;
}

void BinaryTree::Print() {

}