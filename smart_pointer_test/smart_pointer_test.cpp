#include <iostream>
#include <memory>
#include <String>
#include <vector>
using namespace std;    

class Test
{
public:
    Test() { std::cout << " 构造被调用" << std::endl; }
    ~Test() { std::cout << " 析构被调用" << std::endl; }
    
    int getData() {
		return this->a;
    }
private:
    int a = 1;
};

//int main()
//{
//    //auto ptr
//    /*auto_ptr<string> str(new string("wuhuqifei"));*/
//
//	//Test* t = new Test();//堆区写法 t是指针 在栈区
//    //cout << t->getData() << endl;
//	//delete t;
//
//    //Test t;//栈写法
//    //std::cout<<t.getData()<<std::endl;//函数结束 t自动销毁
//
//	//使用智能指针  auto ptr  跟普通的差不多 不用手动delete了
//    /*std::auto_ptr<Test> t(new Test());
//	std::cout << t->getData() << std::endl;*/
//
//    //独占指针
//    /*std::unique_ptr<Test> t(new Test());
//	std::cout << t->getData() << std::endl;*/
//
// //   std::unique_ptr<std::string> str1(new std::string("dada"));
// //   std::unique_ptr<std::string> str2(new std::string("dadakj"));
//
// //   str1 = std::move(str2);//使用move把左值变成右值就可以赋值了
//	//std::cout << *str1 << std::endl;//str1 是 dadakj
//
//    //带容器
//    /*std::vector<std::unique_ptr<std::string>> vec01;
//    std::unique_ptr<std::string> p1(new std::string("dadaad"));
//    std::unique_ptr<std::string> p2(new std::string("wuhuqifei1"));
//
//    vec01.push_back(std::move(p1));
//    vec01.push_back(std::move(p2));
//
//    cout << *vec01[0] << endl;*/
//
//	//共享指针
//	//多个指针指向同一个对象 复制或者拷贝 引用计数+1 智能指针析构时 引用计数-1 计数为0时 自动释放内存
//
//    return 0;
//}

class Father;

class Son {
public:
    std::weak_ptr<Father> father;
};

class Father {
public:
    std::shared_ptr<Son> son;
    void say() {
        std::cout << "father obj hello" << std::endl;
    }
};

int main() {
    /*auto fatherptr = std::make_shared<Father>();
    auto sonptr = std::make_shared<Son>();

    fatherptr->son = sonptr;
    sonptr->father = fatherptr;*/
    //弱指针不允许 weak ->  如 sonptr->father->...xx();不允许
    /*auto temp =sonptr->father.lock();
    if (temp) {
        temp->say();
    }*/
   /* std::cout <<fatherptr.use_count()<< std::endl;
    std::cout << sonptr.use_count() << std::endl;*/

    std::weak_ptr<Father> weakfather;
    {   
        auto fatherptr = std::make_shared<Father>();
        weakfather = fatherptr;
		std::cout << fatherptr.use_count() << std::endl; // 输出 1
    }
    std::cout << weakfather.use_count() << std::endl;
    
    return 0;
    
}