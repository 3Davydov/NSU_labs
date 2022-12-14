
#include "BigInt.hpp"

#if !defined(NINE_ASCII) && !defined(NULL_ASCII) && !defined(MINUS_ASCII)
#define NULL_ASCII 48
#define MINUS_ASCII 45
#define NINE_ASCII 57
#endif

#if !defined(FIRST_IS_BIGGER) && !defined(SECOND_IS_BIGGER) && !defined(EQUAL)
#define FIRST_IS_BIGGER 1
#define SECOND_IS_BIGGER 2
#define EQUAL 3
#endif

#if !defined(MAX_DEGREE_OF_TWO)
#define MAX_DEGREE_OF_TWO 31
#endif

#ifndef CLASS_MEMBERS
#define CLASS_MEMBERS

BigInt::BigInt() {
	number_str = "0";
	number_bit = 0;
	sign = PLUS;
}

BigInt::BigInt (int input) {
	input < 0 ? sign = MINUS : sign = PLUS;
	if (input < 0) input *= -1;
	std::bitset<LEN> init(input); 
	number_bit = init;
}

bool is_digit(char param){
	if ((int)param < NULL_ASCII || (int) param > NINE_ASCII) return false;
	return true;
}

BigInt::BigInt(std::string input) {  
	try{
		for (unsigned int i = 0; i < input.length(); i++){
			if (! is_digit(input[i])) {
				if (input[i] != MINUS_ASCII) throw(std::invalid_argument("Invalid syntax"));
			}
		}
	}
	catch(std::invalid_argument arg) {std::cout << "Invalid syntax"; return;}
	input[0] == MINUS_ASCII ? sign = MINUS : sign = PLUS;
	if (input[0] == MINUS_ASCII) input.erase(input.find(MINUS_ASCII), 1);
	number_bit = string_to_bit(input);
}

BigInt::BigInt(const BigInt& input) {
	this->number_bit = input.number_bit;
	this->sign = input.sign;
}

BigInt::BigInt(BigInt&& input){
	number_bit = input.number_bit;
	sign = input.sign;
}

BigInt& BigInt::operator=(const BigInt& num){
	number_str = num.number_str;
	number_bit = num.number_bit;
	sign = num.sign;
	return *this;
}

BigInt& BigInt::operator=(BigInt&& num){
	number_str = num.number_str;
	number_bit = num.number_bit;
	sign = num.sign;
	return *this;
}

BigInt BigInt::operator~() const{
	BigInt tmp(*this);
	~tmp.number_bit;
	return tmp;
}

BigInt& BigInt::operator++() {
	std::bitset<LEN> plus_1(1);
	if (sign == PLUS) number_bit = b_sum(number_bit, plus_1);
	if (sign == MINUS) {
		std::bitset <LEN> for_comp(1);
		if (b_comp(number_bit, for_comp) == EQUAL) {
			sign = PLUS;
			number_bit.reset();
		}
		else number_bit = b_red(number_bit, plus_1);
	}
	return *this;
}

const BigInt BigInt::operator++(int) {
	BigInt ret(*this);
	std::bitset <LEN> plus_1(1);
	if (sign == PLUS) number_bit = b_sum(number_bit, plus_1);
	if (sign == MINUS) {
		std::bitset <LEN> for_comp(1);
		if (b_comp(number_bit, for_comp) == EQUAL) {
			sign = PLUS;
			number_bit.reset();
		}
		else number_bit = b_red(number_bit, plus_1);
	}
	return ret;
}

BigInt& BigInt::operator--() {
	std::bitset<LEN> plus_1(1);
	if (sign == MINUS) number_bit = b_sum(number_bit, plus_1);
	if (sign == PLUS) {
		std::bitset <LEN> for_comp(1);
		if (b_comp(number_bit, for_comp) == EQUAL) {
			number_bit.reset();
		}
		else number_bit = b_red(number_bit, plus_1);
	}
	return *this;
}

const BigInt BigInt::operator--(int) {
	BigInt ret(*this);
	std::bitset<LEN> plus_1(1);
	if (sign == MINUS) number_bit = b_sum(number_bit, plus_1);
	if (sign == PLUS) {
		std::bitset <LEN> for_comp(1);
		if (b_comp(number_bit, for_comp) == EQUAL) {
			number_bit.reset();
		}
		else number_bit = b_red(number_bit, plus_1);
	}
	return ret;
}

