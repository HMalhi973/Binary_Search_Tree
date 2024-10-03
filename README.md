# Binary Tree, TreeSet, and TreeMap APIs

This project implements a Red-Black Tree in C++ through the `TreeSet` and `TreeMap` classes with the support of a templated class `BinaryTreeNode`. The main objective of this work is to showcase how simpler data structures such as binary trees may be used to build more complex stuctures such as sets and maps. This project was completed for the course ECS 36C at UC Davis.

## BinaryTreeNode Implementation Details

The `BinaryTreeNode` class is a templated class that represents a node within a tree (Red-Black Tree in our case). Each node holds a value of generic type `T`, holds left and right pointers for its children, as well as a parent node. Each node has an enum data type `Color` which describes whether the node is red or black. This last variable is essential for mainitaining Red-Black Tree properties. The following list describes ome additional properties of the class:

- Constructors:
  - Default Constructor: Initializes a node with a value and sets default pointers and color.
  - Parametrized Constructors: Initialize node with specific children and color.
- Methods:
  - `black_height` calculates the black height of the subtree rooted at the node (Essential for maintaing Red-Black Tree properties).
  - `is_rbtree` checks whether the subtree satisfies Red-Black Tree Properties.
- Friend Class:
  `TreeSet` class is granted access to the private members of `BinaryTreeNode`, because it will need to manipulate node pointers frequently. 

## TreeSet Implementation Details

The `TreeSet` class is a templated implementation that balances itself using Red-Black Tree properties. It provides efficient deletion, insertion, as well as lookup operations since each operation that could potentially disrupt the balance works towards fixing the violation of Red-Black Tree rules. The class is comprised of three key attributes. A pointer to the root of the tree, a variable that keeps track of the number of elements in the structure, as well as a custom comparator function which defines the order of the elements. The neccessity of this custom function is critical. If the tree is comprised of integers, it is common sense that the integers witll be ordered by their size. However, since this is a templated class and many different data types can be inserted into the tree, it is up to the user to define in which way to order for example a tree of strings. The following list goes over the functionality of this class:

- Constructors:
  - Default Constructor: Initializes an empty tree with a default comparator.
  - Vector Constructor: Builds a tree from the elements in the vector and default constructor.
  - Comparator Constructor: Initializes an empty tree with a custom comparator.
  - Vector and Comparator Constructor: Initializes tree with elements in vector and defines a custom comparator.
- Red-Black Tree Methods:
  - `fix_violation` ensures the tree maintains Red-Black properties. It is called in other methods such as insertion.
  - `rotate_left` performs a left rotation around a given node. It is called within `fix_violation`.
  - `rotate_right` performs a right rotation around a given node. It is called within `fix_violation`.
- Methods:
  - `size` returns number of elements in the tree
  - `add` inserts a new element into the tree. It handles the case where there is a duplicate by replacing it with the new element.
  - `contains` returns a boolean value according to whether an element exists in the tree.
  - `is_empty` returns a boolean value based on if the tree is empty.
  - `min` returns the smallest element in the tree.
  - `max` returns the largest element in the tree.
  - `to_vector` returns a vector with all the sorted elements of the tree.
  - `get` retrieves the element specified.
  - `clear` removes all emelements in the tree and it is called within the destructor to deallocate memory and prevent memory leaks.
- Overloaded Operator Methods:
  - `operator+` returns the union of two sets.
  - `operator+=` does an in-place union with another set (changes the current set).
  - `operator&` returns the intersection of two sets (common elements only).
  - `operator==` checks equality between two sets.
  - `operator !=` checks inequality between two sets.

## TreeMap Implementation Details

The `TreeMap` class is a templated implementation of a map data structure that leverages a `TreeSet` object to manage key-value pairs gracefully. It ensures keys are unique and due to the tree structure that supports it, fast lookup, insertion,  and deletion is provided. This class is particularly useful when you want to store non-numerical data types/objects in a certain order, the key represents the order, while the value would be the object/data type. The functionality is explained in the following list:

- Constructors:
  - Default Constructor: Initializes an empty map in which the comparator is set to compare keys.
  - Vector Constructor: Buiilds a map from a vector of key-value pairs. The comparator is also set to compare keys.
- Methods:
  - `size` returns the number of key-value pairs in the map.
  - `insert` places a new key-value pair into the map. If the key already exists, its vlue is updated.
  - `get` returns the value associated with a specific key.
  - `contains` returns a boolean value according to whether a key exists in the map.
  - `to_vector` returns all key-value pairs in the map as a sorted vector.
  - `clear` removes all pairs from the map. It is called in the destructor to free memory.

## Building and Running the Project 

- Run the following commands to build.

  ```bash
  cd ./Binary_Search_Tree
  mkdir build
  cd build
  cmake ..
  ```
- Run the following to run test cases and verify functionality.

  ```bash
  cd build
  make
  ./run_tests
  ```
