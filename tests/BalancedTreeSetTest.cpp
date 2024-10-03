#include "TreeSet.cpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <random>

TEST(BalancedTreeSetTest, InstantiateEmptyTree)
{
    TreeSet<int> s{};

    ASSERT_TRUE(s.is_balanced());
}

TEST(BalancedTreeSetTest, InsertSortedOrder)
{
    TreeSet<int> s(std::vector<int>{}, [](const int& a, const int& b) -> int {
        return (a < b) ? -1 : (a > b) ? 1 : 0;
    });

    for(int i = 1; i <= 100; ++i){
        s.add(i);
        ASSERT_TRUE(s.is_balanced()) << "Tree became unbalanced after inserting " << i;
    }

    ASSERT_EQ(s.size(), 100);
}


TEST(BalancedTreeSetTest, InstantiateTreeWithInitialElements)
{
    std::vector<int> initial_elements = {1, 2, 3};
    TreeSet<int> s(initial_elements); //Using vector constructor with initial elements

    ASSERT_EQ(s.size(), initial_elements.size()) << "Tree size should match number of initial elements.";
    ASSERT_TRUE(s.is_balanced()) << "Tree should be balanced after initialization.";
    
    //Verify that all initial elements are present using a traditional for loop
    for(size_t i = 0; i < initial_elements.size(); ++i){
        ASSERT_TRUE(s.contains(initial_elements[i])) << "Tree should contain element: " << initial_elements[i];
    }

}



//Test if TreeSet can handle a large amount of shuffled elements and check if it is balanced after appending them all
TEST(BalancedTreeSetTest, LargeDataSetStressTest)
{
    std::vector<int> elements;
    for(int i = 0; i < 10000; ++i){
        elements.push_back(i);
    }
    TreeSet<int> s(elements); //Initialize with 10,000 elements

    ASSERT_EQ(s.size(), 10000) << "Tree should contain 10,000 elements.";
    ASSERT_TRUE(s.is_balanced()) << "Large tree should remain balanced.";

    //Shuffle and verify containment
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);

    for(size_t i = 0; i < elements.size(); ++i){
        ASSERT_TRUE(s.contains(elements[i])) << "Tree should contain element: " << elements[i];
    }
}
