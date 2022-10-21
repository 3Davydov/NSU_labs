#include <gtest/gtest.h>
#include "../BigInt.hpp"
#include <vector>
class MultipleParams{
public:
    std::vector <BigInt> data;
    template <class Head> void Set_up(std::vector <BigInt> &data, Head head){
        BigInt tmp(head);
        data.push_back(tmp);
    }
    template <class Head, class... Args> void Set_up(std::vector <BigInt> &data, Head head, Args... args){
        BigInt tmp(head);
        data.push_back(tmp);
        Set_up(data, args...);
    }
};

class TestBigInt1 : public ::testing::TestWithParam<std::tuple<std::string, int, BigInt>>, public MultipleParams{};
class TestBigInt2 : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>>, public MultipleParams{};

class TestBigInt3 : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>>, public MultipleParams{};

class TestBigInt4 : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string, std::string, std::string, std::string, 
                                                    std::string, std::string, std::string, std::string>>, public MultipleParams{};

class TestBigInt5 : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string, std::string, std::string, std::string, 
                                                    std::string, std::string>>, public MultipleParams{};
                                                    
class TestBigInt6 : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string, std::string, std::string>>,
                    public MultipleParams{};

class TestBigInt7 : public ::testing::TestWithParam<std::tuple<std::string, std::string>>, public MultipleParams{};

TEST_P(TestBigInt1, testing_constructors){
    std::string init_whith_str = std::get<0>(GetParam());
    int init_whith_int = std::get<1>(GetParam());
    BigInt init_whith_BigInt = std::get<2>(GetParam());
    Set_up(data, init_whith_str, init_whith_int, init_whith_BigInt); 
    EXPECT_TRUE((int) data[1] == init_whith_int);
    EXPECT_TRUE((std::string(data[0])) == init_whith_str);
    EXPECT_TRUE(data[2] == init_whith_BigInt);
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestBigInt1, ::testing::Values (
                                                                            std::make_tuple("12345", 234234, 123),
                                                                            std::make_tuple("0", 0, 0),
                                                                            std::make_tuple("-63463298758923573245783426", -579235, -9879682)
                                                                            ));

TEST_P(TestBigInt2, testing_bool_operators){
    std::string param1 = std::get<0>(GetParam());
    std::string param2 = std::get<1>(GetParam());
    std::string param3 = std::get<2>(GetParam());
    Set_up(data, param1, param2, param3); 
    EXPECT_TRUE(data[0] == data[1]);
    EXPECT_TRUE(data[0] != data[2]);
    EXPECT_TRUE(data[0] < data[2]);
    EXPECT_TRUE(data[0] >= data[1]);
    EXPECT_FALSE(data[0] > data[1]);
    EXPECT_FALSE(data[2] <= data[0]);
}

INSTANTIATE_TEST_CASE_P(testing_bool_operators, TestBigInt2, ::testing::Values (
                                            std::make_tuple("9918446744073709551615", "9918446744073709551615", "19918446744073709551730"),
                                            std::make_tuple("-19918446744073709551730", "-19918446744073709551730", "-9918446744073709551615")
                                            ));

TEST_P(TestBigInt3, testing_unary_operators){
    std::string param1 = std::get<0>(GetParam());
    std::string param2 = std::get<1>(GetParam());
    std::string param3 = std::get<2>(GetParam());
    Set_up(data, param1, param2, param3); 
    EXPECT_TRUE(++data[0] == data[2]);
    EXPECT_TRUE(data[0]++ == data[2]); 
    EXPECT_TRUE(--data[0] == data[2]);
    data[0]--;
    data[0]--;
    EXPECT_TRUE(data[0] == data[1]);
}

INSTANTIATE_TEST_CASE_P(testing_unary_operators, TestBigInt3, ::testing::Values (
                                                                                std::make_tuple("67", "66", "68"),
                                                                                std::make_tuple("-67", "-68", "-66")
                                                                                ));

