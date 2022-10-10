#include "BigInt.hpp"

#ifndef OVERLOAD_OPERATORS
#define OVERLOAD_OPERATORS

BigInt operator+(const BigInt& num1, const BigInt& num2) { 
	BigInt copy(num1);
	std::cout << num1;
	copy += num2;
	return copy;
}

BigInt operator-(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy -= num2);
}

BigInt operator*(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy *= num2);
}

BigInt operator/(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy /= num2);
}

BigInt operator^(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy ^= num2);
}

BigInt operator%(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy %= num2);
}

BigInt operator&(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy &= num2);
}

BigInt operator|(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy |= num2);
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	BigInt copy(i);
	if (i.sign == MINUS) o << "-";
	//o << i.number_str;
	int len = size_bit(copy.number_bit);
	copy.number_str = bit_to_string(copy.number_bit, len);
	o << copy.number_str;
	return o;
}

std::istream& operator>>(std::istream& o, BigInt& i){
	std::string input;
	o >> input;
	try{
		for (unsigned int i = 0; i < input.length(); i++){
			if ((int)input[i] < 48 || (int)input[i] > 57) {
				if (input[i] != '-') throw(std::invalid_argument("Invalid syntax"));
			}
		}
	}
	catch(std::invalid_argument arg) {std::cout << "Invalid syntax"; return o;}
	BigInt copy(input);
	i = copy;
	return o;
}

#endif