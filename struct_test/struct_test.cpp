#include <iostream>

struct Student
{
	int age;
	std::string name;
	double score;//double类型占8个字节 float类型占4个字节
	
	//还有构造函数
	Student(int sage, std::string sname, double sscore) :
		age(sage), name(sname), score(sscore) 
	{
	}
};

struct Point
{
	int x;
	int y;
};

class Rectangle
{
public:
	/*Rectangle() {}*/
	void setDim(int w, int h)
	{
		width = w;
		height = h;
	};

	int getwidth()
	{
		return width;
	};

	int getheight()
	{
		return height;
	};

private:
	int width;
	int height;
};

void movePoint(Point &p, int dx ,int dy)
{
	p.x += dx;
	p.y += dy;
}

struct Rec{
	int z;
	int v;
};

struct Area
{
	int value;
};

//函数体返回结构体
Area calArea(Rec &rec) {
	Area a;
	a.value = rec.z * rec.v;
	return a;
}


int main()
{
	/*Student s1;
	s1.age = 18;
	s1.name = "shijin";
	s1.score = 99.5;*/

	/*Student s2(11,"sss",11.2);
	std::cout << s2.age << " " << s2.name << " " << s2.score << std::endl;*/

	/*Rectangle rect;*/
	/*auto rect = new Rectangle();*/
	
	//无法访问私有变量
	/*rect->width;*/

	/*std::cout << rect << std::endl;
	rect->setDim(10, 55);
	std::cout << rect->getheight();

	delete rect;
	rect = nullptr;*/

	//作为参数传入函数中
	/*Point P{ 1,2 };
	movePoint(P, 3, 4);
	std:: cout << P.x << " " << P.y << std::endl;*/

	Rec rec{ 5, 10 };
	Area B = calArea(rec);
	std::cout << "Area: " << B.value << std::endl;
	
	return 0;
}