TEST_P(TestBigInt4, testing_assigment_operators){
    std::string param1 = std::get<0>(GetParam());
    std::string param2 = std::get<1>(GetParam());
    std::string param3 = std::get<2>(GetParam());
    std::string param4 = std::get<3>(GetParam());
    std::string param5 = std::get<4>(GetParam());
    std::string param6 = std::get<5>(GetParam());
    std::string param7 = std::get<6>(GetParam());
    std::string param8 = std::get<7>(GetParam());
    std::string param9 = std::get<8>(GetParam());
    std::string param10 = std::get<9>(GetParam());
    Set_up(data, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10); 
    data[0] += data[0];
    EXPECT_TRUE(data[0] == data[1]);
    data[1] -= data[2];
    EXPECT_TRUE(data[1] == data[3]);
    data[3] *= data[4];
    EXPECT_TRUE(data[3] == data[5]);
    data[5] /= data[6];
    EXPECT_TRUE(data[5] == data[7]);
    data[7] %= data[8];
    EXPECT_TRUE(data[7] == data[9]);
}

INSTANTIATE_TEST_CASE_P(testing_assigment_operators, TestBigInt4, ::testing::Values (
                                                            std::make_tuple("9918446744073709551615", "19836893488147419103230", 
                                                            "198368934881474191032300", "-178532041393326771929070", "56",
                                                             "-9997794318026299228027920", "1983689348814741910323", "-5040", "-1024", "944")
                                                             ));

TEST_P(TestBigInt5, testing_assigment_bool__operators){
    std::string param1 = std::get<0>(GetParam());
    std::string param2 = std::get<1>(GetParam());
    std::string param3 = std::get<2>(GetParam());
    std::string param4 = std::get<3>(GetParam());
    std::string param5 = std::get<4>(GetParam());
    std::string param6 = std::get<5>(GetParam());
    std::string param7 = std::get<6>(GetParam());
    std::string param8 = std::get<7>(GetParam());
    Set_up(data, param1, param2, param3, param4, param5, param6, param7, param8);  
    data[0] &= data[1];
    EXPECT_TRUE(data[0] == data[3]);
    data[0] |= data[2];
    EXPECT_TRUE(data[0] == data[4]);
    data[5] ^= data[6];
    EXPECT_TRUE(data[5] == data[7]);
}

INSTANTIATE_TEST_CASE_P(testing_assigment_bool__operators, TestBigInt5, ::testing::Values (
                                                                                            std::make_tuple("107", "12", "48", "8", "56",
                                                                                                             "54", "28", "-42")
                                                                                            ));

TEST_P(TestBigInt6, testing_assigment_bool__operators){
    std::string param1 = std::get<0>(GetParam());
    std::string param2 = std::get<1>(GetParam());
    std::string param3 = std::get<2>(GetParam());
    std::string param4 = std::get<3>(GetParam());
    std::string param5 = std::get<4>(GetParam());
    Set_up(data, param1, param2, param3, param4, param5);  
    EXPECT_TRUE((data[0] + data[0]) == data[1]);
    EXPECT_TRUE((data[2] - data[3]) == data[4]);
}

INSTANTIATE_TEST_CASE_P(testing_assigment_bool__operators, TestBigInt6, ::testing::Values (
                                                            std::make_tuple("9918446744073709551615", "19836893488147419103230", 
                                                            "-9918446744073709551615", "-9918446744073709551616", "1"
                                                            )));

TEST_P(TestBigInt7, testing_assigment_bool__operators){
    std::string param1 = std::get<0>(GetParam());
    std::string param2 = std::get<1>(GetParam());
    Set_up(data, param1, param2);  
    EXPECT_TRUE((int)data[0 == data[1]]);
    EXPECT_TRUE(std::string(data[1]) == "-1073741829");
}

INSTANTIATE_TEST_CASE_P(testing_assigment_bool__operators, TestBigInt7, ::testing::Values (
                                                            std::make_tuple("-5368709125", "-1073741829"
                                                            )));
