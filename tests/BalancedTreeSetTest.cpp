#include "TreeSet.cpp"
#include <gtest/gtest.h>

TEST(BalancedTreeSetTest, InstantiateEmptyTree)
{
    TreeSet<int> s{};

    ASSERT_TRUE(s.is_balanced());
}
