#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>

double heavy_work(double x)
{
	double value = static_cast<int>(x);

	for (int i = 0; i < 100000; ++i)
	{
		value = std::sqrt(value + 1.0) + value * 0.000001;
	}

	return value;
}

template<typename I, typename T>
void acc(I first, I last, T* result,unsigned long block_id)
{
	//std::cout << "start block id:" << block_id << "  t_id :" << std::this_thread::get_id() << std::endl;

	T sum = 0;

	for (;first != last;first++) {
		auto a = heavy_work(*first);
		sum += a;
	}

	*result = sum;

	//std::cout << "end block id:" << block_id << "  t_id :" << std::this_thread::get_id() << std::endl;//使用mutex解决原子操作的问题
}

template<typename I, typename T>
T mutilthread_process(I first, I last, T init)
{
    unsigned long vec_element_sum = std::distance(first, last);//容器元素总数量
	//return sum;

	unsigned long thread_process_minNum = 1000;

	unsigned long theroy_threads = (vec_element_sum + thread_process_minNum -1 ) / thread_process_minNum;
	
	unsigned long hard_Num = std::thread::hardware_concurrency();

	unsigned long utimate_threads_Num = std::min(hard_Num != 0 ? hard_Num : 2, theroy_threads);

	//std::cout << utimate_threads_Num << std::endl;

	unsigned long one_thread_process_which_data = vec_element_sum / utimate_threads_Num;
	
	//还需一个放结果的容器
	std::vector<T> result_vec(utimate_threads_Num);
	
    //创建线程对象放在容器里
	std::vector<std::thread> threads_in_vector(utimate_threads_Num-1);

	I firstplace = first;
	
	for (unsigned long i = 0; i < utimate_threads_Num - 1; i++)
	{
		I lastplace = firstplace;
		
		std::advance(lastplace, one_thread_process_which_data);//移动迭代器指针 
		
		threads_in_vector[i] = std::thread(	
			acc<I,T>,
			firstplace,
			lastplace,
			&result_vec[i]
			,i
		);

		std::cout << "block id " << i << "t_id :" << threads_in_vector[i].get_id() << std::endl;

		firstplace = lastplace;
	}

	acc<I, T>(
		firstplace,
		last,
		&result_vec[utimate_threads_Num - 1],
		utimate_threads_Num - 1);

	std::cout
		<< "block " << utimate_threads_Num - 1
		<< " main thread id = "
		<< std::this_thread::get_id()
		<< std::endl;
	
	for (auto& t : threads_in_vector) {
		t.join();
	}

	return std::accumulate(
		result_vec.begin(),
		result_vec.end(),
		init//返回这个？
	);
	
}

int main() {
	std::vector<int> vec;
	for (int i = 1; i <= 10000; i++)
	{
		vec.push_back(i);
	}

	std::cout << " ";
	//unsigned long long a = std::accumulate(vec.begin(), vec.end(), 0ULL);
	//for (auto& v : vec) {
	//	std::cout << v << " ";
	//}

	//mutilthread_process<std::vector<int>::iterator, int>;
	auto start1 = std::chrono::high_resolution_clock::now();
	double a = mutilthread_process(vec.begin(), vec.end(), 0.0);
	//auto end1 = std::chrono::high_resolution_clock::now();
	//std::cout << "多线程结果" << a << std::endl;
	//std::cout << "多线程耗时"
	//	<< std::chrono::duration<double, std::milli>(end1 - start1).count()
	//	<< " ms" << std::endl;


	//auto start2 = std::chrono::high_resolution_clock::now();
	//double b = 0;
	//for (auto& v : vec) {
	//	b = heavy_work(v) + b;
	//}
	//auto end2 = std::chrono::high_resolution_clock::now();
	//std::cout << "单线程结果" << b << std::endl;
	//std::cout << "单线程耗时"
	//	<< std::chrono::duration<double, std::milli>(end2 - start2).count()
	//	<< " ms" << std::endl;

	
	return 0;
}
