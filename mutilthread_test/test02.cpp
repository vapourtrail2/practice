#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <deque>

std::mutex mutex;
std::deque<int> q;

//往队列放数据的线程
void fun_1() {
	int i = 10;
	while (i>0)
	{
		std::unique_lock<std::mutex> locker(mutex);
		q.push_front(i);
		locker.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		i--;
	}
}

//从队列取线程
void fun_2() {
	int j = 0;
	while ( j != 1)
	{
		std::unique_lock <std::mutex> locker(mutex);

		if (!q.empty()) {
			j = q.back();
			q.pop_back();
			std::cout << "j = " << j << std::endl;
		}
		else
		{	
			locker.unlock();
		}
	}
}

int main() {
	std::thread t1(fun_1);
	std::thread t2(fun_2);

	t1.join();
	t2.join();

	return 0;
}