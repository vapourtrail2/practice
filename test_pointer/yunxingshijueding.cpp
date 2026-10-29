#include <iostream>

int main() {
	int a = 10;
	int b = 20;
	int n;

	std::cin >> n;

	int* p;
	if (n == 1) {
		p = &a;
	}
	else
	{
		p = &b;
	}

	std::cout << *p << std::endl;
}