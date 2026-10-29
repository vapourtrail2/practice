#include <iostream>
#include <vector>
#include <string> 

void func() {
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

int main()
{
	
	//std::vector<int> vec2(std::move(vec));
	///*for (auto num : vec2)
	//{
	//	std::cout << num << ",";
	//}*/
	//vec2.push_back(6);
	//vec2.push_back(6);
	//vec2.push_back(6);
	//for (auto num : vec2)
	//{
	//	std::cout << num << " " ;
	//}
	//std::cout << std::endl;

	//vec2.pop_back(); 
	//for (auto num : vec2)
	//{
	//	std::cout << num << " ";
	//}
	//std::cout << std::endl;

	//vec2.insert(vec2.begin() + 1, 10);

	//for (auto num : vec2)
	//{
	//	std::cout << num << " ";
	//}

	//std::cout << std::endl;

	//vec2.erase(vec2.begin());

	//for (auto num : vec2)
	//{
	//	std::cout << num << " ";
	//}
	//return 0;

	std::vector<std::string> vec = { "Hello", "World", "C++" };
	

	try {
		std::cout << vec.at(1) << std::endl; 
		std::cout << vec.at(5) << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std:: endl;
	}


	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}

	std::cout << std::endl;

	for (auto it = vec.begin(); it != vec.end(); ++it) {
		std::cout << * it << " ";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	//修改
	std::vector<int> vec1 = { 1, 2, 3, 4, 5 };
	vec1[0] = 10;
	vec1.at(2) = 30;

	for (auto num : vec1)
	{
		std::cout << num << " ";
	}
	

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	for (auto it = vec1.begin(); it != vec1.end(); ++it) {
		if (* it == 5) {
			*it = 100;
		}
	}

	for (auto num : vec1)
	{
		std::cout << num << " ";
	}

	
	func();

	std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));
	
	/*for (auto it = matrix.begin(); it != matrix.end(); it++)
	{
		std::cout << *it <<
	}*/

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = i*4 + j+1;
		}
	}
	
	for (std::vector<int> num : matrix) {
		for (int numm : num) {
			std::cout << numm << " ";
		}
		std::cout << std::endl;
	}

	func();

	//结构体与vector
	struct Stu
	{
		std::string name;
		int age;
	};

	std::vector<Stu> students;
	
	students.push_back({ "nada",1});
	students.push_back({ "da", 21 });
	students.push_back({ "zzz", 2 });	

	for (auto items : students) {
		std::cout << items.age << " " << items.name << std::endl;
	}

	return 0;
}

