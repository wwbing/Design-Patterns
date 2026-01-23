#include <iostream>
using namespace std;
/*
    原型模式：
		有一个原型，每次创建时通过克隆原型，可以避免new操作。
		主要适用于创建的对象很复杂
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
    tool.split(binary);

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