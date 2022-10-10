#include "BigInt.hpp"
#ifndef SUPPORTIVE_FUNCTIONS
#define SUPPORTIVE FUNCTIONS

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
#endif