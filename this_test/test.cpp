#include <stdio.h>
#include <iostream>
using namespace std;

class A {
public:
	int x;
	void func() {
		x = 10;
	}
};

int main() {
	A a;
	a.func();
	cout << a.x<< endl;
	return 0;
}	