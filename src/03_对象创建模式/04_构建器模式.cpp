#include <iostream>
#include <string>
using namespace std;
/*
    构建器模式：一句话概括（本质上是用于对象创建的 -> 模板方法）-> 演化后是 完善的构建器模式
*/

//====================================================
// House基类（模板方法模式）
class HouseBase
{
  public:
    virtual ~HouseBase() {}
    void Init()
    {
        buildStep1();

        for (int i = 0; i < 4; ++i) {
            buildStep2();
        }

        buildStep3();

        buildStep4();
    };
    virtual void buildStep1() = 0;
    virtual void buildStep2() = 0;
    virtual void buildStep3() = 0;
    virtual void buildStep4() = 0;
};

class StoneHouse : public HouseBase
{
  public:
    virtual void buildStep1() override
    {
        cout<<"石头房子第一步"<<endl;
    }

    virtual void buildStep2() override
    {
        cout<<"石头房子第二步"<<endl;
    }

    virtual void buildStep3() override
    {
        cout<<"石头房子第三步"<<endl;
    }

    virtual void buildStep4() override
    {
        cout<<"石头房子第四步"<<endl;
	}
};

class GlassHouse : public HouseBase
{
  public:
    virtual void buildStep1() override
    {
        cout<<"玻璃房子第一步"<<endl;
    }

    virtual void buildStep2() override
    {
        cout<<"玻璃房子第二步"<<endl;
    }

    virtual void buildStep3() override
    {
        cout<<"玻璃房子第三步"<<endl;
    }

    virtual void buildStep4() override
    {
        cout<<"玻璃房子第四步"<<endl;
	}
};

// 使用方式
void Process()
{
    StoneHouse stone;
    stone.Init();

    GlassHouse glass;
    glass.Init();
}

//====================================================
// 构建器模式实现
// 解决：分离复杂对象的构建与表示，支持多步骤构建

/*
    构建器模式适用场景：
    1. 对象创建复杂，需要多个步骤
    2. 创建算法独立于对象的组成部分
    3. 同一构建过程可以创建不同表示
*/

//====================================================
// 第一步：定义产品（复杂的房子）
class House
{
  private:
    string walls;    // 墙壁
    string doors;    // 门
    string windows;  // 窗户
    string roof;     // 屋顶

  public:
    void setWalls(string w) { walls = w; }
    void setDoors(string d) { doors = d; }
    void setWindows(string w) { windows = w; }
    void setRoof(string r) { roof = r; }

    void show()
    {
        cout << "建造的房子：" << endl;
        cout << "  墙壁：" << walls << endl;
        cout << "  门：" << doors << endl;
        cout << "  窗户：" << windows << endl;
        cout << "  屋顶：" << roof << endl;
    }
};

//====================================================
// 第二步：抽象构建者
class HouseBuilder
{
  protected:
    House *house;

  public:
    HouseBuilder() { house = new House(); }
    virtual ~HouseBuilder() { delete house; }

    House *getHouse() { return house; }

    virtual void buildWalls() = 0;
    virtual void buildDoors() = 0;
    virtual void buildWindows() = 0;
    virtual void buildRoof() = 0;
};

// 具体构建者：石头房子
class StoneHouseBuilder : public HouseBuilder
{
  public:
    virtual void buildWalls() override
    {
        house->setWalls("石墙");
    }
    virtual void buildDoors() override
    {
        house->setDoors("木门");
    }
    virtual void buildWindows() override
    {
        house->setWindows("普通窗户");
    }
    virtual void buildRoof() override
    {
        house->setRoof("瓦片屋顶");
    }
};

// 具体构建者：玻璃房子
class GlassHouseBuilder : public HouseBuilder
{
  public:
    virtual void buildWalls() override
    {
        house->setWalls("玻璃墙");
    }
    virtual void buildDoors() override
    {
        house->setDoors("自动玻璃门");
    }
    virtual void buildWindows() override
    {
        house->setWindows("落地玻璃窗");
    }
    virtual void buildRoof() override
    {
        house->setRoof("透明玻璃屋顶");
    }
};

//====================================================
// 第三步：指挥者 - 控制构建步骤
class HouseDirector
{
  private:
    HouseBuilder *builder;

  public:
    HouseDirector(HouseBuilder *b) : builder(b) {}

    void setBuilder(HouseBuilder *b) { builder = b; }

    House *construct()
    {
        // 按照固定步骤构建
        builder->buildWalls();
        builder->buildDoors();
        builder->buildWindows();
        builder->buildRoof();
        return builder->getHouse();
    }
};

//====================================================
// 使用方式
void TestBuilder()
{
    // 构建石头房子
    StoneHouseBuilder *stoneBuilder = new StoneHouseBuilder();
    HouseDirector director(stoneBuilder);
    House *stoneHouse = director.construct();
    stoneHouse->show();
    delete stoneHouse;
    delete stoneBuilder;

    cout << "========== 构建玻璃房子 ==========" << endl;

    // 构建玻璃房子 - 只需换构建器
    GlassHouseBuilder *glassBuilder = new GlassHouseBuilder();
    director.setBuilder(glassBuilder);
    House *glassHouse = director.construct();
    glassHouse->show();
    delete glassHouse;
    delete glassBuilder;

    /*
        构建器模式优点：
        1. 分离构建与表示：构建过程由Director控制，具体细节由Builder负责
        2. 步骤可控：可以在构建过程中添加额外步骤
        3. 易扩展：新增产品类型只需新增Builder
        4. 客户端与构建过程解耦
    */
}

int main()
{
    cout << "========== 模板方法模式 ==========" << endl;
    Process();

    cout << endl << "========== 构建器模式 ==========" << endl;
    TestBuilder();
    return 0;
}