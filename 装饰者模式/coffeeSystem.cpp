#include <iostream>
#include <string>
using namespace std;

/**********************************
需求：
购买咖啡时，也可以要求添加其他各种调料
例如： 蒸奶（steamed milk）, 豆浆(soy)
摩卡(mocha)...，咖啡店需要根据加入不同的
调料收取不同的费用。
      咖啡        ：    价钱
综合（houseBlend）:    0.89
浓缩 (espresso)   :    1.99

      配料       ：     价钱
牛奶 （milk）    :     0.10
摩卡 （mocha）   :     0.20
豆浆 （soy)      :     0.15
**********************************/


class Baverage //饮料类
{
public:
	Baverage(){ }
	virtual string getDescription()
	{
		return description;
	}

	virtual double cost() = 0;
	string description;
};

class HouseBlend : public Baverage
{
public:
	HouseBlend(){
		description = "House blend coffee";
	}

	double cost()
	{
		return 0.89;
	}
};

class Espresso : public Baverage
{
public:
	Espresso(){
		description = "Espresso coffee";
	}

	double cost()
	{
		return 1.99;
	}
};

/* 调料装饰者抽象类 */
class CondimentDecorator : public Baverage
{
public:
	virtual string getDescription() = 0;
};

class Mocha : public CondimentDecorator
{
public:
	Mocha(Baverage *beverage)
	{
		m_pBeverage = beverage;
	}

	string getDescription()
	{
		cout << "Mocha getDescription" << endl;
		return m_pBeverage->getDescription() + " , Mocha";
	}

	double cost()
	{
		cout << "Mocha cost" << endl;
		return m_pBeverage->cost() + 0.20;
	}

	Baverage *m_pBeverage;
};

class Soy : public CondimentDecorator
{
public:
	Soy(Baverage *beverage)
	{
		m_pBeverage = beverage;
	}

	string getDescription()
	{
		cout << "Soy getDescription" << endl;
		return m_pBeverage->getDescription() + " , Soy";
	}

	double cost()
	{
		cout << "Soy cost" << endl;
		return m_pBeverage->cost() + 0.15;
	}

	Baverage *m_pBeverage;
};

int main()
{
	Espresso espresso;
	Baverage *pBaverage = &espresso;
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;

	HouseBlend houseBlend;  //点一杯综合咖啡
	pBaverage = &houseBlend;
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;
	Mocha mocha(pBaverage); // 摩卡的综合咖啡 (装饰它)
	pBaverage = &mocha;
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;
	Soy soy(pBaverage);  //加点豆浆
	pBaverage = &soy;
	// 0.89 + 0.20 + 0.15 = 1.24
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;
	return 0;
}