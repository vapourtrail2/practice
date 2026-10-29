#include <iostream>

int main()
{
    const int a = 0;
    const int b = 2;
    /*a = 10;*/
    
	const int* p = &a;
    //*p = 19;
    p = &b;//可以换目标

	std::cout << *p << std::endl;

    //类型别名
    typedef int shijin;
    shijin i = 0;
    std::cout <<  "i = " << i << std::endl;

	//decltype 关键字  
    int c = 10;
	int& d = c;
    
    decltype(d) e = c;

	std::cout << "e = " << e << std::endl;
    
    return 0;
}
