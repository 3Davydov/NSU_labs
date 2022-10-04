#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>

#define DIFF 48
#define LEN 1024
#define PLUS 1
#define MINUS 0

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

	void show() {
		std::cout << number_bit << std::endl;
		std::cout << number_str << std::endl;
		std::cout << (int)sign << std::endl;
	}
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

BigInt::BigInt() {
	sign = PLUS;
}

BigInt::BigInt (int input) {
	input < 0 ? sign = MINUS : sign = PLUS;
	if (input < 0) input *= -1;
	std::bitset<LEN> init(input);  // можно ли как то вызвать конструктор bitset?
	number_bit = init;
}

BigInt::BigInt(std::string input) {  // бросать исключение std::invalid_argument при ошибке
	try{
		for (unsigned int i = 0; i < input.length(); i++){
			if ((int)input[i] < 48 || (int)input[i] > 57) {
				if (input[i] != '-') throw(std::invalid_argument("Invalid syntax"));
			}
		}
	}
	catch(std::invalid_argument arg) {std::cout << "Invalid syntax"; return;}
	input[0] == '-' ? sign = MINUS : sign = PLUS;
	if (input[0] == '-') input.erase(input.find('-'), 1);
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
		if (b_comp(number_bit, for_comp) == 3) {
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
		if (b_comp(number_bit, for_comp) == 3) {
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
		if (b_comp(number_bit, for_comp) == 3) {
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
		if (b_comp(number_bit, for_comp) == 3) {
			number_bit.reset();
		}
		else number_bit = b_red(number_bit, plus_1);
	}
	return ret;
}

BigInt& BigInt::operator+=(const BigInt& num) {
	if (sign == num.sign) number_bit = b_sum(number_bit, num.number_bit);
	if (sign != num.sign) {
		//int len;
		switch (b_comp(number_bit, num.number_bit))
		{
		case 3:
			sign = PLUS;
			number_bit.reset();
			break;
		case 1:
			number_bit = b_red(number_bit, num.number_bit);
			break;
		case 2:
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
		//int len;
		switch (b_comp(number_bit, num.number_bit))
		{
		case 3:
			sign = PLUS;
			number_bit.reset();
			break;
		case 1:
			number_bit = b_red(number_bit, num.number_bit);
			break;
		case 2:
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
	if (res != 3) return false;
	return true;
}

bool BigInt::operator!=(const BigInt& num) const {
	if (sign != num.sign) return true;
	int res = b_comp(number_bit, num.number_bit);
	if (res != 3) return true;
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
	if (res == 1) return false;
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
	if (res == 1) return true;
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
	if (res == 1 && res != 3) return false;
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
	if (res == 1 || res == 3) return true;
	else return false;
}

BigInt::operator int() const {
	return (int)number_bit.to_ullong();
}

BigInt::operator std::string() const {
	BigInt copy(*this);
	if (sign == MINUS) copy.number_str.push_back('-');
	int len = size_bit(copy.number_bit);
	copy.number_str += bit_to_string(copy.number_bit, len);
	return copy.number_str;
}

size_t BigInt::size() const {
	BigInt copy(*this);
	int len = size_bit(copy.number_bit);
	copy.number_str = bit_to_string(copy.number_bit, len);
	return copy.number_str.size();
}


int size_bit(std::bitset<LEN> ans) {
	int k = 0;
	for (int i = 0; i < LEN; i++) {
		if (ans[LEN - i - 1] != 0) {
			k = LEN - i - 1;
			break;
		}
	}
	return k + 1;
}

int BigInt::b_comp(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2){
	int len1 = 0, len2 = 0, len = 0;
	len1 = size_bit(bit_arr1);
	len2 = size_bit(bit_arr2);
	len1 > len2 ? len = len1 : len = len2;
	for (int i = 0; i < len; i++) {
		if (bit_arr1[len - i -1] > bit_arr2[len - i - 1]) return 1;
		if (bit_arr1[len - i - 1] < bit_arr2[len - i - 1]) return 2;
	}
	return 3;
}

int BigInt::b_comp(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2) const{
	for (int i = 0; i < LEN; i++) {
		if (bit_arr1[LEN - i - 1] > bit_arr2[LEN - i - 1]) return 1;
		if (bit_arr1[LEN - i - 1] < bit_arr2[LEN - i - 1]) return 2;
	}
	return 3;
}

std::bitset<LEN> BigInt::b_sum(std::bitset<LEN> ans, std::bitset<LEN> num) {
	int overage = 0, current = 0;
	int len1 = 0, len2 = 0, len = 0;
	len1 = size_bit(ans);
	len2 = size_bit(num);
	len1 > len2 ? len = len1 : len = len2;
	for (int i = 0; i < len; i++) {
		current = ans[i] + num[i] + overage;
		ans[i] = current % 2;
		overage = current / 2;
	}
	if (overage > 0) ans[len] = overage % 2;
	return ans;
}

std::bitset<LEN> BigInt::b_pow(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2) {
	std::bitset<LEN> ans;
	std::bitset<LEN> local_ans;
	int len1 = 0, len2 = 0;
	len1 = size_bit(bit_arr1);
	len2 = size_bit(bit_arr2);
	int overage = 0, current = 0;
	for (int i = 0; i < len2; i++) {
		overage = 0;
		for (int j = 0; j < len1; j++) {
			current = bit_arr1[j] * bit_arr2[i] + overage;
			local_ans[j] = current % 2;
			overage = current / 2;
		}
		if (overage > 0) local_ans[8] = overage;
		local_ans <<= i;
		ans = b_sum(ans, local_ans);
		local_ans.reset();
	}
	return ans;
}

std::bitset<LEN> BigInt::b_red(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2) {
	std::bitset<LEN> ans;
	int current = 0;
	int len1 = 0, len2 = 0, len = 0;
	len1 = size_bit(bit_arr1);
	len2 = size_bit(bit_arr2);
	len1 > len2 ? len = len1 : len = len2;
	for (int i = 0; i < len; i++) {
		current = bit_arr1[i] - bit_arr2[i];
		if (current < 0) {
			current += 2;
			for (int j = i + 1; j < len; j++) {
				if (bit_arr1[j] == 1) { 
					bit_arr1[j] = 0; 
					for (int k = j - 1; k >= i + 1; k--) bit_arr1[k] = 1;
					break;
				}
			}
		}
		ans[i] = current;
	}
	return ans;
}

std::bitset<LEN> BigInt::string_to_bit(std::string input) {
	std::bitset<LEN> bits(0);
	std::bitset<LEN> grade(10);
	for (unsigned int i = 0; i < input.length(); i++) {
		bits = b_pow(bits, grade);
		bits = b_sum(bits, (int)input[i] - DIFF);
	}
	return bits;
}

void pow_2(std::string& grade) {
	int overage = 0, current = 0;
	std::string ans;
	int len = grade.length();
	for (int i = 0; i < len; i++) {
		current = ((int)grade[len - i - 1] - DIFF) * 2 + overage;
		ans.push_back(current % 10 + DIFF);
		overage = current / 10;
	}
	if (overage > 0) {
		ans.push_back(overage + DIFF);
	}
	std::reverse(ans.begin(), ans.end());
	grade = ans;
}

std::string operator_sum(std::string& s1, std::string& s2) {
	std::string ans;
	int len = 0, longest = 0, len1 = 0, len2 = 0;
	len1 = s1.length();
	len2 = s2.length();
	if (len1 > len2) {
		len = len2;
		longest = 1;
	}
	else {
		len = len1;
		longest = 2;
	}
	int overage = 0, current = 0;
	for (int i = 0; i < len; i++) {
		current = ((int)s1[len1 - i - 1] - DIFF) + ((int)s2[len2 - i - 1] - DIFF) + overage;
		ans.push_back(current % 10 + DIFF);
		overage = current / 10;
	}
	if (len1 > len2) {
		for (int i = len; i < len1; i++) {
			current = ((int)s1[len1 - i - 1] - DIFF) + overage;
			ans.push_back(current % 10 + DIFF);
			overage = current / 10;
		}
		if (overage > 0) ans.push_back(overage + DIFF);
	}
	if (len2 > len1) {
		for (int i = len; i < len2; i++) {
			current = ((int)s2[len2 - i - 1] - DIFF) + overage;
			ans.push_back(current % 10 + DIFF);
			overage = current / 10;
		}
		if (overage > 0) ans.push_back(overage + DIFF);
	}
	if (len1 == len2 && overage > 0) ans.push_back(overage + DIFF);
	std::reverse(ans.begin(), ans.end());
	return ans;
}

std::string bit_to_string(std::bitset<LEN> bit_arr, int len) {
	std::string ans;
	std::string grade;
	grade.push_back('1');
	for (int i = 0; i < len; i++) {
		if (bit_arr[i] == 1) ans = operator_sum(ans, grade);
		pow_2(grade);
	}
	return ans;
}

std::bitset<LEN> BigInt::bit_div(std::bitset<LEN> bit_arr1, std::bitset<LEN> bit_arr2, std::string ret) {
	std::bitset<LEN> grade = 1;
	std::bitset<LEN> ans;
	std::bitset<LEN> local_ans;
	std::bitset<LEN> plus_1(1);
	int check = 0;
	while (true) {
		while (b_comp(b_pow(grade | ans, bit_arr2), bit_arr1) == 2) {
			if ((ans & grade) != 0) {
				break;
			}
			grade <<= 1;
		}
		grade >>= 1;
		ans |= grade;
		grade = 1;
		check = b_comp(b_sum(b_pow(ans, bit_arr2), bit_arr2), bit_arr1);
		if (check == 1 || check == 3) break;
	}
	if (check == 3) return b_sum(ans, plus_1);
	else {
		if (ret == "remainder") ans = b_red(bit_arr1, b_pow(ans, bit_arr2));
		return ans;	
	}

}

BigInt operator+(const BigInt& num1, const BigInt& num2) {
	BigInt copy(num1);
	return (copy += num2);
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
	o << i.number_str;
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
