#include <iostream>
#include <vector>

void func(int &x) {
	x = 20;
}

int main() {
	std::vector<int> vec(1);
	std::cout << vec[0];
}