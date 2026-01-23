#include <iostream>
using namespace std;

/*
// ========== 基本业务操作 ： 对各种主体流进一步 加密===========
// 业务操作：流 -基类
class Stream
{
  public:
    virtual void Read(int number) = 0;
    virtual void Seek(int position) = 0;
    virtual void Write(char data) = 0;

    virtual ~Stream(){};
};

// 主体类: 文件流
class FileStream : public Stream
{
  public:
    virtual void Read(int number) {
        // 读文件流
    };

    virtual void Seek(int position) {
        // 查文件流
    };

    virtual void Write(char data) {
        // 写文件流
    };
};

// 主体类：网络流
class NetworkStream : public Stream
{
  public:
    virtual void Read(int number) {
        // 读网络流
    };

    virtual void Seek(int position) {
        // 查网络流
    };

    virtual void Write(char data) {
        // 写网络流
    };
};

// 主体类：缓存流
class BufferStream : public Stream
{
  public:
    virtual void Read(int number) {
        // 读缓存流
    };

    virtual void Seek(int position) {
        // 查缓存流
    };

    virtual void Write(char data) {
        // 写缓存流
    };
};

// ========== 拓展操作 ： 对各种主体流进一步 加密===========

// 拓展类: 加密文件流
class CryptoFileStream : public FileStream
{
  public:
    virtual void Read(int number)
    {
        // 额外的加密操作
        FileStream::Read(number); // 读文件流
    };

    virtual void Seek(int position)
    {
        // 额外的加密操作
        FileStream::Seek(position); // 查文件流
    };

    virtual void Write(char data)
    {
        // 额外的加密操作
        FileStream::Write(data); // 写文件流
    };
};

// 拓展类: 加密网络流
class CryptoNetworkStream : public NetworkStream
{
  public:
    virtual void Read(int number)
    {
        // 额外的加密操作
        NetworkStream::Read(number); // 读网络流
    };

    virtual void Seek(int position)
    {
        // 额外的加密操作
        NetworkStream::Seek(position); // 查网络流
    };

    virtual void Write(char data)
    {
        // 额外的加密操作
        NetworkStream::Write(data); // 写网络流
    };
};

// 拓展类: 加密缓存流
class CryptoBufferStream : public BufferStream
{
  public:
    virtual void Read(int number)
    {
        // 额外的加密操作
        BufferStream::Read(number); // 读缓存流
    };

    virtual void Seek(int position)
    {
        // 额外的加密操作
        BufferStream::Seek(position); // 查缓存流
    };

    virtual void Write(char data)
    {
        // 额外的加密操作
        BufferStream::Write(data); // 写缓存流
    };
};

// ========== 拓展操作 ： 对各种主体流 加缓存 =========== ...... 就会出现更多的子类

// 利用继承进行功能的拓展明显是不合理的，不是一个好的模式 ---> 引出了策略模式
*/



int main()
{

    return 0;
}