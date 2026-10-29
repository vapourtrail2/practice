#include <iostream>
#include <thread>
#include <mutex>

/*
	给共享数据加一把锁，如果要访问这个数据先加锁 使用完了再解锁，如果有线程正在使用这个变量 ，那么就会被锁住，别的线程不让使用，必须等待，除非解锁了，别的线程才可以使用
*/

/*
	dosomething();可能抛异常 ，导致m.unlock()没法释放	所以用std::lock_guard<std::mutex> guard(m); 利用RAII 构造加锁 析构解锁
	RAII 资源的生命周期绑定在对象的生命周期上
*/
std::mutex m;

void func(int &a) {
	std::lock_guard<std::mutex> grand(m);
	a++;//这里可能抛异常
}//grand对象被销毁，析构函数调用m.unlock()
//

int main() {
	int x = 0;
	std::thread t1(func, std::ref(x));
	std::thread t2(func, std::ref(x));
	t1.join();
	t2.join();

	std::cout << x;
	
	return 0;
}