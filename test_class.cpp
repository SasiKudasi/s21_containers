#include <iostream>
#include "node.hpp"
using namespace std;

template <typename Key, typename Value = void>
class RedBlackTree
{
    using NodeType = Node<Key, Value>;
    NodeType* root = nullptr;

};
