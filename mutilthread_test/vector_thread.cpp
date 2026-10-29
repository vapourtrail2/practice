#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

std::mutex mutex;
//并发编程 2.3 

void worker(int id, int count, int delay) {
	for (int i = 0; i < count; i++){
		{
		std::lock_guard<std::mutex> lock(mutex);//加锁
		std::cout << "线程" << id << ":" << i << std::endl;//这个线程独占执行这个语句
		}//离开作用域，自动解锁
		std::this_thread::sleep_for(std::chrono::microseconds(delay));
	}
}

int main() {

	//const int ThreadCount = 2;
	//const int LoopCount = 5;
	//const int Delay = 1000000;

	//std::vector<std::thread> vec1;

	//for (int i = 0; i < ThreadCount; i++)
	//{
	//	vec1.emplace_back(worker, i,LoopCount, Delay);
	//}
 //	
	//for (auto &a :vec1)//
	//{
	//	a.join();
	//}
	//
	//std::cout << "zhixingwanbi" << std::endl;

	
	return 0;
}