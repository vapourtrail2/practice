#include <iostream>
#include <utility>

/*
如果没有正确处理拷贝构造，可能发生浅拷贝和重复释放。

如果没有正确处理移动构造，可能无法高效转移资源。

如果没有正确处理析构函数，可能发生内存泄漏。*/
class Buffer
{
public:
	Buffer(int size) :size_(size),ptr_(new int[size]){
		std::cout << "construction" << std::endl;
	};

	Buffer(const Buffer& other) {//Buffer b = a 先创建b 然后用a初始化b 需要有一个函数接受a 初始化b
		size_ = other.size_;
		ptr_ = new int[size_];
	
		//深拷贝
		for (size_t i = 0; i < size_; i++)
		{
			ptr_[i] = other.ptr_[i];
		}
		//std::cout << "2" << std::endl;
	}

	//拷贝赋值运算符
	Buffer& operator=(const Buffer& other) {
		if (this == &other) {
			return *this;
		}

		int* newPtr = new int[other.size_];//重新申请

		for (int i = 0; i < other.size_; i++)
		{
			newPtr[i] = other.ptr_[i];
		}

		//释放旧数组
		delete[] ptr_;
	
		ptr_ = newPtr;
		size_ = other.size_;	

		return *this;
	}

	//不需要释放旧资源
	Buffer(Buffer&& other) noexcept {
		size_ = other.size_;
		ptr_ = other.ptr_;

		other.size_ = 0;
		other.ptr_ = nullptr;
		//std::cout << "3" << std::endl;
	}

	//需要释放旧资源
	Buffer& operator=(Buffer&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		//释放旧数组
		delete[] ptr_;//接受新数组，得把旧的delete了 因为Buffer a ;Buffer b ; 必须先把a的数组移除了。 必须清理b原来的资源

		ptr_ = other.ptr_ ;
		size_ = other.size_;

		other.size_ = 0;
		other.ptr_ = nullptr;

		return *this;
	}

	void setValue(int index, int v) {
		ptr_[index] = v;
	}

	int getValue(int index) const {
		return ptr_[index];
	}

	//如果没有正确处理析构函数 可能会造成内存泄露
	~Buffer() {
		delete[] ptr_;
	};

private:
	int size_  = 0;
	int* ptr_ = nullptr;
};

int main() {
	//Buffer b1(10);
	//Buffer b2 = b1;
	//Buffer b3 = std::move(b2);

	Buffer b1(3);
	b1.setValue(0, 199);
	b1.setValue(1, 199);
	b1.setValue(2, 199);

	Buffer b2 = b1;
	
	b2.setValue(0, 999);

	std::cout << b1.getValue(0) << " " << b2.getValue(0);

	return 0;
}