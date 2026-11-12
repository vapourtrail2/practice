#pragma once
#include <cstddef>
#include <vector>
#include <utility>
#include <cstdint>

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
	void* allocate_Memory();
	void return_Memory(void* ptr);
	std::size_t count_size() const;
	bool isMemoryPtr(void* p, std::size_t& index) const;
	template <typename T,typename... Args>//可以推导出多个实参的多个类型
	T* create(Args... args) {//相当于接受 int args1, int args2

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
		try
		{
			return new (p) T(args...);
		}
		catch (...)
		{
			return_Memory(p);
			throw;//为什么直接throw
		}
		
	}

	Memory_Pool(const Memory_Pool&) = delete;//禁用拷贝构造函数
	Memory_Pool& operator=(const Memory_Pool&) = delete;

private:
	std::size_t poolSize_;
	std::size_t blockSize_ = 0;
	std::size_t alignSize_;
	std::size_t blockCount_ = poolSize_ / blockSize_;
	std::vector<unsigned char> is_address_ptr_used;
	char* memory_ = nullptr;
	Freeblock* freeList_ = nullptr;
	std::size_t freeCount_ = 0;//记录freeList里的节点数
};

