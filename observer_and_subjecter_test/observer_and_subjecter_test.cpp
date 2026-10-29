#include <iostream>
#include <string>
#include <list>

/*
*   obs创建时 就把自己从构造函数中注册到sub里
*   sub一有消息  就遍历list里的obs
*   obs收到消息 调用update()
*/

class IObserver {
public:
    virtual ~IObserver()
    {

    }
    virtual void update(const std::string& message) = 0;
};

class ISubjecter {
public:
    virtual ~ISubjecter()
    {

    }
    virtual void Attach(IObserver* obs) = 0;
    virtual void Detach(IObserver* obs) = 0;
    virtual void Notify() = 0;
};

class Subjecter : public ISubjecter {
public:
    virtual ~Subjecter() {}
    
    virtual void Attach(IObserver* obs)  override
    {
        observers_.push_back(obs);
    }

    virtual void Detach(IObserver* obs)  override
    {
        observers_.remove(obs);
    }

    void setMessage(const std::string& message) {
        message_ = message;
        Notify();
    }

    virtual void Notify() override
    {
        for (auto observer : observers_)
        {
            observer->update(message_);
        }
    }
    
private:
    std::list<IObserver*> observers_;//为什么用父类的类型 这就是为什么要多态了 如果有Emailobs和Logobs的话 都可以添加到这个list里
    std::string message_;
};

class Observer : public IObserver {
public:
    virtual ~Observer() {
        subject_.Detach(this);
    }

    Observer(int num, ISubjecter& subject) :
        num_(num), subject_(subject) {
        subject_.Attach(this);
    }

    virtual void update(const std::string& message) override
    {
        messagee_ = message;
        std::cout << "message is" << messagee_ << std::endl;
    }

private:
    //需要知道自己收到的消息 自己订阅的发布者
    ISubjecter& subject_;//为什么不用*  想取消订阅 必须知道这个obs订阅的sub 所以要有这个sub  。第二 不应该依赖具体的sub 用接口
    std::string messagee_;
    int num_;//第几个obs
};

int main()
{
    Subjecter sub;
    Observer ob1(1, sub);
    Observer ob2(2, sub);
    Observer ob3(3, sub);

    sub.setMessage("ddd");

    return 0;
}
