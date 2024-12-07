#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "RBTree.h"
#include <functional>
#include <vector>

namespace s21 {

template <typename Key, typename T, typename Compare = std::less<Key>>
class map {
public:
  // Typedefs
  using key_type = Key;
  using mapped_type = T;
  using compare_type = Compare;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename RBTree<key_type, value_type, compare_type>::iterator;
  using const_iterator =
      typename RBTree<key_type, value_type, compare_type>::const_iterator;
  using size_type = size_t;
  using node_type = typename RBTree<key_type, value_type, compare_type>::Node;

  // Map Member functions
  map() {}
  explicit map(std::initializer_list<value_type> const &items) {
    for (auto i : items) {
      insert(i);
    }
  }
  map(const map &m) {
    for (auto i : m) {
      insert(i);
    }
  }
  map(map &&m) noexcept : tree_(std::move(m.tree_)) {}
  map &operator=(const map &m) noexcept {
    tree_ = std::copy(m.tree_);
    return *this;
  }
  map &operator=(map &&m) noexcept {
    tree_ = std::move(m.tree_);
    return *this;
  }
  ~map() {}

  // Map Element access
  mapped_type &at(const key_type &key) {
    auto i = iterator(tree_.find(key));
    if (i == end()) {
      throw std::out_of_range("map::at");
    }
    return (*i).second;
  }
  mapped_type &operator[](const key_type &key) noexcept {
    auto i = iterator(tree_.find(key));
    if (i == end()) {
      i = insert(key, mapped_type()).first;
    }
    return (*i).second;
  }

  // Map Iterators
  iterator begin() const noexcept { return tree_.begin(); }
  iterator end() const noexcept { return tree_.end(); }

  // Map Capacity
  bool empty() const noexcept { return tree_.size() == 0; }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Map Modifiers
  void clear() noexcept { tree_.delete_tree(); }
  std::pair<iterator, bool> insert(const value_type &value) noexcept {
    std::pair<iterator, bool> res;
    node_type *x = tree_.insert(value.first, value);
    res.second = true;
    if (!x) {
      x = tree_.find(value.first);
      res.second = false;
    } else {
      tree_.fix(x);
    }
    res.first = iterator(x);
    return res;
  }
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) noexcept {
    std::pair<iterator, bool> res;
    node_type *x = tree_.insert(key, value_type(key, obj));
    res.second = true;
    if (!x) {
      x = tree_.find(key);
      res.second = false;
    } else {
      tree_.fix(x);
    }
    res.first = iterator(x);
    return res;
  }
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) noexcept {
    std::pair<iterator, bool> res;
    node_type *x = tree_.insert(key, value_type(key, obj));
    res.second = true;
    if (!x) {
      x = tree_.find(key);
      operator[](key) = obj;
      res.second = false;
    } else {
      tree_.fix(x);
    }
    res.first = iterator(x);
    return res;
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>>
  insert_many(Args &&...args) noexcept {
    std::vector<std::pair<iterator, bool>> res;
    for (const auto &arg : {args...}) {
      res.push_back(insert(arg));
    }
    return res;
  }
  void erase(iterator pos) noexcept { tree_.delete_node(pos); }
  void swap(map &other) noexcept { tree_.swap(other.tree_); }
  void merge(map &other) noexcept { tree_.merge(other.tree_); }

  // Map Lookup
  bool contains(const key_type &key) const noexcept {
    return iterator(tree_.find(key)) != end();
  }

private:
  RBTree<key_type, value_type, compare_type> tree_;
};
} // namespace s21
#endif // S21_MAP_H_