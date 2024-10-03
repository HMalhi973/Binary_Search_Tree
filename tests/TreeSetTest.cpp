#include "TreeSet.cpp"
#include <gtest/gtest.h>

TEST(TreeSetTest, InstantiateEmptyTree)
{
    TreeSet<int> s{};

    ASSERT_EQ(s.size(), 0);
}

TEST(TreeSetTest, InstantiateTreeWithComparator)
{
    // comparator that returns the opposite of the default comparator
    auto cmp = [](int a, int b) {
        if (a < b)
        {
            return 1;
        }
        else if (a > b)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    };
    TreeSet<int> s(cmp);

    ASSERT_EQ(s.size(), 0);

    s.add(1);
    s.add(2);
    s.add(3);
    s.add(4);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 4, 3, 2, 1 }));
    ASSERT_EQ(s.min(), 4);
}

TEST(TreeSetTest, UnionTwo)
{
    TreeSet<int> s1({ 1, 2, 3, 4, 5 });
    TreeSet<int> s2({ 3, 4, 5, 6, 7 });
    TreeSet<int> s3 = s1 + s2;

    ASSERT_EQ(s3.size(), 7);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({ 1, 2, 3, 4, 5, 6, 7 }));

    // union should not mutate original sets
    ASSERT_EQ(s1.size(), 5);
    ASSERT_EQ(s1.to_vector(), std::vector<int>({ 1, 2, 3, 4, 5 }));
    ASSERT_EQ(s2.size(), 5);
    ASSERT_EQ(s2.to_vector(), std::vector<int>({ 3, 4, 5, 6, 7 }));
}

TEST(TreeSetTest, Clear)
{
    TreeSet<int> s({ 1, 2, 3, 4, 5 });
    s.clear();

    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.to_vector(), std::vector<int>({}));
}

//Verify contains() method correctly identifies which elements are in the set
TEST(TreeSetTest, Contains)
{
    TreeSet<int> s(std::vector<int>{1, 2, 3});
    ASSERT_TRUE(s.contains(2));
    ASSERT_FALSE(s.contains(4));
}

//See if adding duplicates increseases size (it shouldn't) and check if the set has
///unique elements
TEST(TreeSetTest, AddDuplicates)
{
    TreeSet<int> s(std::vector<int>{1, 2, 3});
    s.add(2); //Duplicate
    s.add(4);
    ASSERT_EQ(s.size(), 4); //{1, 2, 3, 4}
    ASSERT_EQ(s.to_vector(), std::vector<int>({1, 2, 3, 4}));
}

//Check if duplication is handled correctly when using += overloaded operator
TEST(TreeSetTest, OperatorPlusEquals)
{
    TreeSet<int> s1(std::vector<int>{1, 2, 3});
    TreeSet<int> s2(std::vector<int>{3, 4, 5});
    s1 += s2;
    ASSERT_EQ(s1.size(), 5);
    ASSERT_EQ(s1.to_vector(), std::vector<int>({1, 2, 3, 4, 5}));
}

//Verify if overloaded & operator behaves as intended (creates set with elements that exist only in both sets)
TEST(TreeSetTest, Intersection)
{
    TreeSet<int> s1(std::vector<int>{1, 2, 3, 4});
    TreeSet<int> s2(std::vector<int>{3, 4, 5, 6});
    TreeSet<int> intersection = s1 & s2;
    ASSERT_EQ(intersection.size(), 2);
    ASSERT_EQ(intersection.to_vector(), std::vector<int>({3, 4}));
}

//verify if overloaded & operator with no common elements creates an empty set
TEST(TreeSetTest, IntersectionNoCommon)
{
    TreeSet<int> s1(std::vector<int>{1, 2, 3});
    TreeSet<int> s2(std::vector<int>{4, 5, 6});
    TreeSet<int> intersection = s1 & s2;
    ASSERT_EQ(intersection.size(), 0);
    ASSERT_EQ(intersection.to_vector(), std::vector<int>{});
}


//Verify if overloaded == operator correctly checks whether both sets have the same elements
TEST(TreeSetTest, Equality)
{
    TreeSet<int> s1(std::vector{1, 2, 3});
    TreeSet<int> s2(std::vector{3, 2, 1});
    TreeSet<int> s3(std::vector{1, 2, 4});
    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 == s3);
}

//Do the same as above but with the overloaded != operator
TEST(TreeSetTest, Inequality)
{
    TreeSet<int> s1(std::vector{1, 2, 3});
    TreeSet<int> s2(std::vector{1, 2, 3});
    TreeSet<int> s3(std::vector{1, 2, 4});
    ASSERT_FALSE(s1 != s2);
    ASSERT_TRUE(s1 != s3);
}

//min() and max() should return largest or smallest vale
TEST(TreeSetTest, MinAndMax)
{
    TreeSet<int> s(std::vector<int>{5, 3, 7, 2, 4, 6, 8});
    ASSERT_EQ(s.min(), 2);
    ASSERT_EQ(s.max(), 8);
}

//min() and max() need to return nullopt whenever set is empty
TEST(TreeSetTest, MinAndMaxEmpty)
{
    TreeSet<int> s;
    ASSERT_EQ(s.min(), std::nullopt);
    ASSERT_EQ(s.max(), std::nullopt);
}

//test overloaded + operator
TEST(TreeSetTest, UnionDisjointSets)
{
    TreeSet<int> s1(std::vector{1, 2, 3});
    TreeSet<int> s2(std::vector{4, 5, 6});
    TreeSet<int> s3 = s1 + s2;
    ASSERT_EQ(s3.size(), 6);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({1, 2, 3, 4, 5, 6}));
}

//try using clear() and check if it correctly emptied the set
TEST(TreeSetTest, AddAfterClear)
{
    TreeSet<int> s(std::vector<int>{1, 2, 3});
    s.clear();
    ASSERT_TRUE(s.is_empty());
    s.add(4);
    s.add(5);
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.to_vector(), std::vector<int>({4, 5}));
}

//Check if elements added randomly are sorted naturally
TEST(TreeSetTest, AddRandomOrder)
{
    TreeSet<int> s;
    s.add(3);
    s.add(1);
    s.add(4);
    s.add(2);
    s.add(5);
    ASSERT_EQ(s.to_vector(), std::vector<int>({1, 2, 3, 4, 5}));
}






