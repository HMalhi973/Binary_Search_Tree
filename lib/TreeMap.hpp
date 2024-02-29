#ifndef TREE_MAP_HPP
#define TREE_MAP_HPP

// DO NOT CHANGE THIS FILE

#include <cstddef>
#include <optional>
#include <vector>
#include "BinaryTreeNode.hpp"
#include "TreeSet.hpp"

template <typename TKey, typename TValue>
class TreeMap
{
private:
    TreeSet<std::pair<TKey, TValue>> _tree;

public:
    TreeMap();
    TreeMap(const std::vector<std::pair<TKey, TValue>> &items);

    /// @brief Returns the number of elements in the map.
    /// @return The number of elements in the map.
    size_t size() const;

    /// @brief insert a key-value pair into the map
    /// @param key unique key for searching in map
    /// @param value the mapped value of the key
    void insert(TKey key, TValue value);

    /// @brief get the value of a key
    /// @param key unique key for searching in map
    /// @return the mapped value
    std::optional<TValue> get(TKey key) const;

    /// @brief check if a key is in the map
    /// @param key unique key to search for
    /// @return true if key is in the map, otherwise false
    bool contains(TKey key) const;

    /// @brief traverse the map in order and return the values as a vector
    /// @return a sorted vector containing all kv-pair in the map
    std::vector<std::pair<TKey, TValue>> to_vector() const;

    /// @brief check if the map is empty
    /// @return true if the map is empty, otherwise false
    bool is_empty() const;

    /// @brief remove every element in the set
    void clear();
    ~TreeMap();
};

#endif
