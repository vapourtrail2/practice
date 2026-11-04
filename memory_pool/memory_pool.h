#pragma once
#include <cstddef>

struct  Freeblock
{
	Freeblock* next;//指向下一个Freeblock对象
};

//每次分配一个块
class Memory_Pool
{
public:
	Memory_Pool(std::size_t poolsize, std::size_t blocksize);
	~Memory_Pool();
	void* allocate_Memory();
	void return_Memory(void* ptr);
	int count_size() const;
	
private:
	std::size_t poolSize_;
	std::size_t blockSize_;
	char* memory_ = nullptr;
	Freeblock* freeList_ = nullptr;
	std::size_t freeList_count = 0;//记录freeList里的节点数
};

