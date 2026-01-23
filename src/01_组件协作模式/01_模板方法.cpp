#include <iostream>
using namespace std;

// 底层库开发
class Lib
{
  public:
    void step1()
    {
        cout << "step1" << endl;
    }

    virtual void step2()=0; // 变化

    void step3()
    {
        cout << "step3" << endl;
    }

    virtual void step4()=0; // 变化

    void step5()
    {
        cout << "step5" << endl;
    }

    // 算法框架是稳定的，不变的。这是模板方法的核心
    void run()
    {
        step1();
        step2();
        step3();
        step4();
        step5();
    }

    virtual ~Lib();
};

// 应用层开发
class Application : public Lib
{
  public:
    void step2() override
    {
        cout << "step2" << endl;
    }

    void step4() override
    {
        cout << "step4" << endl;
	}
};

int main()
{
    Application a;
    a.run();
}