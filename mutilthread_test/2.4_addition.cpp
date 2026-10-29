#include <iostream>
#include <numeric>
#include <vector>

template <typename T>
void print(T v) {
	std::cout << v << std::endl;
}

// struct operator 和 template
template<typename Iterator, typename T>
struct func
{
	int operator()(Iterator fir, Iterator end, T& woqu)
	{
		return std::accumulate(fir, end, woqu);
	}
};

int main() {
	//int i = 1;
	//print(i);
	//std::vector<int> v{ 1,2,3,4,5 };
	//int res = std::accumulate(v.begin(),v.end(), 0);
	//std::cout << "res: " << res << std::endl;

	int res = 0;
	
	std::vector<int> v = { 1,3,4,5,6 };
	
	func<std::vector<int>::iterator,int> c;
	
	int a = c(v.begin(), v.end(), res);

	std::cout << a;
	return 0;
}
