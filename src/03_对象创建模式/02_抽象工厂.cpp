#include <iostream>
using namespace std;

/*
    提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们的具体类。
*/

// 假想业务场景：文件分割器 + 跨平台支持

/*
    ========== 工厂方法遇到的问题 ==========
    假设现在需求变了：文件分割器需要在不同平台上运行
    - Windows 平台
    - Linux 平台
    - Mac 平台

    每个平台都有：二进制分割器、文本分割器、视频分割器

    如果用工厂方法，我们需要创建 3 * 3 = 9 个具体工厂类：
    - WindowsBinaryFactory, WindowsTxtFactory, WindowsVideoFactory
    - LinuxBinaryFactory, LinuxTxtFactory, LinuxVideoFactory
    - MacBinaryFactory, MacTxtFactory, MacVideoFactory

    问题：类数量膨胀！每增加一个平台，就要增加 N 个工厂类
    客户端代码复杂：需要协调多个工厂来创建一套产品
*/

/*
//====================================================
// 第一步：定义产品抽象基类

// 文件分割器基类
class ISpliter
{
  public:
    virtual void split() = 0;
    virtual ~ISpliter(){};
};

//====================================================
// 第二步：定义具体产品（多平台）

// Windows 平台
class WindowsBinarySpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Windows 二进制文件分割中...." << endl;
    }
};

class WindowsTxtSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Windows 文本文件分割中...." << endl;
    }
};

class WindowsVideoSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Windows 视频文件分割中...." << endl;
    }
};

// Linux 平台
class LinuxBinarySpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Linux 二进制文件分割中...." << endl;
    }
};

class LinuxTxtSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Linux 文本文件分割中...." << endl;
    }
};

class LinuxVideoSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Linux 视频文件分割中...." << endl;
    }
};

// Mac 平台
class MacBinarySpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Mac 二进制文件分割中...." << endl;
    }
};

class MacTxtSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Mac 文本文件分割中...." << endl;
    }
};

class MacVideoSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Mac 视频文件分割中...." << endl;
    }
};

//====================================================
// 第三步：使用工厂方法实现（类膨胀问题暴露）

// 工厂基类
class SpliterFactory
{
  public:
    virtual ISpliter *createSplter() = 0;
    virtual ~SpliterFactory(){};
};

// Windows 具体工厂
class WindowsBinaryFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new WindowsBinarySpliter();
    }
};

class WindowsTxtFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new WindowsTxtSpliter();
    }
};

class WindowsVideoFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new WindowsVideoSpliter();
    }
};

// Linux 具体工厂
class LinuxBinaryFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new LinuxBinarySpliter();
    }
};

class LinuxTxtFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new LinuxTxtSpliter();
    }
};

class LinuxVideoFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new LinuxVideoSpliter();
    }
};

// Mac 具体工厂
class MacBinaryFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new MacBinarySpliter();
    }
};

class MacTxtFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new MacTxtSpliter();
    }
};

class MacVideoFactory : public SpliterFactory
{
  public:
    virtual ISpliter *createSplter() override
    {
        return new MacVideoSpliter();
    }
};
*/

/*
    问题总结（工厂方法）：
    1. 类数量膨胀：3个平台 × 3种分割器 = 9 个工厂类
    2. 如果再加 Android、iOS 平台，类会爆炸！
    3. 客户端需要知道每个产品的具体工厂类，代码复杂
    4. 新增平台时，所有使用分割器的客户端代码都要改！
*/

/*
//====================================================
// 客户端使用 - 问题更明显
class FileProcessTool
{
  private:
    ISpliter *spliter;

  public:
    void process(SpliterFactory *factory)
    {
        spliter = factory->createSplter();
        spliter->split();
    }
};

void Process()
{
    FileProcessTool tool;

    // 问题：客户端需要知道每个产品的具体工厂
    // 切换平台时代码改动大

    // Windows 平台
    WindowsBinaryFactory *w_binary = new WindowsBinaryFactory();
    tool.process(w_binary);

    WindowsTxtFactory *w_txt = new WindowsTxtFactory();
    tool.process(w_txt);

    // Linux 平台
    LinuxBinaryFactory *l_binary = new LinuxBinaryFactory();
    tool.process(l_binary);

    LinuxVideoFactory *l_video = new LinuxVideoFactory();
    tool.process(l_video);

    // Mac 平台
    MacTxtFactory *m_txt = new MacTxtFactory();
    tool.process(m_txt);

}
*/
/*
工厂方法的问题：
        1. 每增加一个平台，就要新增 3 个工厂类
        2. 客户端代码中 new 了很多具体工厂类
        3. 如果要统一切换平台，需要改动很多地方

*/