BigInt& BigInt::operator+=(const BigInt& num) {
	if (sign == num.sign) number_bit = b_sum(number_bit, num.number_bit);
	if (sign != num.sign) {
		switch (b_comp(number_bit, num.number_bit))
		{
		case EQUAL:
			sign = PLUS;
			number_bit.reset();
			break;
		case FIRST_IS_BIGGER:
			number_bit = b_red(number_bit, num.number_bit);
			break;
		case SECOND_IS_BIGGER:
			number_bit = b_red(num.number_bit, number_bit);
			sign = num.sign;
			break;
		default:
			break;
		}
	}
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
	if (sign != num.sign) sign = MINUS;
	else sign = PLUS;
	number_bit = b_pow(number_bit, num.number_bit);
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
	if (sign != num.sign) number_bit = b_sum(number_bit, num.number_bit);
	if (sign == num.sign) {
		switch (b_comp(number_bit, num.number_bit))
		{
		case EQUAL:
			sign = PLUS;
			number_bit.reset();
			break;
		case FIRST_IS_BIGGER:
			number_bit = b_red(number_bit, num.number_bit);
			break;
		case SECOND_IS_BIGGER:
			if (num.sign == PLUS) sign = MINUS;
			else sign = PLUS;
			number_bit = b_red(num.number_bit, number_bit);
			break;
		default:
			break;
		}
	}
	return *this;
}

BigInt& BigInt::operator/=(const BigInt& num) {
	number_bit = bit_div(number_bit, num.number_bit, "main");
	if (sign != num.sign) sign = MINUS;
	else sign = PLUS;
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& num) {
	number_bit ^= num.number_bit;
	sign ^= num.sign;
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& num) {
	number_bit = bit_div(number_bit, num.number_bit, "remainder");
	if (sign != num.sign) sign = MINUS;
	else sign = PLUS;
	return *this;
}

BigInt& BigInt::operator&=(const BigInt& num) {
	number_bit &= num.number_bit;
	sign &= num.sign;
	return *this;
}

BigInt& BigInt::operator|=(const BigInt& num) {
	number_bit |= num.number_bit;
	sign |= num.sign;
	return *this;
}

BigInt BigInt::operator+() const { 
	BigInt ret(*this);
	ret.sign = PLUS;
	return ret;
}

BigInt BigInt::operator-() const {
	BigInt ret(*this);
	ret.sign = MINUS;
	return ret;
}

bool BigInt::operator==(const BigInt& num)  const{
	if (sign != num.sign) return false;
	int res = b_comp(number_bit, num.number_bit);
	if (res != EQUAL) return false;
	return true;
}

bool BigInt::operator!=(const BigInt& num) const {
	if (sign != num.sign) return true;
	int res = b_comp(number_bit, num.number_bit);
	if (res != EQUAL) return true;
	return false;
}

bool BigInt::operator<(const BigInt& num) const {
	if (sign != num.sign) {
		bool res = 0;
		sign < num.sign ? res = true : res = false;
		return res;
	}
	int res = 0;
	if (sign == PLUS) res = b_comp(number_bit, num.number_bit);
	else res = b_comp(num.number_bit, number_bit);
	if (res == FIRST_IS_BIGGER) return false;
	else return true;
}

bool BigInt::operator>(const BigInt& num) const{
	if (sign != num.sign) {
		bool res = 0;
		sign < num.sign ? res = false : res = true;
		return res;
	}
	int res = 0;
	if (sign == PLUS) res = b_comp(number_bit, num.number_bit);
	else res = b_comp(num.number_bit, number_bit);
	if (res == FIRST_IS_BIGGER) return true;
	else return false;
}

bool BigInt::operator<=(const BigInt& num) const {
	if (sign != num.sign) {
		bool res = 0;
		sign < num.sign ? res = true : res = false;
		return res;
	}
	int res = 0;
	if (sign == PLUS) res = b_comp(number_bit, num.number_bit);
	else res = b_comp(num.number_bit, number_bit);
	if (res == FIRST_IS_BIGGER && res != EQUAL) return false;
	else return true;
}

bool BigInt::operator>=(const BigInt& num) const {
	if (sign != num.sign) {
		bool res = 0;
		sign < num.sign ? res = false : res = true;
		return res;
	}
	int res = 0;
	if (sign == PLUS) res = b_comp(number_bit, num.number_bit);
	else res = b_comp(num.number_bit, number_bit);
	if (res == FIRST_IS_BIGGER || res == EQUAL) return true;
	else return false;
}

BigInt::operator int() const {
	int len = size_bit(number_bit);
	BigInt copy(*this);
	BigInt int_max(INT_MAX), int_min(INT_MIN);
	for (int i = len; i > MAX_DEGREE_OF_TWO; i--){
		copy.number_bit[i] = 0;
	}
	if (sign == PLUS){
		int index = 0;
		while (copy >= int_max) {copy.number_bit[index] = 0; index++;}
	}
	else{
		int index = 0;
		while (copy <= int_min) {copy.number_bit[index] = 0; index++;}
	}
	return (int)(copy.number_bit.to_ulong() * pow(-1, sign + 1));
}

BigInt::operator std::string() const {
	BigInt copy(*this);
	if (sign == MINUS) copy.number_str.push_back(MINUS_ASCII);
	int len = size_bit(copy.number_bit);
	copy.number_str += bit_to_string(copy.number_bit, len);
	return copy.number_str;
}

size_t BigInt::size() const {
	BigInt copy(*this);
	int len = size_bit(copy.number_bit);
	copy.number_str = bit_to_string(copy.number_bit, len);
	size_t ans = copy.number_str.size();
	sign == MINUS ? ans++ : ans;
	return ans;
}

#endif
