#include <iostream>
using namespace std;

//函数模板
template <typename T>
T maxNum(T a, T b) {
	return (a > b) ? a : b;//为什么加括号？因为三目运算符的优先级较低，如果不加括号，可能会导致语法错误或者逻辑错误。
}

//类模板 类模板允许定义通用的类 通过类型参数化 实现不同类型的对象
//template <typename T>
//class MyClass {
//public:
//	T data;
//};  
//这是格式

template <typename T,typename U>
class Pair {
public:
	T first;
	U second;

	Pair(T a, U b) : first(a), second(b) {};

	void display() {
		cout << "First: " << first << ", Second: " << second << endl;
	}
	//要点 ：1.类模板可以有多个类型参数 2.参数模板可以用于成员变量和成员函数 3.类模板的实例化需要指定具体的参数类型
};

int main()
{
	//cout << maxNum(3, 5) << endl; // 输出: 5
	//cout << maxNum(3.5, 2.1) << endl; // 输出: 3.5
	//cout << maxNum('a', 'b') << endl;	

	Pair<int, string> p1(1, "hello");
	p1.display();
	Pair<double, float > p2(1.11, 2.222);
	p2.display();
	return 0;
}


