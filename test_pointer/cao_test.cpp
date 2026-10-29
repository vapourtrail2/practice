#include <iostream>
using namespace std;

int main() {
	int a = 0;
	//定义一个指针变量  然后取a的地址  且这个指针是整型指针
	int* ptr = &a;
	cout << "ptr的值  也就是它存的内容为: " << ptr;
	//如果你取出它所指向的值 也就是a的值
	cout << "  取出它所指向的值 也就是a的值: " << *ptr;
    
 
	return 0;
}