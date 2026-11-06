#include <iostream>
#include <new>
#include <cstddef>
#include <cstdint>

struct alignas(32) Data
{
    double values[4];
};

int main()
{
    std::size_t poolSize = 1024;
    std::size_t alignment = alignof(Data);

    // 按照 32 字节对齐要求申请原始内存
    void* memory = ::operator new(
        poolSize,
        std::align_val_t{ alignment }
        );

    std::uintptr_t address_int_value = reinterpret_cast<std::uintptr_t>(memory);

    std::cout << address_int_value % alignment << std::endl;

    ::operator delete(memory, std::align_val_t{ alignment });

    return 0;
}