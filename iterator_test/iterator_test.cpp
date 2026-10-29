#include <iostream>
#include <vector>


int main()
{
	//-> 箭头运算符 把解引用和成员访问结合在一起 it->func() 和 (*it).func()是一样的

	std::vector<int> vec = { 1, 3 ,4 ,5 ,5};
	std::cout << vec.capacity() << std::endl;

	return 0;
}
