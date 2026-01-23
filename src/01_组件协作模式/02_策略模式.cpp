#include <iostream>
using namespace std;

/*
原始实现

enum taxCountry {
    cnTax = 1,
    deTax = 2,
    amTax = 3
};

int taxOrder(string countryName)
{
    if (countryName == "CN") {
        return cnTax * 10;
    } else if (countryName == "DE") {
        return deTax * 10;
    } else if (countryName == "AM") {
        return amTax * 10;
    }
    // 假设又来了新的国家的税需要计算，那么就会在后面加，这一块就要重新编译，复用性太差。
    // 并且这样的写法违背了开闭原则。（正确的应该是对拓展开放，对修改封闭），这里没有对修改封闭
    return 0;
}

*/

// 策略模式

class BaseTax
{
  public:
    virtual int CalculateTax() = 0;
    virtual ~BaseTax(){};
};

class CNTax : public BaseTax
{
    virtual int CalculateTax() override
    {
        return 1 * 10;
    }
};

class DETax : public BaseTax
{
    virtual int CalculateTax() override
    {
        return 1 * 10;
    }
};

class AMTax : public BaseTax
{
    virtual int CalculateTax() override
    {
        return 1 * 10;
    }
};
// 一般而言这些类都是放在不同的文件，新增国家计税，只需要继承这个类然后重写CalcuLateTax函数即可，其他文件中类可以二进制复用

// 策略中心
class TaxOrder
{
  private:
    BaseTax *strategy = nullptr;

  public:
    int TaxOrderFunc(string countryName) //一般策略模式的策略中心的对象的创建，会用工厂模式给替代，这里为了纯粹的演示策略模式本身，不用工厂
    {
        if (countryName == "CN") {
            strategy = new CNTax();
        } else if (countryName == "DE") {
            strategy = new DETax();
        }
        else if (countryName == "AM") {
			strategy = new AMTax();
        }

        return strategy->CalculateTax();
    }
};

int main()
{

    TaxOrder center;
    int tax = center.TaxOrderFunc("CN");
    cout<<tax<<endl;
    return 0;
}