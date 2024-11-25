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

  Node *LowerBound(Node *node, int i) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->value >= i) {
      Node *tmp_node = LowerBound(node->left, i);
      if (tmp_node != nullptr) {
        return tmp_node;
      }
      return node;
    }
    return LowerBound(node->right, i);
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Node *root = nullptr;
  AVL avl(root);
  char prev_command = '0';
  int prev_value = 0;
  for (int i = 0; i < n; ++i) {
    char command = '0';
    std::cin >> command;
    if (command == '+') {
      int value = 0;
      std::cin >> value;
      if (prev_command == '+' || prev_command == '0') {
        avl.root = avl.Insert(avl.root, value);
      } else {
        avl.root = avl.Insert(avl.root, ((prev_value + value) % 1000000000));
      }
    }
    if (command == '?') {
      int value = 0;
      std::cin >> value;
      Node *node = avl.LowerBound(avl.root, value);
      if (node != nullptr) {
        prev_value = node->value;
        std::cout << prev_value << "\n";
      } else {
        prev_value = -1;
        std::cout << prev_value << "\n";
      }
    }
    prev_command = command;
  }
  avl.DeleteTree(avl.root);
  return 0;
}
