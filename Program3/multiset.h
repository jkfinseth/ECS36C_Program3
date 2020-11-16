#ifndef MULTISET_H_
#define MULTISET_H_

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <utility>

template <typename K>
class Multiset {
 public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size();
  // Returns true if multiset is empty --O(1)
  bool Empty();

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K &key);
  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K &key);

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K& key);
  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K& key);

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K& Floor(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K& Ceil(const K &key);

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Max();
  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Min();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  struct Node {
    K key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    unsigned int quantity;
  };
  std::unique_ptr<Node> root;
  unsigned int item_counter = 0;

  // Private constants
  // ...To be completed (if any)...

  // Private methods

  // Recursive function to find min
  Node* BstMin(Node *n) {
    if (n->left)
      return BstMin(n->left.get());
    else
      return n;
  }

  // Recursive function to find max
  Node* BstMax(Node *n) {
    if (n->right)
      return BstMax(n->right.get());
    else
      return n;
  }

  // Recursive inserting function
  void BstInsert(std::unique_ptr<Node> &n, const K &key) {
    // Set up new node if it doesn't exist
    if (!n) {
      n = std::unique_ptr<Node>(new Node{key});
      n->quantity = 1;
    } else if (key < n->key) {
      BstInsert(n->left, key);
    } else if (key > n->key) {
      BstInsert(n->right, key);
    // Otherwise add 1 to quantity if exists
    } else {
      n->quantity++;
    }
  }

  // Recursive remove function
  void BstRemove(std::unique_ptr<Node> &n, const K &key) {
    if (!n) return;

    if (key < n-> key) {
      BstRemove(n->left, key);
    } else if (key > n-> key) {
      BstRemove(n->right, key);
    } else {
      // Remove node only if 1 exists
      if (n->quantity == 1) {
        if (n->left && n-> right) {
          n-> key = BstMin(n->right.get())->key;
          BstRemove(n->right, n->key);
        } else {
          n = std::move((n->left) ? n->left : n->right);
        }
      // Otherwise remove 1 from quantity
      } else {
        n->quantity--;
      }
    }
  }

  // Overloaded for prime factor program
  friend std::ostream& operator<< (std::ostream& os, const Node& input) {
    if (input.left != nullptr)
      os << *input.left.get();

    os << input.key << " (x" << input.quantity
    << "), ";

    if (input.right != nullptr)
     os << *input.right.get();

    return os;
  }

  friend std::ostream& operator<< (std::ostream& os, const Multiset<K>& input) {
    Node *n = input.root.get();
    os << *n << std::endl;

    return os;
  }
};

//
// Your implementation of the class should be located below
//
template <typename K>
size_t Multiset<K>::Size() {
  return item_counter;
}

template <typename K>
bool Multiset<K>::Empty() {
  if (item_counter == 0)
    return true;
  else
    return false;
}

template <typename K>
void Multiset<K>::Insert(const K &key) {
  BstInsert(root, key);

  item_counter++;
}

template <typename K>
void Multiset<K>::Remove(const K &key) {
  if (!Contains(key))
    throw std::invalid_argument("Invalid key");

  BstRemove(root, key);

  item_counter--;
}

template <typename K>
bool Multiset<K>::Contains(const K& key) {
  Node *n = root.get();

  while (n) {
    if (key == n->key)
      return true;

    if (key < n->key)
      n = n->left.get();
    else
      n = n->right.get();
  }

  return false;
}

template <typename K>
size_t Multiset<K>::Count(const K& key) {
  if (!Contains(key))
    throw std::invalid_argument("Invalid key");

  Node *n = root.get();

  // Search for the node
  while (n) {
    if (key == n->key)
      break;
    else if (key < n->key)
      n = n->left.get();
    else
      n = n->right.get();
  }
  return n->quantity;
}

template <typename K>
const K& Multiset<K>::Floor(const K &key) {
  if (Empty())
    throw std::invalid_argument("Empty multiset");

  if (Min() > key)
    throw std::invalid_argument("Invalid key");

  Node *n = root.get();

  while (n) {
    if (key == n->key)
      break;

    if (key > n->key) {
      Node *temp = n->right.get();
      if (temp) {
        // Case: both nodes are too small
        if (key > n->right.get()->key)
          n = n->right.get();
        // Case: Node is smaller than key but next value is too large
        else
          break;
      // Case: Min aquired
      } else {
        break;
      }
    } else {
      n = n->left.get();
    }
  }
  return n->key;
}

template <typename K>
const K& Multiset<K>::Ceil(const K &key) {
  if (Empty())
    throw std::invalid_argument("Empty multiset");

  if (Max() < key)
    throw std::invalid_argument("Invalid key");

  Node *n = root.get();

  while (n) {
    if (key == n->key)
      break;

    if (key < n->key) {
      Node *temp = n->left.get();
      if (temp) {
        // Case: Both nodes are too large
        if (key < n->left.get()->key)
          n = n->left.get();
        // Case: Node is larger than key but next value is too small
        else
          break;
      // Case: Max aquired
      } else {
        break;
      }
    } else {
      n = n->right.get();
    }
  }
  return n->key;
}

template <typename K>
const K& Multiset<K>::Max() {
  if (Empty())
    throw std::invalid_argument("Empty multiset");

  return BstMax(root.get())->key;
}

template <typename K>
const K& Multiset<K>::Min() {
  if (Empty())
    throw std::invalid_argument("Empty multiset");

  return BstMin(root.get())->key;
}

#endif  // MULTISET_H_
