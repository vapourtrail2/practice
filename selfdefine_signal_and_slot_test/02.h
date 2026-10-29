#include <QObject>
#include <QDebug>

class Sub : public QObject {
	Q_OBJECT
public:
	Sub() {
	}
	//槽函数是普通的成员函数
public slots://这样写也可以
	void receiveNewspaper(const QString& name) {
		qDebug() << "rec:" << name;
	}
};

// 在这个新写法中，C++ 编译器直接获取了 receiveNewspaper 函数的内存地址。
// 对于 C++ 编译器来说，receiveNewspaper 
// 只要是一个可以访问的普通成员函数（public）就行了。编译器不需要它被标记为“槽”
// 也不需要通过 MOC 系统去查字符串表。
