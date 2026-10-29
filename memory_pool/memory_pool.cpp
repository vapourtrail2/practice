#include <iostream>
#include <cstddef>
#include <new>
#include "memory_pool.h"
//但是这版有问题就是不能给外部一个引用 不然会绕开private修改freeList_ 11

Memory_Pool::Memory_Pool(std::size_t poolsize, std::size_t blocksize)
{
    poolSize_ = poolsize;
    blockSize_ = blocksize;
    memory_ = new char[poolSize_];

    for (size_t i = 0; i < poolSize_ / blockSize_; i++)
    {
        char* block = memory_ + blocksize * i;//每个block指向每个块的首地址
        //构造链表
        Freeblock* node = new (block) Freeblock;//在当前内存块构造节点
        node->next = freeList_;
        freeList_ = node;
    }
}

Memory_Pool::~Memory_Pool()
{
    delete[] memory_;
}

Freeblock*& Memory_Pool::allocate_Memory()
{
    
    if (freeList_ != nullptr)
    {
        for (int i = 0; i < 11; i++)
        {
            if (freeList_ == nullptr) {//内存已经分配完毕
                std::cout << "memory_pool is fulled" << std::endl;
                break;
            }
            allocated[i] = freeList_;
            freeList_ = freeList_->next;
            //std::cout << "current allocated address :" << allocated[i] << std::endl;
        }
    }
    return freeList_;
}

void Memory_Pool::return_Memory(void* ptr)//好像有点问题
{
    for (int i = 0; i < 11; i++)
    {
        if (allocated[i] != nullptr) {
            allocated[i]->next = freeList_;
            freeList_ = allocated[i];
            allocated[i] = nullptr;
        }
    }
}

int Memory_Pool::count_size(Freeblock* freeList)//这意味着函数调用时，会创建一个新的指针变量 freeList，将传入的地址复制给它。
{//还是可以遍历到 不过是两个指针指向一个节点，但是你如果用副本的话操作不会影响到freeList_。因为只是统计数据
    int count = 0;
    while (freeList != nullptr)
    {
        freeList = freeList->next;
        count++;
    }

    return count;
}

//利用链表管理内存块
int main()
{
    ////内存分块
    //std::size_t poolsize = 1024;
    //std::size_t blocksize = 64;
    //
    //char* memory = new char[poolsize];//分配 1024 个 char 类型的元素，动态申请连续的 1024 个字节的空间 new[] 会根据数据类型和元素数量，计算需要分配的内存大小
    // 
    ////std::cout << "首地址" << static_cast<void*>(memory) << std::endl;

    //Freeblock* freeList = nullptr;//表头指针
    //for (size_t i = 0; i < poolsize / blocksize; i++)
    //{
    //    char* block =  memory + blocksize*i ;//每个block指向每个块的首地址
    //    //构造链表
    //    Freeblock* node = new (block) Freeblock;//在当前内存块构造节点
    //    node->next = freeList;
    //    freeList = node;
    //    
    //    //std::cout << "第" << i << " 个block" << " ";
    //    //std::cout << "block 起始下标" << i << "起始地址" << static_cast<void*>(block) << std::endl;
    //}
    //
    ////从链表分配内存块
    //Freeblock* allocated[16] = { nullptr };
    //if (freeList != nullptr)
    //{
    //    for (int i = 0; i < 16; i++)
    //    {
    //        if (freeList == nullptr) {//内存已经分配完毕
    //            std::cout << "memory_pool is fulled" << std::endl;
    //            break;
    //        }
    //        allocated[i] = freeList;
    //        freeList = freeList->next;
    //        //std::cout << "current allocated address :" << allocated[i] << std::endl;
    //    }
    //}
    //int pre_count = count_size(freeList);
    //std::cout << "分配后的空闲链表节点个数:" << pre_count << std::endl;

    ////回收内存，就是把数组的指针加回空闲链表中
    ////if (freeList != nullptr)  这个不能写，万一freelist满了 ，freelist -> nullptr了 就没法回收内存了
    ////{
    //for (int i = 0; i < 16; i++)
    //{
    //    if (allocated[i] != nullptr) {
    //        allocated[i]->next = freeList;
    //        freeList = allocated[i];
    //        allocated[i] = nullptr;
    //    }
    //}
    ////}

    //int later_count = count_size(freeList);
    //std::cout << "回收后的空闲链表节点个数:" << later_count << std::endl;
    //delete[] memory;

    Memory_Pool pool(1024, 64);
    auto &ptr= pool.allocate_Memory();//ptr是freeList_的另一个名字
    int a =pool.count_size(ptr);
    std::cout << "分配后的空闲链表节点个数:" << a << std::endl;
    pool.return_Memory(&ptr);
    int b = pool.count_size(ptr);//实参里取地址解引用他就是取地址解引用
    std::cout << "回收后的空闲链表节点个数:" << b << std::endl;
    
    return 0;
}
