#include <iostream>
#include <vector>
using namespace std;

/*
    场景：定时器定时触发更新（被观察者），其他模块（观察者）会随着更新每次触发自己的业务逻辑
*/

/*
默认实现
class ModelA
{
  public:
    void doSth()
    {
        cout<<"模块A触发业务逻辑"<<endl;
    }
};

class ModelB
{
  public:
    void doSth()
    {
        cout<<"模块B触发业务逻辑"<<endl;
    }
};

class Timer
{
  public:
    void update() //定时触发逻辑
    {
        // 1：触发模块A的业务逻辑
        ModelA modelA;
        modelA.doSth();

        // 2：触发模块B的业务逻辑
        ModelB modelB;
        modelB.doSth();

        // 这种写法的缺点在于：每次加入新的模块都要改动update代码，需要重新编译。违反开闭原则（多拓展开发对修改封闭）
    };
};

*/

// 观察者模式实现

// 观察者基类
class BaseObserver
{
  public:
    virtual void doSth() = 0;
    virtual ~BaseObserver(){};
};

class ObserverA : public BaseObserver
{
  public:
    virtual void doSth() override
    {
        cout << "观察者A触发业务逻辑" << endl;
    }
};

class ObserverB : public BaseObserver
{
  public:
    virtual void doSth() override
    {
        cout << "观察者B触发业务逻辑" << endl;
    }
};

class Timer
{
  private:
    vector<BaseObserver *> handler;

  public:
    void addObserver(BaseObserver *observer)
    {
        handler.push_back(observer);
    };

    void removeObserver()
    {
        // 这里实现简单的删除最新的观察者
        handler.pop_back();
    };

    void update()
    {
        // 遍历所有的被观察者 通知他们（触发他们的业务逻辑）
        for (auto it = handler.begin(); it != handler.end(); it++) {
            (*it)->doSth();
        }
        // 有新增模块，无法改动update中的函数，update这块可以复用，维护了开闭原则（对修改封闭，对拓展开放）
    }
};

int main()
{
    Timer timer;

    timer.addObserver(new ObserverA);
    timer.addObserver(new ObserverB);
    timer.update();

    return 0;
}