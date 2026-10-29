//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <vector>
//#include <atomic>
//using namespace std;
//
//int n = 0;//全局 方法1 加锁
//mutex a;
//
////atomic<int> n(0);//方法2 原子变量
//void increase() {
//	for (int i = 0; i < 100000; i++)
//	{
//		a.lock();//只能一次让一个线程执行
//		n++;
//		a.unlock();
//	}
//}
//
//int main()
//{
//	vector<thread> threadsvec;
//	for (int i = 0; i < 10; i++)
//	{
//		threadsvec.push_back(thread(increase));//这句执行以后，所有线程已经启动 ，已经开始并发跑
//	}
//	//十个线程被操作系统分配到CPU的不同核心上执行，十个同时执行increase函数
//	//等待所有线程执行完毕
//	for (auto& t : threadsvec) {
//		t.join();//main 也就是主线程 等待每个子线程执行完毕  一起等 此时所有线程还在并发执行，
//	}
//	cout << n << endl;
//	return 0;
//}
//
