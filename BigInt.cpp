#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>
#include "BigInt.hpp"
#define DIFF 48
#define LEN 1024
#define PLUS 1
#define MINUS 0

int main()
{
	BigInt a("-120");
	std::cout << a << std::endl;
	std::cin >> a;
	std::cout << a << std::endl;
	return 0;
}
