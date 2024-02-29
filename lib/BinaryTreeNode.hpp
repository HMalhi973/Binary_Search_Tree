#ifndef BINARY_TREE_NODE_HPP
#define BINARY_TREE_NODE_HPP

// DO NOT CHANGE THIS FILE
#include <stdlib.h>     /* abs */

enum Color { Red, Black };

template <typename T>
class BinaryTreeNode
{
private:
    // make constructors and `_next` field only available to `TreeSet` class
    // to avoid instantiating node and mutating `_next` outside `TreeSet` class.

    template <typename U>
    friend class TreeSet;

    BinaryTreeNode<T> *_left;
    BinaryTreeNode<T> *_right;
    BinaryTreeNode<T> *_parent = nullptr;
    Color _color;


    explicit BinaryTreeNode(T value) :
        _left(nullptr), _right(nullptr), value(value), _color(Red) {}

    BinaryTreeNode(T value, Color color) :
        _left(nullptr), _right(nullptr), value(value), _color(color) {}

    BinaryTreeNode(T value, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right) :
        _left(left), _right(right), value(value) {}

    BinaryTreeNode(T value, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right, Color color) :
        _left(left), _right(right), value(value), _color(color) {}

    int black_height() const {
        int left_black_height = _left ? _left->black_height() : 0;
        int right_black_height = _right ? _right->black_height() : 0;
        return (_color == Black ? 1 : 0) + std::max(left_black_height, right_black_height);
    }

public:
    T value;
    BinaryTreeNode<T> *left() { return _left; }
    BinaryTreeNode<T> *right() { return _right; }

    /// @brief check if the tree is balanced
    /// @return true if the tree is balanced, otherwise false
    /// @note see defintion "Red-Black properties" on textbook 13.1 P.331-332
    bool is_rbtree() const {
        // Property 1: Every node is either Red or Black
        if (_color != Red && _color != Black)
        {
            return false;
        }

        // Property 2: The root is Black
        if (_parent == nullptr && _color != Black)
        {
            return false;
        }

        // Property 3: All leaves (nullptr) are Black - this is covered implicitly

        // Property 4: If a node is Red, then both its children are Black
        if (_color == Red)
        {
            if ((_left && _left->_color != Black) || (_right && _right->_color != Black))
            {
                return false;
            }
        }

        // Property 5: Every path from a node to a descendant nullptr contains the same number of Black nodes
        int left_black_height = _left ? _left->black_height() : 0;
        int right_black_height = _right ? _right->black_height() : 0;
        if (left_black_height != right_black_height)
        {
            return false;
        }

        bool left_balanced = _left ? _left->is_rbtree() : true;
        bool right_balanced = _right ? _right->is_rbtree() : true;

        return left_balanced && right_balanced;
    }

};

#endif
