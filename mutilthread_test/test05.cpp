#include <iostream>
#include <thread>
#include <chrono>

void func() {
		std::this_thread::sleep_for(
			std::chrono::seconds(2)
		);

		std::cout << "worker1 finished\n";
	}

void func2() {
	std::this_thread::sleep_for(
			std::chrono::seconds(2)
	);

	std::cout << "worker2 finished\n";
}

//wait for threadµÄÓÃ·¨

void worker() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "worker finished\n";
}


void wait_for_thread(std::thread t) {
	t.join();
}

int main() {
	/*std::thread t1(func);
	std::thread t2(func2);
	t1.join();
	
	t1 = std::move(t2);
	t1.join();*/

	std::thread t1(worker);

	wait_for_thread(std::move(t1));

	return 0;
}