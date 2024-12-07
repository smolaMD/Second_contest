#include <iostream>

struct Node {
  int value = 0;
  int cnt = 1;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
};

class SplayTree {

 public:
  Node *root;

  explicit SplayTree(Node *root) : root(root) {
  }

  Node *Insert(Node *node, const int &value) {
    if (node == nullptr) {
      node = new Node;
      node->value = value;
      node->cnt = 1;
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
    return Splay(node);
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

 private:
  void SetParent(Node *child, Node *parent) {
    if (child != nullptr) {
      child->parent = parent;
    }
  }

  void KeepParent(Node *vertex) {
    SetParent(vertex->left, vertex);
    SetParent(vertex->right, vertex);
  }

  void Rotate(Node *child, Node *parent) {
    Node *g_parent = parent->parent;
    if (g_parent) {
      if (g_parent->left == parent) {
        g_parent->left = child;
      } else {
        g_parent->right = child;
      }
    }
    child->parent = g_parent;
    if (parent->right == child) {
      parent->right = child->left;
      child->left = parent;
    } else {
      parent->left = child->right;
      child->right = parent;
    }
    KeepParent(child);
    KeepParent(parent);
  }

  Node *Splay(Node *vertex) {
    if (!vertex->parent) {
      return vertex;
    }
    if (!vertex->parent->parent) {
      Rotate(vertex, vertex->parent);
      return vertex;
    }
    Node *parent = vertex->parent;
    Node *g_parent = parent->parent;
    if ((g_parent->left == parent) == (parent->left == vertex)) {
      Rotate(parent, g_parent);
      Rotate(vertex, parent);
    } else {
      Rotate(vertex, parent);
      Rotate(vertex, g_parent);
    }
    return Splay(vertex);
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Node *root = nullptr;
  SplayTree avl(root);
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
