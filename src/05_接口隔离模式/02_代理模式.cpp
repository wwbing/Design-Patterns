#include <iostream>
/*
    代理模式：为子系统提供一致的（稳定）界面，定义高层接口使子系统更易复用
		中间层隔离
*/

//  ========== 原始实现 ：不采用代理隔离 ===========

/*
// 抽象基类
class ISubject
{
  public:
    virtual void Process()=0;
};

class RealSubject:public ISubject
{
  public:
    virtual void Process() override
    {
        //具体业务逻辑
    }
};

// 客户端
class ClentApp
{
  private:
    ISubject* subject;

  public:
    ClentApp()
    {
        subject = new RealSubject();
    }

    void func()
    {
        // 直接访问，没有进行中间层隔离
        subject->Process();
    }
};
*/

//  ========== 代理模式实现 ===========

// 抽象基类
class ISubject
{
  public:
    virtual void Process()=0;
};

class RealSubject:public ISubject
{
  public:
    virtual void Process() override
    {
        //具体业务逻辑
    }
};

// 代理类
class SubjectProxy
{
  private:
    ISubject *subject;

  public:
    SubjectProxy()
    {
        subject = new RealSubject();
    }

    // 间接访问，中间层隔离
    void process()
    {
        subject->Process();
	}
};


// 客户端
class ClentApp
{
  private:
    SubjectProxy* proxy;

  public:
    ClentApp()
    {
        proxy = new SubjectProxy();
    }

    void func()
    {
        // 通过代理类间接访问
        proxy->process();
    }
};

int main()
{
    return 0;
}