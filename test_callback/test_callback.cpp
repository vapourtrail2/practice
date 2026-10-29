#include <iostream>
#include <functional>
using namespace std;

//回调函数；
/*
    把一段可执行的函数逻辑，当成参数保存起来。等到某个时机再由别人反过来调用它
    关键点:你把函数交给别人  别人再来调用你
*/

/*
    函数指针
*/

void OnComplete(bool a) {//你
    cout << "is called  " << a << endl;
}

//函数指针写法 void (*func)(bool)  
void loadFile(function<void(bool)> func) {//别人
    cout << "1234" << endl;
	bool ok = true;
    
    if (func) {
        func(ok);
    }
}

int main()
{
	loadFile(OnComplete);
	return 0;
}