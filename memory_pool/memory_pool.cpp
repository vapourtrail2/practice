#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <new>
#include "memory_pool.h"

//内存池提供存储空间。
// New 构造业务对象。
//显式析构结束业务对象生命周期。
//内存池重新构造 Freeblock，接管这块存储。

//new是申请一个新的动态内存 然后在这个内存上创建对象
//placement new 是在ptr指向的地址上创建对象
struct Test
{
    int v;
    
    Test(int v) : v(v) {
        std::cout << "construction" << std::endl;
    }

    ~Test() {
        std::cout << "destruction" << std::endl;
    }
};

struct alignas(32) Data
{
    double arr[4];
};


Memory_Pool::Memory_Pool(std::size_t poolsize, std::size_t blocksize):poolSize_(poolsize),blockSize_(blocksize)
{
    if (poolSize_ == 0 || blockSize_ == 0) {
        throw std::invalid_argument("blockSize and poolSize cannot be zero");
    }

    if (blockSize_ > poolSize_) {
        throw std::invalid_argument("blockSize can not bigger than poolSize_ error");
    }

    if (blockSize_ < sizeof(Freeblock)) {
        throw std::invalid_argument("block is not big ,can not place the Freeblock");
    }

    //if (poolSize_ % blockSize_ != 0)
    //{
    //    throw std::invalid_argument("不能被整除");
    //}

    if (blockSize_ % alignof(Freeblock) != 0) {
        throw std::invalid_argument("alignment is error");
    }

    memory_ = new char[poolSize_];

    //除了满足内存大小 还得考虑内存地址是否满足对象的类型对齐原则
    for (size_t i = 0; i < poolSize_ / blockSize_; i++)
    {
        char* block = memory_ + blockSize_ * i;//每个block指向每个块的首地址
        //构造链表
        Freeblock* node = new (block) Freeblock;//在当前内存块构造节点
        freeCount_++;
        node->next = freeList_;
        freeList_ = node;
    }
}

Memory_Pool::~Memory_Pool()
{
    delete[] memory_;
}

//问题: 一次分配一个内存块，而不是在内部分配11次  2.返回分配出去的内存块地址 而不是freeList_引用
//返回void* 提供原始内存
//已经分配的内存用指针管理 也就是p1->block15 p2->block14... 没分配出去的用freeList_管理
void* Memory_Pool::allocate_Memory()
{
    if (freeList_ == nullptr)
    {
        return nullptr;
    }
    
    //用不同的指针返回 而不是用内部的指针返回
    Freeblock* res = freeList_;
    freeList_ = res->next;
    freeCount_--;
    res->~Freeblock();//释放block中freelist的生命周期
    //结束Freelist生命周期 ->原始空间内存等待使用  ->placement new构造业务对象，using .... ，然后析构业务对象 再调用ruturn memory ，创建对象 新的Freelist对象进入链表
    return res;
}

//放回FreeList里面  
void Memory_Pool::return_Memory(void* ptr)
{
    if (ptr == nullptr) {
        return;
    }

    //Freeblock* res = static_cast<Freeblock*>(ptr);
    Freeblock* res = new (ptr) Freeblock;//在ptr指向的地方 重新构造一个FreeBlock对象 因为对象都已经析构完了 所以需要在这个内存上新建一个fb对象 然后按照逻辑重新构造链表
    res->next = freeList_;
    freeCount_++;
    freeList_ = res;
}
//还是可以遍历到 不过是两个指针指向一个节点，但是你如果用副本的话操作不会影响到freeList_。因为只是统计数据
//遍历时间复杂度O(n) 现在这么改时间复杂度就是O(1)
int Memory_Pool::count_size() const//这意味着函数调用时，会创建一个新的指针变量 freeList，将传入的地址复制给它。
{
    return freeCount_;
    //int count = 0;
    //auto ptr = freeList_;
    //while (ptr != nullptr)
    //{
    //    ptr = ptr->next;
    //    count++;
    //}
    //return count;
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

    //Memory_Pool pool(1024, 64);
    //void* p1 = pool.allocate_Memory();
    //void* p2 = pool.allocate_Memory();
    //void* p3 = pool.allocate_Memory();

    ////std::cout << p1 << " " << p2 << " " << p3 << std::endl;
    //std::cout << pool.count_size() << std::endl;
    //pool.return_Memory(p2);
    //std::cout << pool.count_size() << std::endl;
    
    //void* p = pool.allocate_Memory();
    //Test* obj = new (p) Test(100);
    //std::cout << obj->v << std::endl;
    //obj->~Test();
    //pool.return_Memory(p);

    try
    {
        Memory_Pool pool(1024, 0);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "参数错误" << e.what() << std::endl;
    }
   
    //try
     //{
     //    Memory_Pool pool(1000, 64);
     //}
     //catch (const std::invalid_argument& e)
     //{
     //    std::cout << "参数错误" << e.what() << std::endl;
     //}

    try
    {
        Memory_Pool pool(1024, 4);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "参数错误" << e.what() << std::endl;
    }
    try
    {
        Memory_Pool pool(1024, 10);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "参数错误" << e.what() << std::endl;
    }

    
    //auto &ptr= pool.allocate_Memory();//ptr是freeList_的另一个名字
    //int a =pool.count_size(ptr);
    //std::cout << "分配后的空闲链表节点个数:" << a << std::endl;
    //pool.return_Memory(&ptr);
    //int b = pool.count_size(ptr);//实参里取地址解引用他就是取地址解引用
    //std::cout << "回收后的空闲链表节点个数:" << b << std::endl;
    
    return 0;
}
