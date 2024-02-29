#ifndef TREE_SET_HPP
#define TREE_SET_HPP

// DO NOT CHANGE THIS FILE

#include <cstddef>
#include <vector>
#include <functional>
#include <optional>
#include "BinaryTreeNode.hpp"

template <typename T>
class TreeSet
{
private:
    BinaryTreeNode<T> *_root;
    std::function<int(T, T)> _comparator;
    size_t _size;

    // Red-Black Tree functions
    // if not doing Red-Black tree, these functions can be empty

    /// @brief fix any violation of red-black tree properties
    /// @param z the new node inserted
    /// @note textbook 13.3 P.339
    void fix_violation(BinaryTreeNode<T> *z);

    /// @brief left rotation
    /// @param x the node to rotate on
    /// @note textbook 13.2 P.336
    void rotate_left(BinaryTreeNode<T> *x);

    /// @brief Right rotation
    /// @param y the node to rotate on
    /// @note textbook P.336 exercise 13.2-1
    void rotate_right(BinaryTreeNode<T> *y);



public:
    TreeSet();
    TreeSet(const std::vector<T> &items);
    TreeSet(std::function<int(T, T)> comparator);
    TreeSet(const std::vector<T> &items, std::function<int(T, T)> comparator);

    /// @brief Returns the number of elements in the tree.
    /// @return The number of elements in the tree.
    size_t size() const;

    /// @brief adds a value to the set.
    /// If there is an element whose value equals (checked by comparator) `value`,
    /// the existing value will be replaced by `value`.
    /// @param value put this value into the set
    void add(T value);

    /// @brief check if a element is in the set
    /// @param value the element
    /// @return true if value is in the set, otherwise false
    bool contains(T value) const;

    /// @brief check if the set is empty
    /// @return true if the set is empty, otherwise false
    bool is_empty() const;

    /// @brief search for the smallest value in the set
    /// @return the minimum value in the set
    std::optional<T> min() const;

    /// @brief search for the largest value in the set
    /// @return the maximum value in the set
    std::optional<T> max() const;

    /// @brief traverse the set in order and return the values as a vector
    /// @return a sorted vector containing all values in the set
    std::vector<T> to_vector() const;

    /// @brief finds a value and return it
    /// @param value 
    /// @return value if found, otherwise std::nullopt
    std::optional<T> get(T value) const;

    /// @brief set uniom
    /// @param other another set to be unioned
    /// @return the result of the union
    TreeSet operator+(const TreeSet &other);

    /// @brief in-place set union
    /// @param other another set to be unioned
    /// @return a reference to this set
    TreeSet &operator+=(const TreeSet &other);

    /// @brief set intersection
    /// @param other another set
    /// @return the result of the intersection
    TreeSet operator&(const TreeSet &other);

    /// @brief set equal
    /// @param other another set
    /// @return true if the two sets contails same elements, otherwise false
    bool operator==(const TreeSet &other) const;

    /// @brief set not equal
    /// @param other another set
    /// @return true if the two sets contails different elements, otherwise false
    bool operator!=(const TreeSet &other) const;

    /// @brief check if the tree is balanced
    /// @return true if the tree is balanced, otherwise false
    bool is_balanced() const
    {
        if (!_root)
            return true;
        return _root->is_rbtree();
    }

    /// @brief remove every element in the set
    void clear();
    virtual ~TreeSet();
};

#endif
