#include <iostream>

class Base
{
public:
	virtual void func() {
		std::cout << "Base func" << std::endl;
	}
};

int main()
{
	Base* p = new Base();
	
	return 0;
}
