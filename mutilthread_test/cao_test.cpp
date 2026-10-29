#include <iostream>
#include <vector>

//int main() {
//	std::vector<int> vec;
//	for (int i = 3; i <= 10; i++)
//	{
//		vec.push_back(i);
//	}
//	
//	std::vector<int>::iterator it;
//	it = vec.end() -1;//end() 指向最后一个元素后面的位置
//	for (auto a : vec )
//	{
//		std::cout << *it << " ";
//		if(it != vec.begin())
//		{ 
//			it = it - 1; 
//		}
//		else
//		{
//			return 0;
//		}
//		
//	}
//
//	return 0;
//}
//
//int main() {
//	int a[10];
//	for (int i = 1; i <= 10; i++)
//	{
//		a[i-1] = i;
//		//std::cout << a[i-1] << " ";
//	}
//
//	int* p = &a[9];
//	//std::cout << *p;
//	for (int i = 1; i <= 10; i++)
//	{
//		printf("%d ", *p);
//		if (*p != 1) {
//			p--;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//}


//break 结束当前for循环  2.打印前把指针移到首处
int main() {
	std::vector<int> a;

	for (int i = 1; i <= 10; i++)
	{
		a.push_back(i);
	}

	std::vector<int>::iterator it = a.begin();

	for (;it!=a.end();it++)
	{
		std::cout << *it << " ";
		
	}

	std::cout  << " " << std::endl;

	it = a.begin();
	std::vector<int>::iterator it_2 = a.end() - 1;
	
	for (;it != a.end();it++)
	{
		if (it < it_2) {
			int temp;
			temp = *it;
			*it = *it_2;
			*it_2 = temp;
			it_2--;
			
			//for (auto &v :a)
			//{
			//	std::cout << v << " ";
			//}
			//std::cout << " " << std::endl;
		}
		else
		{
			break;
		}
	}

	std::cout << "-----------------";
	std::cout << " " << std::endl;
	it = a.begin();
	for (;it != a.end();it++)
	{
		std::cout << *it << " ";
	}

	return 0;

}