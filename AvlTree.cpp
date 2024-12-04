#include "BynaryTree.hpp"
#include <iostream>
namespace Tree {
/*
 *& -- ссылка на указатель, через нее можно изменять указатель
 */
class AvlTree {
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

  void RightRotate(AvlTree *&tree) {
    AvlTree *newRoot = tree->left; // Новый корень — левый ребенок
    tree->left = newRoot->right; // Перемещаем правое поддерево нового корня
    newRoot->right = tree; // Текущий корень становится правым ребенком
    updateHeight(tree); // Обновляем высоту старого корня
    updateHeight(newRoot); // Обновляем высоту нового корня
    tree = newRoot;        // Обновляем корень
  }
  void LeftRotate(AvlTree *&tree) {
    AvlTree *newRoot = tree->right; // Новый корень — правый ребенок
    tree->right = newRoot->left; // Перемещаем левое поддерево нового корня
    newRoot->left = tree; // Текущий корень становится левым ребенком
    updateHeight(tree); // Обновляем высоту старого корня
    updateHeight(newRoot); // Обновляем высоту нового корня
    tree = newRoot;        // Обновляем корень
  }

  void balance(AvlTree *&tree) {
    if (tree == nullptr)
      return;
    int balanceFactor = getBalance(tree);
    if (balanceFactor <= -2) {
      if (getBalance(tree->left) > 0) {
        LeftRotate(tree->left); // Левый поворот левого поддерева
      }
      RightRotate(tree); // Правый поворот
    } else if (balanceFactor >= 2) {
      if (getBalance(tree->right) < 0) {
        RightRotate(tree->right); // Правый поворот правого поддерева
      }
      LeftRotate(tree); // Левый поворот
    }
  }

  void insert(AvlTree *&tree, int key, int value) {
    if (tree == nullptr) {
      tree = new AvlTree(key, value);
      return;
    }

    if (key < tree->key) {
      insert(tree->left, key, value);
    } else /*if (key > tree->key) */ { // если раскоментировать то не будет
                                       // возможности вставлять дубликаты в
                                       // структуру
      insert(tree->right, key, value);
    }
    // else {
    //   // Обновление значения при совпадении ключа
    //   tree->value = value;
    // }
    updateHeight(tree);
    balance(tree);
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
  tree->insert(tree, 10, 200);
  tree->insert(tree, 20, 200);
  tree->insert(tree, 5, 50);
  tree->insert(tree, 15, 150);
  tree->insert(tree, 20, 200);
  tree->insert(tree, 25, 250);

  tree->print(tree);
  return 0;
}