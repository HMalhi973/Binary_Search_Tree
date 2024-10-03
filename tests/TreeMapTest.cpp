#include <gtest/gtest.h>
#include "TreeMap.cpp"
#include <algorithm>
#include <random>

//Empty TreeMap test
TEST(TreeMapTest, InstantiateEmptyTreeMap)
{
    TreeMap<int, std::string> map(std::vector<std::pair<int, std::string>>{});
    
    ASSERT_TRUE(map.is_empty()) << "Empty TreeMap should behave as empty.";
    ASSERT_EQ(map.size(), 0) << "Empty TreeMap should have size 0.";
    ASSERT_EQ(map.to_vector(), (std::vector<std::pair<int, std::string>>{})) << "to_vector should return an empty vector for an empty TreeMap.";
}



TEST(TreeMapTest, InstantiateTreeMapWithInitialElements)
{
    std::vector<std::pair<int, std::string>> initial_elements = {
        {1, "One"}, {2, "Two"}, {3, "Three"}
    };
    TreeMap<int, std::string> map(initial_elements);
    
    ASSERT_EQ(map.size(), initial_elements.size()) << "TreeMap size should match number of initial elements.";
    ASSERT_FALSE(map.is_empty()) << "TreeMap should not be empty after initialization.";
    
    // Verify that all initial key-value pairs are present
    for(size_t i = 0; i < initial_elements.size(); ++i){
        ASSERT_TRUE(map.contains(initial_elements[i].first)) << "TreeMap should contain key: " << initial_elements[i].first;
        ASSERT_EQ(map.get(initial_elements[i].first), initial_elements[i].second) << "Value mismatch for key: " << initial_elements[i].first;
    }
}


//Ensure that get() correctly retrieves the elements that were inserted and shows us the .second part of the pair
TEST(TreeMapTest, InsertAndRetrieve)
{
    TreeMap<int, std::string> map; 

    //Insert key-value pairs
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");

    ASSERT_EQ(map.size(), 3) << "TreeMap size should be 3 after inserting three elements.";

    ASSERT_TRUE(map.contains(2)) << "TreeMap should contain key 2.";
    ASSERT_FALSE(map.contains(4)) << "TreeMap should not contain key 4.";

    //Verify retrieval
    ASSERT_EQ(map.get(1), "one") << "Value for key 1 should be 'one'.";
    ASSERT_EQ(map.get(2), "two") << "Value for key 2 should be 'two'.";
    ASSERT_EQ(map.get(3), "three") << "Value for key 3 should be 'three'.";
    ASSERT_EQ(map.get(4), std::nullopt) << "Value for non-existing key 4 should be std::nullopt.";   
}


//Test get() method with keys that do not exist
TEST(TreeMapTest, GetMethod)
{
    TreeMap<int, std::string> map; //Using default constructor

    //Insert key-value pairs using traditional for loop
    std::vector<std::pair<int, std::string>> elements = {
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    for(size_t i = 0; i < elements.size(); ++i){
        map.insert(elements[i].first, elements[i].second);
    }

    //Retrieve existing keys
    for(size_t i = 0; i < elements.size(); ++i){
        ASSERT_EQ(map.get(elements[i].first), elements[i].second) 
            << "Value mismatch for key: " << elements[i].first;
    }

    //Attempt to retrieve non-existing keys
    std::vector<int> non_existing_keys = {4, 5, 6};
    for(size_t i = 0; i < non_existing_keys.size(); ++i){
        ASSERT_EQ(map.get(non_existing_keys[i]), std::nullopt) 
            << "get() should return std::nullopt for non-existing key: " << non_existing_keys[i];
    }
}

//Check if TreeMap returns the keys in sorted order when placed in a vector
TEST(TreeMapTest, IteratorTraversal)
{
    TreeMap<int, std::string> map; //Using default constructor

    //Insert key-value pairs using a traditional for loop
    std::vector<std::pair<int, std::string>> elements = {
        {5, "five"}, {3, "three"}, {7, "seven"}, {2, "two"}, {4, "four"}, {6, "six"}, {8, "eight"}
    };
    for(size_t i = 0; i < elements.size(); ++i){
        map.insert(elements[i].first, elements[i].second);
    }

    //Expected sorted order
    std::vector<std::pair<int, std::string>> expected = {
        {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}
    };

    //Retrieve elements using to_vector()
    std::vector<std::pair<int, std::string>> actual = map.to_vector();

    //Verify the size
    ASSERT_EQ(actual.size(), expected.size()) << "Iterator traversal should return all elements.";

    //Verify each key-value pair is in the expected sorted order
    for(size_t i = 0; i < expected.size(); ++i){
        ASSERT_EQ(actual[i].first, expected[i].first) << "Key mismatch at index " << i;
        ASSERT_EQ(actual[i].second, expected[i].second) << "Value mismatch at index " << i;
    }
}

//Ensure duplicates are handled in such a way last inserted value is what remains for each duplicate key
TEST(TreeMapTest, InitializeWithDuplicateKeys)
{
    std::vector<std::pair<int, std::string>> initial_elements = {
        {1, "one"}, {2, "two"}, {2, "TWO"}, {3, "three"}, {3, "THREE"}, {3, "THREE-UPDATED"}
    };
    TreeMap<int, std::string> map(initial_elements); // Initialize with duplicates

    //Expected: {1, "one"}, {2, "TWO"}, {3, "THREE-UPDATED"}
    std::vector<std::pair<int, std::string>> expected = {
        {1, "one"}, {2, "TWO"}, {3, "THREE-UPDATED"}
    };
    std::vector<std::pair<int, std::string>> actual = map.to_vector();

    ASSERT_EQ(actual.size(), expected.size()) << "TreeMap should contain unique keys after initialization with duplicates.";

    for(size_t i = 0; i < expected.size(); ++i){
        ASSERT_EQ(actual[i].first, expected[i].first) << "Key mismatch at index " << i;
        ASSERT_EQ(actual[i].second, expected[i].second) << "Value mismatch at index " << i;
    }
}

//Ensure insertion in random order causes no unexpected results
TEST(TreeMapTest, InsertRandomOrder)
{
    TreeMap<int, std::string> map; 

    std::vector<std::pair<int, std::string>> elements;
    for(int i = 1; i <= 1000; ++i){
        elements.emplace_back(i, "Value_" + std::to_string(i));
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);

    for(size_t i = 0; i < elements.size(); ++i){
        map.insert(elements[i].first, elements[i].second);
    }

    ASSERT_EQ(map.size(), elements.size()) << "TreeMap size should be 1000 after inserting 1000 unique elements.";

    //Verify all elements are present
    for(size_t i = 0; i < elements.size(); ++i){
        ASSERT_TRUE(map.contains(elements[i].first)) << "TreeMap should contain key: " << elements[i].first;
        ASSERT_EQ(map.get(elements[i].first), elements[i].second) << "Value mismatch for key: " << elements[i].first;
    }
}

