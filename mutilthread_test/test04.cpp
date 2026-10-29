#include <iostream>
#include <thread>
#include <chrono>

class worker {
public:
	void func(int value, int delay) {
		for (int i = 0; i < value; i++)
		{
			std::cout << "t1" << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}
};

int main() {
	worker w;

	std::thread t1(&worker::func,&w,5,200);

	for (int i = 0; i < 5; ++i)
	{
		std::cout
			<< "main: "
			<< i
			<< std::endl;

		std::this_thread::sleep_for(
			std::chrono::milliseconds(500)
		);
	}

	t1.join();

	return 0;
}