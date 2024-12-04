#include "BynaryTree.hpp"
#include <iostream>
namespace Tree {

class AvlTree  {
private:
  int key;
  int value;
  int height = 0;
  AvlTree *left = nullptr;
  AvlTree *right = nullptr;

public:
  AvlTree(int key, int value) {
    this->key = key;
    this->value = value;
  }
  //~AvlTree();

  void updateHeight(AvlTree *tree) {

    int leftHeight = getHeight(tree->left);
    int rightHeight = getHeight(tree->right);
    tree->height = std::max(leftHeight, rightHeight) + 1;
  }
  int getHeight(AvlTree *tree) {
    return ((tree == nullptr) ? -1 : tree->height);
  }

  int getBalance(AvlTree *tree) {
    if (tree == nullptr) {
      return 0;
    }
    return getHeight(tree->right) - getHeight(tree->left);
  }

  void RightRotate(AvlTree *tree) {
     AvlTree *newRoot = tree->left;       // Новый корень — левый ребенок
    tree->left = newRoot->right;        // Перемещаем правое поддерево нового корня
    newRoot->right = tree;              // Текущий корень становится правым ребенком
    updateHeight(tree);                 // Обновляем высоту старого корня
    updateHeight(newRoot);              // Обновляем высоту нового корня
    tree = newRoot;                     // Обновляем корень
  }
  void LeftRotate(AvlTree *tree) {
    AvlTree *newRoot = tree->right;     // Новый корень — правый ребенок
    tree->right = newRoot->left;        // Перемещаем левое поддерево нового корня
    newRoot->left = tree;               // Текущий корень становится левым ребенком
    updateHeight(tree);                 // Обновляем высоту старого корня
    updateHeight(newRoot);              // Обновляем высоту нового корня
    tree = newRoot;                     // Обновляем корень
  }

  void balance(AvlTree *tree) {
    auto balance = getBalance(tree);
    if (balance == -2) {
      if (getBalance(tree->left) == 1)
        LeftRotate(tree->left);
      RightRotate(tree);
    } else if (balance == 2) {
      if (getBalance(tree->right) == -1)
        RightRotate(tree->right);
      LeftRotate(tree);
    }
  }

  void insert(int key, int value) {
    if (key < this->key) {
      if (this->left == nullptr) {
        this->left = new AvlTree(key, value);
      } else {
        this->left->insert(key, value);
      }
    } else {
      if (this->right == nullptr) {
        this->right = new AvlTree(key, value);
      } else {
        this->right->insert(key, value);
      }
    }
    updateHeight(this);
    balance(this);
  }

  void print(AvlTree *node) {
    if (node != nullptr) {
      print(node->left);
      std::cout << node->key << " " << node->value << std::endl;
      print(node->right);
    }
  }
};
} // namespace Tree

int main() {
  Tree::AvlTree *tree = new Tree::AvlTree(5, 2);
  tree->insert(2, 2);
  tree->insert(3, 3);
  tree->insert(4, 4);
  tree->insert(5, 5);
  tree->insert(6, 6);

  tree->print(tree);
  return 0;
}