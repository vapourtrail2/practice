#pragma once
#include <cstddef>
#include <vector>
#include <utility>
#include <cstdint>
#include <new>
#include <stdexcept>

struct  Freeblock
{
	Freeblock* next;//指向下一个Freeblock对象
};

//每次分配一个块
class Memory_Pool
{
public:
	Memory_Pool(std::size_t poolsize, std::size_t blocksize,std::size_t alignsize);
	~Memory_Pool();
	
	std::size_t count_size() const;
	

	//创建业务对象
	template <typename T,typename... Args>//可以推导出多个实参的多个类型
	T* create(Args... args) {//相当于接受 int args1, int args2  //这里发生一次拷贝 按值传递 虽然接受的是rvalue 但是args是有名字的变量 所以在这里他是作为左值

		if (sizeof(T) > blockSize_) {
			throw std::invalid_argument("object is too large");
		}

		if (alignof(T) > alignSize_)
		{
			throw std::invalid_argument("alignment is not appropriation，too large");
		}
		void* p = allocate_Memory();
		if (p == nullptr)
		{
			return nullptr;//返回空指针 ，表示没申请下来block
		}

		std::size_t index;

		if (!isMemoryPtr(p,index))
		{
			return_Memory(p);
			throw std::invalid_argument("invalid block");
		}
		try
		{
			T* obj = new (p) T(args...);//构造对象
			destructors_[index] = &destoryObject<T>;
			return obj;	
			//destructors_[index] = &callDestructor<T>;
		}
		catch (...)
		{
			return_Memory(p);
			throw;//为什么直接throw;
		}
		
	}

	//回收业务对象
	template<typename T>
	void destroy(T* obj) {
		if (obj == nullptr)
		{
			return;
		}

		size_t index = 0;
	    //判断这个指针在不在这个内存里
		if (!isMemoryPtr(obj, index)) {
			throw std::invalid_argument("invaild ptr");
		}
		
		if (is_address_ptr_used[index] == 0)
		{
			throw std::invalid_argument("is releady released");
		}
		
		obj->~T();//结束业务对象的生命周期
		return_Memory(obj);
	}

	Memory_Pool(const Memory_Pool&) = delete;//禁用拷贝构造函数
	Memory_Pool& operator=(const Memory_Pool&) = delete;//禁止拷贝赋值运算符

private:
	void* allocate_Memory();
	void return_Memory(void* ptr);
	bool isMemoryPtr(void* p, std::size_t& index) const;

	using Destructor = void(*)(void*);
	template<typename T>
	static void destoryObject(void* ptr) {//存进函数指针数组 需要static
		T* obj = static_cast<T*>(ptr);	
		obj->~T();//这里.不出来应该是没找到具体的析构函数 ，因为用的是模板 执行对应的析构函数
	}

private:
	
	std::size_t poolSize_;
	std::size_t blockSize_ = 0;	
	std::size_t alignSize_;
	std::size_t blockCount_  = 0 ;//总共多少个block
	std::vector<unsigned char> is_address_ptr_used;
	std::vector<Destructor> destructors_;//函数指针的容器，不同类型的对象调用不同类型的析构函数
	char* memory_ = nullptr;
	Freeblock* freeList_ = nullptr;
	std::size_t freeCount_ = 0;//记录freeList里的节点数
};

