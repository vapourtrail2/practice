#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
   /* std::string str1 = "Hello world";
	std::string str2 = "llo";
	size_t pos = str1.find(str2); 
	std::string str3 = str1.substr(2, 2);
	std::cout << str3 << std::endl;
	std::cout << pos;*/
   
	//str.append(", World!"); // 使用append方法连接字符串
    //std::cout << str << std::endl; // 输出: Hello, World!

	std::string str = "Hello,World!";
	//try {
	//	char c = str.at(10);
	//}
	//catch (const std::out_of_range& e) {
	//	std::cout << "info is" << e.what() << std::endl;
	//}

	//str.insert(2, "abc"); // 在索引位置2插入字符串"abc"	
	//cout << str << endl; // 输出: "zzabczzzz"


	// 字符串流 stringstream
	//stringstream ss;
	//ss << "Hello, " << "worddd" << "1" << 123;// 将多个数据写入字符串流
	//string dad  =  ss.str();
	//cout << dad << endl; // 输出: "Hello, worddd1123"

	//str.clear(); // 清空字符串内容
	str.erase(5, 7);
	cout << str << endl; // 输出: "" (空字符串)
	
    return 0;
}
