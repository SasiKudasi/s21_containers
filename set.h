#ifndef CPP2_S21_CONTAINERS_1_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_S21_CONTAINERS_S21_SET_H_

#include "RBTree.h"

namespace s21 {

template <typename T, typename Compare = std::less<T>> class set {
public:
  // Typedefs
  using key_type = T;
  using value_type = T;
  using compare_type = Compare;
  using reference = value_type &;
  using const_reference = const reference;
  using iterator =
      typename RBTree<key_type, value_type, compare_type>::iterator;
  using const_iterator =
      typename RBTree<key_type, value_type, compare_type>::const_iterator;
  using size_type = size_t;
  using node_type = typename RBTree<key_type, value_type, compare_type>::Node;

  // Member functions
  set() {}
  explicit set(std::initializer_list<value_type> const &items) {
    for (auto i : items) {
      insert(i);
    }
  }
  set(const set &s) {
    for (auto i : s) {
      insert(i);
    }
  }
  set(set &&s) noexcept : tree_(std::move(s.tree_)) {}
  set &operator=(const set &s) noexcept {
    tree_ = std::copy(s.tree_);
    return *this;
  }
  set &operator=(set &&s) noexcept {
    tree_ = std::move(s.tree_);
    return *this;
  }
  ~set() {}

  // Iterators
  iterator begin() const noexcept { return tree_.begin(); }
  iterator end() const noexcept { return tree_.end(); }

  // Capacity
  bool empty() const noexcept { return tree_.size() == 0; }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Modifiers
  void clear() noexcept { tree_.delete_tree(); }
  std::pair<iterator, bool> insert(const value_type &value) noexcept {
    std::pair<iterator, bool> res;
    node_type *x = tree_.insert(value, value);
    res.second = true;
    if (!x) {
      x = tree_.find(value);
      res.second = false;
    } else {
      tree_.fix(x);
    }
    res.first = iterator(x);
    return res;
  }

  // vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) noexcept {
    std::vector<std::pair<iterator, bool>> res;
    for (const auto &arg : {args...}) {
      res.push_back(insert(arg));
    }
    return res;
  }
  void erase(iterator pos) noexcept { tree_.delete_node(pos); }
  void swap(set &other) noexcept { tree_.swap(other.tree_); }
  void merge(set &other) noexcept { tree_.merge(other.tree_); }

  // Lookup
  iterator find(const key_type &key) const noexcept {
    return iterator(tree_.find(key));
  }
  bool contains(const key_type &key) const noexcept {
    return find(key) != end();
  }

private:
  RBTree<key_type, value_type, compare_type> tree_;
};
} // namespace s21
#endif // CPP2_S21_CONTAINERS_1_S21_CONTAINERS_S21_SET_H_