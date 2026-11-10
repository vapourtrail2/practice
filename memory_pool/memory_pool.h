#pragma once
#include <cstddef>
#include <vector>

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
	int count_size() const;
	bool isMemoryPtr(void* p, std::size_t& index) const;

	Memory_Pool(const Memory_Pool&) = delete;//禁用拷贝构造函数
	Memory_Pool& operator=(const Memory_Pool&) = delete;

private:
	std::size_t poolSize_;
	std::size_t blockSize_;
	std::size_t alignSize_;
	std::size_t blockCount_ = poolSize_ / blockSize_;
	std::vector<unsigned char> is_address_ptr_used;
	char* memory_ = nullptr;
	Freeblock* freeList_ = nullptr;
	std::size_t freeCount_ = 0;//记录freeList里的节点数
};

