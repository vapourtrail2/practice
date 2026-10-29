//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <chrono>
//
//void func() {
//
//	std::this_thread::sleep_for(std::chrono::seconds(1));
//
//	std::cout << "Hello from thread!" << std::endl;
//}
//
//int main() {
//
//	std::thread t(func);
//	t.join();
//	
//
//	return 0;
//}

//#include <iostream>
//#include <thread>
//using namespace std;
//class Task
//{
//public:
//    void operator()(int i)  //()÷ÿ‘ÿ
//    {
//        cout << i << endl;
//    }
//};
//
//int main()
//{
//    for (int i = 0; i < 4; i++)
//    {
//        Task task;
//        thread t(task, i);
//        t.detach();
//    }
//}

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::chrono::milliseconds timeeee(1000); // 1√Î÷”

std::mutex mutex;

int var_1 = 0;
int var_2 = 0;

void mission_1() {
	mutex.lock();
	std::this_thread::sleep_for(timeeee *5);
	mutex.unlock();	
}

void mission_2() {
	while (true)
	{
		if (mutex.try_lock()) {
			var_1++;
			std::cout << "mission_1 execu " << var_1 << std::endl;
			mutex.unlock();
			return;
		}
		else
		{
			var_2++;
			std::cout << "mission_2 execu " << var_2 << std::endl;
			std::this_thread::sleep_for(timeeee);
		}
	}
}

int main() {
	std::thread t1(mission_1);
	std::thread t2(mission_2);
	t1.join();
	t2.join();
	
	return 0;
}