#include <iostream>

int MaxValue(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

struct Node {
  int value = 0;
  int cnt = 1;
  Node *left = nullptr;
  Node *right = nullptr;
  int height = 0;
};

class AVL {
 private:
  int Height(Node *node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }

  void FixHeight(Node *node) {
    node->height = MaxValue(Height(node->left), Height(node->right)) + 1;
  }

  int BalanceFactor(Node *node) {
    return Height(node->right) - Height(node->left);
  }

  Node *Right(Node *node) {
    Node *left = node->left;
    node->left = left->right;
    left->right = node;
    FixHeight(left);
    FixHeight(node);
    return left;
  }

  Node *Left(Node *node) {
    Node *right = node->right;
    node->right = right->left;
    right->left = node;
    FixHeight(right);
    FixHeight(node);
    return right;
  }

  Node *Balance(Node *node) {
    if (BalanceFactor(node) == 2) {
      if (BalanceFactor(node->right) < 0) {
        node->right = Right(node->right);
      }
      node = Left(node);
    }
    if (BalanceFactor(node) == -2) {
      if (BalanceFactor(node->left) > 0) {
        node->left = Left(node->left);
      }
      node = Right(node);
    }
    return node;
  }

 public:
  Node *root;

  explicit AVL(Node *root) : root(root) {
  }

  Node *Insert(Node *node, const int &value) {
    if (node == nullptr) {
      node = new Node;
      node->value = value;
      node->cnt = 1;
      node->height = 1;
      return node;
    }
    if (value < node->value) {
      node->left = Insert(node->left, value);
    } else if (value > node->value) {
      node->right = Insert(node->right, value);
    } else {
      node->cnt++;
      return node;
    }
    FixHeight(node);
    return Balance(node);
  }

  void DeleteTree(Node *root) {
    if (root == nullptr) {
      return;
    }
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }

  int BinarySearch(Node *node, int target) {
    if (node == nullptr) {
      return 0;
    }
    if (target == node->value) {
      return node->cnt;
    }
    if (target < node->value) {
      return BinarySearch(node->left, target);
    }
    return BinarySearch(node->right, target);
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Node *root = nullptr;
  AVL avl(root);
  for (int i = 0; i < n; ++i) {
    int value = 0;
    std::cin >> value;
    avl.root = avl.Insert(avl.root, value);
  }
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int target = 0;
    std::cin >> target;
    std::cout << avl.BinarySearch(avl.root, target) << "\n";
  }
  avl.DeleteTree(avl.root);
  return 0;
}
