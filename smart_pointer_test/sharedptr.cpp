#include <stdio.h>
#include <memory>
#include <iostream>
using namespace std;

class Person {
public:
	Person(int v) {
		this->no = v;
		cout << "constructor is called " << this->no << endl;
	}
	~Person()
	{
		cout << "destructor is called" << this->no << endl;
	}

private:
	int no;
};

//·Âº¯Êý ÄÚ´æÉ¾³ý
class DestructPerson {
public:

};

int main() {
	
	return 0;
}