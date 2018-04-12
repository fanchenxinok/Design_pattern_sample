#include <iostream>
#include <vector>
#include <list>
using namespace std;
/*******************************************************
ʵ������
Duck���࣬ϣ���̳�Duck���Ѽ�ӵ���Ϊ��������Ѽ�ӵĲ�ͬ����ͬ
********************************************************/
typedef enum
{
	FALSE = 0,
	TRUE = 1
}BOOL;

/* Ѽ�ӽе���Ϊ�ĸ��� */
class QuackBehavior
{
public:
	virtual void quack() = 0;
};

/* Ѽ�ӷɵ���Ϊ�ĸ��� */
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