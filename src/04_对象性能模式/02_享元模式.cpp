#include <iostream>
#include <string>
#include <unordered_map>

/*
    享元模式：运用共享技术有效支持大量细粒度对象（池化思想）
*/

// 业务场景，字体类，会频繁的使用，并且有多种字体
class Font
{
  private:
    std::string key;

  public:
    Font(std::string i_key)
    {
        key = i_key;
    }
};

// 享元模式：池化技术实现复用，避免频繁创建太多细粒度的对象
class FontPool
{
  private:
    std::unordered_map<std::string, Font *> fontpool;

  public:
    Font *GetFont(std::string key)
    {
        for (auto pair : fontpool) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        fontpool[key] = new Font(key);
        return fontpool[key];
    }
};

int main()
{
    return 0;
}