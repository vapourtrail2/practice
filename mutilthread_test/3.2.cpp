#include <mutex>
#include <thread>
#include <iostream>
#include <list>
#include <algorithm>
#include <math.h>
//mutex 互斥 它们不能同时进入同一把锁保护的临界区
class SafeList
{
private:
	std::list<int> datalist;
	std::mutex m;

public:
	void add_data(int v) {
		std::lock_guard<std::mutex> g(m);
		datalist.push_back(v);
	}

	bool delete_data() {
		std::lock_guard<std::mutex> g(m);
		if (datalist.empty()) {
			return false;
		}
		datalist.pop_back();
		return true;
	}

	bool contained_data(int v) {
		std::lock_guard<std::mutex> g(m);
		return std::find(
			datalist.begin(),
			datalist.end(),
			v
		) != datalist.end();
	}

	std::size_t size() {
		std::lock_guard<std::mutex> g(m);
		return datalist.size();
	}

	void print_data() {
		//只能保证一个线程修改数据 但不保证某个线程的先后修改顺序

		std::list<int> templist;
		{//控制锁的持有时间 减少不必要的时间
			std::lock_guard<std::mutex> g(m);
			templist = datalist;
		}

		for (auto v : templist)
		{
			std::cout << v << " ";
		}
	}
};

int main() {
	SafeList safelist;
	//satelist.add_data(10);
	//satelist.add_data(20);
	//satelist.add_data(30);

	//bool v = satelist.contained_data(50);
	//std::cout << v << std::endl;

	//std::thread t1(&SafeList::add_data, &safelist, 10);//1 成员函数 2 哪个对象上执行 3 参数
	//std::thread t2(&SafeList::add_data, &safelist, 20);

	//t1.join();
	//t2.join();

	//std::cout << safelist.contained_data(10) << std::endl;
	//std::cout << safelist.contained_data(20) << std::endl;

	std::thread t1([&safelist]() {
		for (int i = 0; i < 1000; i++)
		{
			safelist.add_data(i);
		}
		});

	std::thread t2([&safelist]() {
		for (int i = 1000; i < 2000; i++)
		{
			safelist.add_data(i);
		}
		});

	t1.join();
	t2.join();

	safelist.print_data();
	
	return 0;
}