#include <iostream>

//左值和右值 左值就是左边的值 有持久化的对象和内存地址 ，右值就是右边的值 没有持久化的对象和内存地址 只能被使用一次
//语法 int&& a = 10; 

int main()
{
    //char 用来表示一个字符  它是整数类型
    char a = 'a';
    std::cout << "大小: " << sizeof(a) <<std:: endl;
    std::cout << "asc: " << int(a) <<std:: endl;
    return 0;
}
