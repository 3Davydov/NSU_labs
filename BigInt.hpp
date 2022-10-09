#ifndef LIBS
#define LIBS

#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>

#endif

#ifndef DIFF
#define DIFF 48
#endif

#ifndef LEN
#define LEN 1024
#endif

#ifndef PLUS
#define PLUS 1
#endif

#ifndef MINUS
#define MINUS 0
#endif

#pragma once
class BigInt {
public:
	BigInt();
	BigInt(int input);
	BigInt(std::string input);
	BigInt(const BigInt& input);
	BigInt(BigInt&& input);
	//~BigInt();

	BigInt& operator=(const BigInt&);
	BigInt& operator=(BigInt&&);

	BigInt operator~() const;

	BigInt& operator++();
	const BigInt operator++(int);
	BigInt& operator--();
	const BigInt operator--(int);

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;
	BigInt operator-() const;

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator std::string() const;

	size_t size() const;

private:
	std::string number_str;
	std::bitset<LEN> number_bit;
	char sign;
	friend std::ostream& operator<<(std::ostream& o, const BigInt& i);
	friend std::istream& operator>>(std::istream& o, BigInt& i);
	std::bitset<LEN> string_to_bit(std::string input);
	std::bitset<LEN> b_sum(std::bitset<LEN> ans, std::bitset<LEN> num);
	std::bitset<LEN> b_red(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2);
	int b_comp(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2);
	std::bitset<LEN> b_pow(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2);
	std::bitset<LEN> bit_div(std::bitset<LEN> bit_arr1, const std::bitset<LEN> bit_arr2, std::string ret);
	int b_comp(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2) const;
};
int size_bit(std::bitset<LEN> ans);
std::string bit_to_string(std::bitset<LEN> bit_arr, int len);

BigInt operator+(const BigInt& num1, const BigInt& num2);

BigInt operator-(const BigInt& num1, const BigInt& num2);

BigInt operator*(const BigInt& num1, const BigInt& num2);

BigInt operator/(const BigInt& num1, const BigInt& num2);

BigInt operator^(const BigInt& num1, const BigInt& num2);

BigInt operator%(const BigInt& num1, const BigInt& num2);

BigInt operator&(const BigInt& num1, const BigInt& num2);

BigInt operator|(const BigInt& num1, const BigInt& num2);

std::ostream& operator<<(std::ostream& o, const BigInt& i);

std::istream& operator>>(std::istream& o, BigInt& i);

