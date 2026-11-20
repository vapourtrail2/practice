#include <iostream>
#include <new>
#include <cstddef>
#include <cstdint>
using namespace std;

struct alignas(32) Data
{
    double values[4];
};

int main()
{
    int arr[3] = { 1,2,3 };
    std::cout <<arr[0];

    return 0;
}