//====================================================
// 抽象工厂实现
// 一个工厂类创建同一个平台的所有产品

//====================================================
// 第一步：定义产品抽象基类

// 文件分割器基类
class ISpliter
{
  public:
    virtual void split() = 0;
    virtual ~ISpliter(){};
};

//====================================================
// 第二步：定义具体产品（多平台）

// Windows 平台
class WindowsBinarySpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Windows 二进制文件分割中...." << endl;
    }
};

class WindowsTxtSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Windows 文本文件分割中...." << endl;
    }
};

class WindowsVideoSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Windows 视频文件分割中...." << endl;
    }
};

// Linux 平台
class LinuxBinarySpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Linux 二进制文件分割中...." << endl;
    }
};

class LinuxTxtSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Linux 文本文件分割中...." << endl;
    }
};

class LinuxVideoSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Linux 视频文件分割中...." << endl;
    }
};

// Mac 平台
class MacBinarySpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Mac 二进制文件分割中...." << endl;
    }
};

class MacTxtSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Mac 文本文件分割中...." << endl;
    }
};

class MacVideoSpliter : public ISpliter
{
  public:
    virtual void split() override
    {
        cout << "Mac 视频文件分割中...." << endl;
    }
};

//====================================================
// 第三步：抽象工厂模式实现

// 抽象工厂基类 - 一个工厂创建一整套产品
class FileSpliterFactory
{
  public:
    // 创建三种分割器
    virtual ISpliter *createBinarySpliter() = 0;
    virtual ISpliter *createTxtSpliter() = 0;
    virtual ISpliter *createVideoSpliter() = 0;
    virtual ~FileSpliterFactory(){};
};

// Windows 具体工厂 - 一套产品一个工厂
class WindowsFactory : public FileSpliterFactory
{
  public:
    virtual ISpliter *createBinarySpliter() override
    {
        return new WindowsBinarySpliter();
    }
    virtual ISpliter *createTxtSpliter() override
    {
        return new WindowsTxtSpliter();
    }
    virtual ISpliter *createVideoSpliter() override
    {
        return new WindowsVideoSpliter();
    }
};

// Linux 具体工厂 - 一套产品一个工厂
class LinuxFactory : public FileSpliterFactory
{
  public:
    virtual ISpliter *createBinarySpliter() override
    {
        return new LinuxBinarySpliter();
    }
    virtual ISpliter *createTxtSpliter() override
    {
        return new LinuxTxtSpliter();
    }
    virtual ISpliter *createVideoSpliter() override
    {
        return new LinuxVideoSpliter();
    }
};

// Mac 具体工厂 - 一套产品一个工厂
class MacFactory : public FileSpliterFactory
{
  public:
    virtual ISpliter *createBinarySpliter() override
    {
        return new MacBinarySpliter();
    }
    virtual ISpliter *createTxtSpliter() override
    {
        return new MacTxtSpliter();
    }
    virtual ISpliter *createVideoSpliter() override
    {
        return new MacVideoSpliter();
    }
};

//====================================================
// 客户端使用 - 只需传入一个工厂，切换平台方便
class FileProcessTool
{
  private:
    ISpliter *binarySpliter;
    ISpliter *txtSpliter;
    ISpliter *videoSpliter;

  public:
    void spilt(FileSpliterFactory *factory)
    {
        // 只需一个工厂参数，就能创建一整套产品
        binarySpliter = factory->createBinarySpliter();
        txtSpliter = factory->createTxtSpliter();
        videoSpliter = factory->createVideoSpliter();

        binarySpliter->split();
        txtSpliter->split();
        videoSpliter->split();
    }
};

void TestAbstractFactory()
{
    FileProcessTool tool;

    // 切换平台只需换一个工厂
    FileSpliterFactory *factory = new WindowsFactory();
    tool.spilt(factory);

    cout << "========== 切换到 Linux 平台 ==========" << endl;
    delete factory;
    factory = new LinuxFactory();
    tool.spilt(factory);

    cout << "========== 切换到 Mac 平台 ==========" << endl;
    delete factory;
    factory = new MacFactory();
    tool.spilt(factory);

    delete factory;

    /*
        抽象工厂优点：
        1. 类数量减少：3个平台 × 1个工厂 = 3 个工厂类
        2. 客户端只需一个工厂参数
        3. 切换平台只需换一个工厂，代码改动小
        4. 新增平台只需增加一个工厂类

        缺点：
        1. 抽象工厂虽然减少了工厂数量，但给工厂加了一层 "必须包含这几样东西" 的枷锁。
		2. 抽象工厂倾向于产品族（风格）的整体切换，但牺牲了增加新产品的灵活性。（增加新产品需要动每个系列（工厂）的代码）
    */
}


int main()
{

    return 0;
}