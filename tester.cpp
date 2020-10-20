#include "../List/List.h"
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::vector;

// --------------------------- elements_tests --------------------------- //

// Checks push methods
TEST(elements_tests, push) {
    List l;
    l.push_front(0);
    l.push_back(1);
    l.push_back(2);
    l.push_front(0);
    l.push_back(3);

    ASSERT_EQ(l, List({0, 0, 1, 2, 3}));
}

// Checks pop methods
TEST(elements_tests, pop) {
    List l;
    l.push_front(0);
    l.push_back(1);
    l.push_back(2);
    l.push_front(0);
    l.push_back(3);
    l.pop_back();
    l.pop_front();
    l.pop_front();

    ASSERT_EQ(l, List({1, 2}));
}

// Checks mixed push and insert methods
TEST(elements_tests, insert_1) {
    List l;
    l.push_front(0);
    l.push_front(0);
    l.push_front(0);
    l.insert(1, 0);
    l.push_front(0);
    l.insert(1, l.get_size() - 1);

    ASSERT_EQ(l,List({0, 1, 0, 0, 1, 0}));
}

// Check iterative consistent inserting
TEST(elements_tests, insert_2) {
    List l;
    for (size_t index = 0u; index < 10u; index++)
        l.insert(index, index);

    ASSERT_EQ(l,List({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));

    l.insert(100, 0);
    l.insert(101, 0);
    l.insert(1002, 10);

    ASSERT_EQ(l, List({101, 100, 0, 1, 2, 3, 4, 5, 6, 7, 1002, 8, 9}));
}

// Checks begin, middle and end inserting
TEST(elements_tests, insert_3) {
    List l;
    l.insert(0, 0);
    l.insert(1, 1);
    l.insert(2, 2);
    ASSERT_EQ(l, List({0, 1, 2}));
}

// Checks begin, middle and end remove
TEST(elements_tests, remove_1) {
    List l;
    l.insert(0, 0);
    l.insert(1, 1);
    l.insert(2, 2);
    l.insert(3, 3);
    l.remove(3);
    l.remove(1);
    l.remove(0);
    ASSERT_EQ(l, List({2}));
}

// Check iterative consistent removing
TEST(elements_tests, remove_2) {
    List l;
    for (size_t index = 0u; index < 10u; index++)
        l.insert(index, index);
    l.insert(100, 0);
    l.insert(101, 0);
    l.insert(1002, 10);

    for (size_t index = 10u; index > 0u; index--)
        l.remove(index);

    ASSERT_EQ(l, List({101, 8, 9}));

    for(size_t index = 2u; index > 0u; index--)
        l.remove(index);
    l.remove(0);

    ASSERT_EQ(l.isEmpty(), true);
}

// Checks clear method
TEST(elements_tests, clear) {
    List l;
    l.push_front(0);
    l.push_front(0);
    l.push_front(0);
    l.insert(1, 0);
    l.push_front(0);
    l.insert(1, l.get_size() - 1);
    l.clear();
    ASSERT_EQ(l, List());
}


// --------------------------- additional_tests --------------------------- //

// Checks at()
TEST(additional_tests, at) {
    List l;
    l.insert(0, 0);
    l.insert(1, 1);
    l.insert(2, 2);
    ASSERT_EQ(l.at(0), 0);
    ASSERT_EQ(l.at(1), 1);
    ASSERT_EQ(l.at(2), 2);
}

// Checks is_empty()
TEST(additional_tests, is_empty) {
    List l;
    l.insert(0, 0);
    l.insert(1, 1);
    l.insert(2, 2);
    l.pop_back();
    l.pop_back();
    l.pop_front();
    ASSERT_EQ(l.isEmpty(), true);
    l.push_front(1);
    ASSERT_EQ(l.isEmpty(), false);
}

// Standart checks of find_last()
TEST(additional_tests, find_last_1) {
    // I use pointers to avoid the not-deep copy error
    // when I create a local copy of variable that stores raw pointers
    // the copy after it reaches an end of a function will be destroyed
    // and our raw pointers of original object will be destroyed too.

    List *l1 = new List({1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1});
    List *l2 = new List({1, 2});
    ASSERT_EQ(l1->find_last(l2), 6);

    List *l3 = new List({1, 1});
    ASSERT_EQ(l1->find_last(l3), 9);
}

// Hard check on falling back in find_last()
TEST(additional_tests, find_last_2) {
    List *l1 = new List({1, 1, 1, 1, 1, 1, 1, 1, 2});
    List *l2 = new List({1, 1, 1, 1, 2});
    ASSERT_EQ(l1->find_last(l2), 4);
}

// --------------------------- exceptions_tests --------------------------- //

// situations for all out_of_range exceptions
TEST(exceptions_tests, out_of_range) {
    List l1;
    ASSERT_THROW(l1.insert(10, 10), std::out_of_range);
    l1.push_back(0);
    ASSERT_THROW(l1.at(10), std::out_of_range);
    ASSERT_THROW(l1.remove(10), std::out_of_range);
    ASSERT_THROW(l1.set(10, 10), std::out_of_range);
    ASSERT_THROW(l1.find_last(new List({1, 2, 3, 4, 5})), std::out_of_range);
}

// situations for all logical_error exceptions
TEST(exceptions_tests, logical_error) {
    List l1;
    ASSERT_THROW(l1.set(10, 10), std::logic_error);
    ASSERT_THROW(l1.at(10), std::logic_error);
    ASSERT_THROW(l1.remove(10), std::logic_error);

}