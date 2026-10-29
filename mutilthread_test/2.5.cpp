#include <iostream>
#include <thread>

void func() {

}

int main() {
	std::thread t1(func);
	
	std::thread::id id = t1.get_id();
	
	std::cout << id;
}