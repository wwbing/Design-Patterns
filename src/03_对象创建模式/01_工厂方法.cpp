#include <iostream>
using namespace std;

/*
    定义一个用于创建对象的接口，让子类决定实例化哪一个类。
    Factory Method 使得一个类的实例化延迟到子类
*/

// 假想业务场景：文件分割器。各种文件分割器

/*
//  ========== 原始实现 ： 抽象基类 + 具体子类===========
class ISpliter
{
  public:
    virtual void split() = 0;
    virtual ~ISpliter(){};
};

class BinaryFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "二进制文件分割中...." << endl;
    }
};

// 音频文件分割器
class VideoFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "音频文件分割中...." << endl;
    }
};

// 文本文件分割器
class TxtFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "文本文件分割中...." << endl;
    }
};

// 使用的场景
class FileProcess
{
  private:
    ISpliter* spliter;
  public:
    void split()
    {
        // 问题：依赖具体类
        spliter = new BinaryFileSpliter();
        // spliter = new TxtFileSpliter();
        // spliter = new VideoFileSpliter();
        // ......
    }
};

*/

// 工厂方法

//====================================================
// 文件分割器基类
class ISpliter
{
  public:
    virtual void split() = 0;
    virtual ~ISpliter(){};
};

class BinaryFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "二进制文件分割中...." << endl;
    }
};

// 音频文件分割器
class VideoFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "音频文件分割中...." << endl;
    }
};

// 文本文件分割器
class TxtFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "文本文件分割中...." << endl;
    }
};

//====================================================
// 工厂基类
class FileSpliterFactory
{
  public:
    virtual ISpliter *createSplter() = 0;
    virtual ~FileSpliterFactory(){};
};

// 具体工厂
class BinaryFileSpliterFactory : public FileSpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new BinaryFileSpliter();
    };
};

class VideoFileSpliterFactory : public FileSpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new VideoFileSpliter();
    };
};

class TxtFileSpliterFactory : public FileSpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new TxtFileSpliter();
    };
};

// 使用的场景
class FileProcessTool
{
  private:
    ISpliter *spliter;
    
  public:
    void split(FileSpliterFactory *i_factory)
    {
        // 解决：编译时不依赖具体类（变化），依赖抽象工厂基类和分割器基类（稳定）
        // 具体创建哪个分割器不在编译器决定，而是运行时由外界传递的i_factory决定
        spliter = i_factory->createSplter();
        spliter->split();
    }
}; 

void Process()
{
    FileProcessTool tool;

    BinaryFileSpliterFactory *binary = new BinaryFileSpliterFactory();
    tool.split(binary);

    VideoFileSpliterFactory *video = new VideoFileSpliterFactory();
    tool.split(video);

    TxtFileSpliterFactory *txt = new TxtFileSpliterFactory();
    tool.split(txt);
}

int main()
{

    return 0;
}
