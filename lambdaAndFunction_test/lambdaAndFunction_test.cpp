#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

//int (*func)(int, int);//这句话的意思是定义了一个函数指针func，它指向一个接受两个int参数并返回int类型的函数。也就是说，func可以用来存储任何符合这个签名的函数的地址。	
//
//int add(int a, int b) {
//    return a + b;
//}

//仿函数
//class Add {
//	public:
//		int operator()(int a, int b) {
//			return a + b;
//		}
//};

//class Func {
//public:
//	Func() {
//		count = 0;
//	}
//
//	void operator()(std::string str) {
//		std::cout << str << std:: endl;
//		count = count + 1;
//	}
//
//	int getCount() {
//		return count;
//	}
//
//private:
//	int count;
//};
//
////二元谓词
//class Funcc {
//public:
//	bool operator() (int a, int b) {
//		return a > b;
//	}
//};

//void voo() {
//	vector<int> vt = { 1, 2, 3, 4, 5 };
//
//	sort(vt.begin(), vt.end(), Funcc());
//
//	for (auto it = vt.begin(); it != vt.end(); it++) {
//		cout << *it << " ";	
//	}
//	
//}

// lambda

void voo(std::function<void()> func) {
	func();
	func();
}


int main()
{
	/*func = &add;
    
	std::cout<<func(3, 4);*/
	/*Add add;*/
	//类对象被调用时，会调用类的operator()方法
	/*std::cout<< add(3, 4);*/

	/* func;
	func("Hello, World!");
	func("This is a functor.");
	std::cout<<func.getCount();*/

	/*voo();*/

	/*auto vooo = []() {
		std::cout << "Hello, Lambda!" << std::endl;
		};

	voo(vooo);*/

	int a = 10;
	auto show = [=]() {
		std::cout << "a: " << a << std::endl;
		};

	show();

	return 0;
}

