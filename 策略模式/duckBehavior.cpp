#include <iostream>
#include <vector>
#include <list>
using namespace std;
/*******************************************************
实现需求：
Duck父类，希望继承Duck类的鸭子的行为可以随着鸭子的不同而不同
********************************************************/
typedef enum
{
	FALSE = 0,
	TRUE = 1
}BOOL;

/* 鸭子叫的行为的父类 */
class QuackBehavior
{
public:
	virtual void quack() = 0;
};

/* 鸭子飞的行为的父类 */
class FlyBehavior
{
public:
	virtual void fly() = 0;
};

class Duck
{
public:
	Duck()
	{
		pQuackBehavior = NULL;
		pFlyBehavior = NULL;
	}
	~Duck(){}

	void setQuackBehavior(QuackBehavior *pQuack)
	{
		pQuackBehavior = pQuack;
	}

	void setFlyBehavior(FlyBehavior *pFly)
	{
		pFlyBehavior = pFly;
	}

	void performQuack()
	{
		if(pQuackBehavior){
			pQuackBehavior->quack();
		}
	}

	void performFly()
	{
		if(pFlyBehavior){
			pFlyBehavior->fly();
		}
	}

	QuackBehavior *pQuackBehavior;
	FlyBehavior *pFlyBehavior;
};

class QuackType1 : public QuackBehavior
{
public:
	void quack()
	{
		cout << "ga ga ga..." << endl;
	}
};

class QuackType2 : public QuackBehavior
{
public:
	void quack()
	{
		cout << "gua gua gua..." << endl;
	}
};

class farmDuck : public Duck
{
public:
	void swim()
	{
		cout << "farm duck is swiming..." << endl;
	}
};

int main()
{
	farmDuck farm_duck;
	QuackType1 quackType1;
	farm_duck.setQuackBehavior(&quackType1);
	farm_duck.performQuack();
	return 0;
}