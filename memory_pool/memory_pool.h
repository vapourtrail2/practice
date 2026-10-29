#pragma once
#include <cstddef>

struct  Freeblock
{
	Freeblock* next;//指向下一个Freeblock对象
};

class Memory_Pool
{
public:
	Memory_Pool(std::size_t poolsize, std::size_t blocksize);
	~Memory_Pool();
	Freeblock*& allocate_Memory();
	void return_Memory(void* ptr);
	int count_size(Freeblock* freeList);
	
private:
	std::size_t poolSize_;
	std::size_t blockSize_;
	char* memory_;
	Freeblock* freeList_ = nullptr;
	Freeblock* allocated[16] = { nullptr };
};

