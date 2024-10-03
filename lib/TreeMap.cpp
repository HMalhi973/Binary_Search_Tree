#ifndef TREE_MAP_CPP
#define TREE_MAP_CPP

#include "TreeMap.hpp"
#include "TreeSet.cpp"

/*********** NOTE: FILE WORK IN PROGRESS (UNFINISHED) ***************************/

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap() {
    _tree = TreeSet<std::pair<TKey, TValue>>([](const std::pair<TKey, TValue>& a, const std::pair<TKey, TValue>& b) -> int {
        if (a.first < b.first)
            return -1;
        else if (a.first > b.first)
            return 1;
        else
            return 0;
    });
}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap(const std::vector<std::pair<TKey, TValue>> &items)
    : _tree(items, [](const std::pair<TKey, TValue>& a, const std::pair<TKey, TValue>& b) -> int {
          if (a.first < b.first)
              return -1;
          else if (a.first > b.first)
              return 1;
          else
              return 0;
      })
{
    
}



template <typename TKey, typename TValue>
size_t TreeMap<TKey, TValue>::size() const {
    return _tree.size();
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::insert(TKey key, TValue value) {
    std::pair<TKey, TValue> insert_pair = std::make_pair(key, value);
    _tree.add(insert_pair);
}

template <typename TKey, typename TValue>
std::optional<TValue> TreeMap<TKey, TValue>::get(TKey key) const {
    //make a pair containing "key" as its first value and a dummy value for second to which compare with other values in TreeSet
    std::pair<TKey, TValue> dummyPair = std::make_pair(key, TValue());
    //Leverage TreeSet's method get() to find the matching pair
    std::optional<std::pair<TKey, TValue>> extracted_pair = _tree.get(dummyPair);

    if(extracted_pair == std::nullopt){
       return std::nullopt; 
    }
    else{
        return extracted_pair->second;
    }
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::contains(TKey key) const {
    //make a pair containing "key" as its first value and a dummy value for second to which compare with other values in TreeSet
    std::pair<TKey, TValue> dummyPair = make_pair(key, TValue());
    //Leverage TreeSet's method contains() to find the matching key
    return _tree.contains(dummyPair);
}

template <typename TKey, typename TValue>
std::vector<std::pair<TKey, TValue>> TreeMap<TKey, TValue>::to_vector() const {
    return _tree.to_vector();
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::is_empty() const {
    return _tree.is_empty();
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::clear() {
    _tree.clear();
}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::~TreeMap() {
    clear();
}

#endif
