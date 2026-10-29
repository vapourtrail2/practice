#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>

template<typename Iterator, typename T>
struct accumulate_block
{
     void operator()(
        Iterator first,
        Iterator last,
        T* result)
    {
        
        *result  = std::accumulate(//执行这个之后 ，result[i] 然后*result销毁
                first,
                last,
                *result
            );
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(
    Iterator first,
    Iterator last,
    T init)
{
    unsigned long const length =
		std::distance(first, last);//总元素数

    if (!length)
        return init;

	unsigned long const min_per_thread = 25;//每个线程最少处理的元素数

    unsigned long const max_threads = //理论最大开启线程数
        (length + min_per_thread - 1)
        / min_per_thread;

    unsigned long const hardware_threads =
        std::thread::hardware_concurrency();
    
    unsigned long const num_threads =
        std::min(
            hardware_threads != 0
            ? hardware_threads
            : 2,
            max_threads
        );//实际需要的线程数

    unsigned long const thread_in_data = length / num_threads;//每个线程分多少数据

    std::vector<T> results(num_threads);//每个线程把自己的结果写回这个result里面

    std::vector<std::thread> threads(num_threads - 1);//创建线程 ，减去一个主线程

    Iterator block_start = first;

    for (unsigned long i = 0;
        i < num_threads - 1;
        ++i)
    {
        Iterator block_end = block_start;

        std::advance(
            block_end,
            thread_in_data
        );//移动25个元素

        accumulate_block<Iterator, T> temp;

         std::thread thread(
            temp,
            block_start,
            block_end,
            &results[i]);

         threads[i] = std::move(thread);
        

        block_start = block_end;

    }

    accumulate_block<Iterator, T>()(
        block_start,
        last,
        &results[num_threads - 1]
        );

    for (auto &t :threads)
    {
        t.join();
    }
    
    for (int i = 0; i < num_threads; i++)
    {
        std::cout << results[i] << " ";
    }

    return std::accumulate(
        results.begin(),
        results.end(),
        init
    );
}

int main() {
    std::vector<int> vec ;
    for (int i = 1; i <= 100; i++)
    {
        vec.push_back(i);
    }

    parallel_accumulate<std::vector<int>::iterator, int>;
    int a = parallel_accumulate(vec.begin(),vec.end(),0 );
    std::cout << a;
    return 0;
}