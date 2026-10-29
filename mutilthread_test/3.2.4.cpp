#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <functional>

//3.2.4 两把互斥锁之间的死锁问题
class Data {
public:
	int value;
	std::mutex mut;
	Data(int v) : value(v) {

	}
};

//这种交换不会死锁
void swap_v_mutil_thread(Data &a, Data &b) {
	std::lock(a.mut, b.mut);
	std::lock_guard<std::mutex> lock_a(a.mut, std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(b.mut, std::adopt_lock);

	std::swap(a.value, b.value);
}

int main() {
 //   try {
 //       throw std::runtime_error("errorrrrrr");
 //   }
 //   catch (const std::exception& e) {
 //       // 显式打印到终端/控制台
 //       std::cerr << "is:    " << e.what() << std::endl;
 //   }
	//return 0; //try catch
	Data a(100);
	Data b(200);
	std::thread t1(swap_v_mutil_thread, std::ref(a), std::ref(b));
	std::thread t2(swap_v_mutil_thread, std::ref(b), std::ref(a));

	t1.join();
	t2.join();

	std::cout << a.value << b.value;

}