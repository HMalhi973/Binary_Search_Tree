#ifndef TREE_MAP_CPP
#define TREE_MAP_CPP

#include "TreeMap.hpp"
#include "TreeSet.cpp"

/*********** NOTE: FILE WORK IN PROGRESS (UNFINISHED) ***************************/

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap() {
    // mock implementation
}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap(const std::vector<std::pair<TKey, TValue>> &items) {
    // mock implementation
}

template <typename TKey, typename TValue>
size_t TreeMap<TKey, TValue>::size() const {
    return 0;  // mock return value
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::insert(TKey key, TValue value) {
    // mock implementation
}

template <typename TKey, typename TValue>
std::optional<TValue> TreeMap<TKey, TValue>::get(TKey key) const {
    return std::nullopt;  // mock return value
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::contains(TKey key) const {
    return false;  // mock return value
}

template <typename TKey, typename TValue>
std::vector<std::pair<TKey, TValue>> TreeMap<TKey, TValue>::to_vector() const {
    return {};  // mock return value
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::is_empty() const {
    return true;  // mock return value
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::clear() {
    // mock implementation
}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::~TreeMap() {
    // mock implementation
}

#endif
