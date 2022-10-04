#include <gtest/gtest.h>
#include "../BigInt.hpp"

class TestBigInt : public ::testing::Test{
public:
    BigInt subj;
    BigInt supportive_1;
    BigInt supportive_2;
    void SetUp(std::string input1, std::string input2, std::string input3){
        BigInt tmp_subj(input1);
        BigInt tmp_sup_1(input2);
        BigInt tmp_sup_2(input3);
        subj = tmp_subj;
        supportive_1 = tmp_sup_1;
        supportive_2 = tmp_sup_2;
    }
};

// Testing bool operators whith positive numbers
TEST_F(TestBigInt, test1){
    SetUp("9918446744073709551615", "9918446744073709551615", "19918446744073709551730");
    EXPECT_TRUE(subj == supportive_1);
    EXPECT_TRUE(subj != supportive_2);
    EXPECT_TRUE(subj < supportive_2);
    EXPECT_TRUE(subj >= supportive_1);
    EXPECT_FALSE(subj > supportive_1);
    EXPECT_FALSE(supportive_2 <= subj);
}

// Testing bool operators whith negative numbers
TEST_F(TestBigInt, test2){
    SetUp("-9918446744073709551615", "9918446744073709551615", "-19918446744073709551730");
    EXPECT_FALSE(subj == supportive_1);
    EXPECT_TRUE(subj != supportive_2);
    EXPECT_FALSE(subj < supportive_2);
    EXPECT_FALSE(subj >= supportive_1);
    EXPECT_TRUE(supportive_1 > subj);
    EXPECT_TRUE(supportive_2 <= subj);
}

// Testing unary operators whith positive numbers
TEST_F(TestBigInt, test3){
    SetUp("67", "66", "68");
    EXPECT_TRUE(++subj == supportive_2);
    EXPECT_TRUE(subj++ == supportive_2); // after that subj = 69
    EXPECT_TRUE(--subj == supportive_2);
    subj--;
    subj--;
    EXPECT_TRUE(subj == supportive_1);
}

// Testing unary operators whith negative numbers
TEST_F(TestBigInt, test4){
    SetUp("-66", "-66", "-67");
    EXPECT_TRUE(--subj == supportive_2);
    EXPECT_TRUE(subj-- == supportive_2); // after that subj = -68
    EXPECT_TRUE(++subj == supportive_2);
    subj++;
    EXPECT_TRUE(subj == supportive_1);
}

// Testing assigment operators
TEST_F(TestBigInt, test5){
    SetUp("9918446744073709551615", "9918446744073709551615", "19836893488147419103230");
    subj += supportive_1;
    EXPECT_TRUE(subj == supportive_2);
    BigInt tmp_1("198368934881474191032300");
    subj -= tmp_1;
    EXPECT_TRUE(std::string(subj) == "-178532041393326771929070");
    BigInt tmp_2("56");
    subj *= tmp_2;
    EXPECT_TRUE(std::string(subj) == "-9997794318026299228027920");
    BigInt tmp_3("1983689348814741910323");
    subj /= tmp_3;
    EXPECT_TRUE(std::string(subj) == "-5040");
    BigInt tmp_4("-1024");
    subj %= tmp_4;
    EXPECT_TRUE(std::string(subj) == "944");
}

// Testing assigment bool operators
TEST_F(TestBigInt, test6){
    SetUp("107", "12", "48");
    subj &= supportive_1;
    EXPECT_TRUE(std::string(subj) == "8");
    subj |= supportive_2;
    EXPECT_TRUE(std::string(subj) == "56");
}