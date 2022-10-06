#include <gtest/gtest.h>
#include "../BigInt.hpp"
#include <vector>

class TestBigInt_1 : public ::testing::Test{
public:
    std::vector <BigInt> data;
    template <class Head> void SetUp(std::vector <BigInt> &data, Head head){
        BigInt tmp(head);
        data.push_back(tmp);
    }
    template <class Head, class... Args> void SetUp(std::vector <BigInt> &data, Head head, Args... args){
        BigInt tmp(head);
        data.push_back(tmp);
        SetUp(data, args...);
    }
};
// Testing bool operators whith positive numbers
TEST_F(TestBigInt_1, test1){
    SetUp(data, "9918446744073709551615" /* data[0] */, "9918446744073709551615" /* data[1] */, "19918446744073709551730" /* data[2] */);
    EXPECT_TRUE(data[0] == data[1]);
    EXPECT_TRUE(data[0] != data[2]);
    EXPECT_TRUE(data[0] < data[2]);
    EXPECT_TRUE(data[0] >= data[1]);
    EXPECT_FALSE(data[0] > data[1]);
    EXPECT_FALSE(data[2] <= data[0]);
}

// Testing bool operators whith negative numbers
TEST_F(TestBigInt_1, test2){
    SetUp(data, "-9918446744073709551615"/* data[0] */, "9918446744073709551615" /* data[1] */, "-19918446744073709551730" /* data[2] */);
    EXPECT_FALSE(data[0] == data[1]);
    EXPECT_TRUE(data[0] != data[2]);
    EXPECT_FALSE(data[0] < data[2]);
    EXPECT_FALSE(data[0] >= data[1]);
    EXPECT_TRUE(data[1] > data[0]);
    EXPECT_TRUE(data[2] <= data[0]);
}

// Testing unary operators whith positive numbers
TEST_F(TestBigInt_1, test3){
    SetUp(data, "67" /* data[0] */, "66" /* data[1] */, "68" /* data[2] */);
    EXPECT_TRUE(++data[0] == data[2]);
    EXPECT_TRUE(data[0]++ == data[2]); 
    EXPECT_TRUE(--data[0] == data[2]);
    data[0]--;
    data[0]--;
    EXPECT_TRUE(data[0] == data[1]);
}

// Testing unary operators whith negative numbers
TEST_F(TestBigInt_1, test4){
    SetUp(data, "-66" /* data[0] */, "-66" /* data[1] */, "-67" /* data [2] */);
    EXPECT_TRUE(--data[0] == data[2]);
    EXPECT_TRUE(data[0]-- == data[2]); // after that subj = 69
    EXPECT_TRUE(++data[0] == data[2]);
    data[0]++;
    EXPECT_TRUE(data[0] == data[1]);
}

// Testing assigment operators
TEST_F(TestBigInt_1, test5){
    SetUp(data, "9918446744073709551615" /* data[0] */, "9918446744073709551615" /* data[1] */, "19836893488147419103230" /* data[2] */,
        "198368934881474191032300" /* data[3] */, "-178532041393326771929070" /* data[4] */, "56" /* data[5] */, 
        "-9997794318026299228027920" /* data[6] */, "1983689348814741910323" /* data[7] */, "-5040" /* data[8] */, "-1024" /* data[9] */, "944" /* data[10] */);
    data[0] += data[1];
    EXPECT_TRUE(data[0] == data[2]);
    data[0] -= data[3];
    EXPECT_TRUE(data[0] == data[4]);
    data[0] *= data[5];
    EXPECT_TRUE(data[0] == data[6]);
    data[0] /= data[7];
    EXPECT_TRUE(data[0] == data[8]);
    data[0] %= data[9];
    EXPECT_TRUE(data[0] == data[10]);
}

// Testing assigment bool operators
TEST_F(TestBigInt_1, test6){
    SetUp(data, "107" /* data[0] */, "12" /* data[1] */, "48" /* data[2] */, "8" /* data[3] */, "56" /* data[4] */);
    data[0] &= data[1];
    EXPECT_TRUE(data[0] == data[3]);
    data[0] |= data[2];
    EXPECT_TRUE(data[0] == data[4]);
}
