//
// Created by bogdan on 25.12.2021.
//

#include "unordered_map.h"
#include <gtest/gtest.h>

TEST(list, simple_tests) {
    list<int> l1;
    std::vector<int> ans;
    for (size_t i = 0; i < 10; ++i) {
        ans.push_back(i);
        l1.add(i);
    }
    auto it = l1.begin();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    list<int> l2(l1);
    it = l2.begin();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    list<int> l3 = l1;
    it = l3.begin();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    list<int> l4(std::move(l1));
    it = l4.begin();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    list<int> l5;
    l5 = std::move(l2);
    it = l5.begin();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    size_t j = 0;
    for (const auto &pos: l5) {
        EXPECT_EQ(pos, j);
        ++j;
    }
    l5.pop();
    l5.pop();
    it = l5.begin();
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(*it, i);
        ++it;
    }
    list<int> l6;
    auto iter1 = l6.add(1);
    l6.add(2);
    auto iter2 = l6.erase(iter1);
    EXPECT_EQ(*iter2, 2);
    EXPECT_EQ(l6.len(), 1);
    EXPECT_EQ(*l6.begin(), 2);
}

TEST(unordered_map, simple_tests) {
    unordered_map<int, int, std::hash<int>, std::equal_to<>> um1;
    auto it = um1.insert(11, 21);
    EXPECT_EQ(it->first, 11);
    EXPECT_EQ(it->second, 21);
    auto um2(um1);
    EXPECT_EQ(um2.begin()->first, 11);
    EXPECT_EQ(um2.begin()->second, 21);
    unordered_map<int, int, std::hash<int>, std::equal_to<>> um3;
    um3 = um1;
    EXPECT_EQ(um3.begin()->first, 11);
    EXPECT_EQ(um3.begin()->second, 21);
    auto um4(std::move(um1));
    EXPECT_EQ(um4.begin()->first, 11);
    EXPECT_EQ(um4.begin()->second, 21);
    unordered_map<int, int, std::hash<int>, std::equal_to<>> um5;
    um5 = std::move(um2);
    EXPECT_EQ(um5.begin()->first, 11);
    EXPECT_EQ(um5.begin()->second, 21);
    um5.insert(12, 22);
    for (const auto &el: um5) {
        EXPECT_EQ(el.first, el.second - 10);
    }
    EXPECT_EQ(um5.at(11), 21);
    EXPECT_THROW(um5.at(3), std::out_of_range);
    unordered_map<int, int, std::hash<int>, std::equal_to<>> um6;
    for (size_t i = 0; i < 10; ++i) {
        um6.insert(10 + i, 20 + i);
    }
    EXPECT_EQ(um6.size(), 10);
    um3.erase(um3.begin());
    EXPECT_TRUE(um3.empty());
    EXPECT_EQ(um4[11], 21);
    um3[13] = 23;
    EXPECT_EQ(um3.at(13), 23);
    EXPECT_EQ(um3.find(13)->second, 23);
}