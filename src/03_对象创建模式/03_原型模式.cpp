#include <iostream>
using namespace std;
/*
    原型模式：
        有一个原型，每次创建时通过克隆原型，可以避免new操作。
        主要适用于对象的创建很复杂、耗时、昂贵的场景

    "比如：某个工具类的构造需要连接数据库，加载500MB的AI模型，耗时10s。如果是工厂模式，每次内部都是new一个工具类，
	会开销特别的大，而原型模式内部是走的拷贝构造，避免闯将的开销"
*/

//====================================================
// 文件分割器基类
class ISpliter
{
  public:
    virtual void split() = 0;
    virtual ISpliter* clone()=0;
    virtual ~ISpliter(){};
};

class BinaryFileSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "二进制文件分割中...." << endl;
    }

    virtual ISpliter *clone() override
    {
        return new BinaryFileSpliter(*this); //这里相当于用拷贝构造clone一个对象返回出去。
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

    virtual ISpliter *clone() override
    {
        return new VideoFileSpliter(*this); 
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

    virtual ISpliter *clone() override
    {
        return new TxtFileSpliter(*this); 
	}
};

// 使用的场景
class FileProcessTool
{
  private:
    ISpliter *spliter;
    
  public:
    void split(ISpliter *prototype)
    {
        spliter = prototype->clone();
        spliter->split();
    }
};

void Process()
{
    FileProcessTool tool;

    BinaryFileSpliter *binary = new BinaryFileSpliter();

    tool.split(binary);	// 内部拷贝 binary 后，调用
    tool.split(binary); // 内部拷贝 binary 后，调用 

    VideoFileSpliter *video = new VideoFileSpliter();
    tool.split(video);

    TxtFileSpliter *txt = new TxtFileSpliter();
    tool.split(txt);
}


int main()
{
	Process();
    return 0;
}