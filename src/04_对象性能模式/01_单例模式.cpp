#include <algorithm>
#include <iostream>
#include <mutex>
using namespace std;

/*
    保证一个类只有一个实例，并保证该实例只有一个全局访问点
*/

// 懒汉单例：使用时才创建单例（注意线程安全）
// 线程安全的主流写法有：直接最外层加锁（性能差）、局部静态变量的懒初始化实现、C++11的call_once实现;
// 注意，双重检查的写法，看似比最外层加锁性能好，但是由于cpu的指令重拍，会有bug，可以用atomic实现安全版本但过于复杂，不推荐

// 版本1：利用 局部static变量的懒初始化原理
class LazySingleTon
{
  private:
    LazySingleTon();
    LazySingleTon(const LazySingleTon &) = delete;
    LazySingleTon operator=(const LazySingleTon &) = delete;

  public:
    static LazySingleTon &GetInstance()
    {
        // 核心魔法：局部static的懒初始化原理，c++11保证线程安全
        // C++11 标准保证：如果多个线程同时试图初始化同一个静态局部变量
        // 只有第一个线程能初始化，其他线程会阻塞直到初始化完成。
        static LazySingleTon instance;
        return instance;
    }
};

// 版本2：利用C++11的once_flag实现
class LazySingleTon2
{
  private:
    static LazySingleTon2 *instance;
    static std::once_flag init_flag;
    
  private:
    LazySingleTon2();
    LazySingleTon2(const LazySingleTon2 &) = delete;
    LazySingleTon2 operator=(const LazySingleTon2 &) = delete;

  public:
    static LazySingleTon2 *GetInstance()
    {
        // 核心魔法：std::call_once，多线程也只会执行一次
        // 第一个参数是 flag
        // 第二个参数是 lambda 表达式（或者函数指针），里面写初始化的逻辑
        std::call_once(init_flag, []() {
			instance = new LazySingleTon2(); 
		});
        
        return instance;
    }
};


// 饿汉单例:天生线程安全，static 成员变量在main函数开始前已经存在
class HungrySingleTon
{
  private:
    static HungrySingleTon instance; // 可以指针也可以对象，都行。区别是指针是new，在堆上要注意释放。对象版本在全局区，进程结束自己释放

  private:
    HungrySingleTon();
    HungrySingleTon(const HungrySingleTon &) = delete;
    HungrySingleTon operator=(const HungrySingleTon &) = delete;

  public:
    static HungrySingleTon &GetInstance()
    {
        return instance;
    }
};

// 静态变量需要类外定义
HungrySingleTon HungrySingleTon::instance = HungrySingleTon();

int main()
{

    return 0;
}
