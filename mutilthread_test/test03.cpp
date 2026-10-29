#include <iostream>
#include <thread>
#include <chrono>

void fun_1() {
	for (int i = 0; i < 10; i++)
	{
		std::cout << "fun_1: " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void fun_2(int& v) {
	v += 100;
}

int main() {
	int value = 2;

	std::thread t1(fun_2,std::ref(value));

	/*for (int i = 0; i < 10; i++)
	{
		std::cout << "fun_2: " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}*/

	t1.join();

	std::cout << "value = " << value << std::endl;
	return 0;
}