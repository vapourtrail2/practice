#include <iostream>
#include <functional>

//»Øµ÷º¯Êý

void func() {
	std::cout << "11";
}

class Button {
public:

	void setfunction(std::function<void()> func) {
		m_function = func;
	}

	void printfunction() {
		m_function();
	}

private:
	std::function<void()> m_function;
};

int main() {
	Button btn;
	btn.setfunction(func);
	btn.printfunction();
}