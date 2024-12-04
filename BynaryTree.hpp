
#include <iostream>
namespace Tree {

class BynaryTree {
   protected:
        int key;
        int value;
private: 
  BynaryTree *left = nullptr;
  BynaryTree *right = nullptr;

public:
  BynaryTree(int key, int value) {
    this->key = key;
    this->value = value;
  };
  // ~BynaryTree();

  void add(int key, int value) {
    if (key < this->key) {
      if (this->left == nullptr) {
        this->left = new BynaryTree(key, value);
      } else {
        this->left->add(key, value);
      }
    } else {
      if (this->right == nullptr) {
        this->right = new BynaryTree(key, value);
      } else {
        this->right->add(key, value);
      }
    }
  }

  BynaryTree *search(int key) {
    if (this->key == key) {
      return this;
    } else if (key < this->key) {
      if (this->left == nullptr) {
        return nullptr;
      } else {
        return this->left->search(key);
      }
    } else {
      if (this->right == nullptr) {
        return nullptr;
      } else {
        return this->right->search(key);
      }
    }
  }

  // void print(BynaryTree *node) {
  //   if (node != nullptr) {
  //     print(node->left);
  //     std::cout << node->key << " " << node->value << std::endl;
  //     print(node->right);
  //   }
  // }

  void print() { std::cout << this->key << " " << this->value << std::endl; }

  BynaryTree *GetMin(BynaryTree *node) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->left == nullptr) {
      return node;
    }
    return GetMin(node->left);
  }

  BynaryTree *GetMax(BynaryTree *node) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->right == nullptr) {
      return node;
    }
    return GetMax(node->right);
  }

  BynaryTree *deleteNode(BynaryTree *node, int key) {
    if (node == nullptr) {
      return nullptr;
    }
    if (key < node->key) {
      node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
      node->right = deleteNode(node->right, key);
    } else {
      if (node->left == nullptr || node->right == nullptr) {
        node = (node->left == nullptr) ? node->right : node->left;
      } else {
        BynaryTree *maxInLeft = GetMax(node->left);
        node->key = maxInLeft->key;
        node->value = maxInLeft->value;
        node->left = deleteNode(node->left, maxInLeft->key);
      }
    }
    return node;
  }
};
} // namespace Tree

