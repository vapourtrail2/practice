#include <iostream>
#include <vector>

class DataManager {
public:
	void setData(std::vector<float>&& v) { //&&表示 接受可以移动的右值引用 比如std::vector<int>{1,2,3} 还有std::move(v) 这种显式的右值引用
		std::cout << "move setData\n";
		volume_ = std::move(v);//这里也要用 move(v) 因为v有名字 是左值 所以用move(v) 就是把v变成右值 
	}

	void setData(const std::vector<float>& v) {
		std::cout << "copy setData\n";
		volume_ = v;
	}

	const std::vector<float>& volume()  {
		//为什么加&  加了& 就是返回volume_本身 不加就是返回拷贝
		return volume_;
	}
	//第一个const的意思是返回的vector<float>对象不能被修改 
private:
	std::vector<float> volume_;
};

int main()
{
	std::vector<float> v;
	v.resize(512 * 512* 512);
	
	DataManager manager;
	//manager.setData(v);//复制一份给manager 很慢
	//std::cout << manager.volume().size() << std::endl;
	//有时候我不想复制了 v的大内存不需要了 直接给manager v变成空壳
	manager.setData(std::move(v)); 
	std::cout << "v size: " << v.size() << std::endl;
	std::cout << "manage size: " << manager.volume().size() << std::endl;	

	return 0;
}
