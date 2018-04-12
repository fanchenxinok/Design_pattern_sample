#include <iostream>
#include <string>
using namespace std;

/**********************************
����
���򿧷�ʱ��Ҳ����Ҫ������������ֵ���
���磺 ���̣�steamed milk��, ����(soy)
Ħ��(mocha)...�����ȵ���Ҫ���ݼ��벻ͬ��
������ȡ��ͬ�ķ��á�
      ����        ��    ��Ǯ
�ۺϣ�houseBlend��:    0.89
Ũ�� (espresso)   :    1.99

      ����       ��     ��Ǯ
ţ�� ��milk��    :     0.10
Ħ�� ��mocha��   :     0.20
���� ��soy)      :     0.15
**********************************/


class Baverage //������
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

/* ����װ���߳����� */
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

	HouseBlend houseBlend;  //��һ���ۺϿ���
	pBaverage = &houseBlend;
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;
	Mocha mocha(pBaverage); // Ħ�����ۺϿ��� (װ����)
	pBaverage = &mocha;
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;
	Soy soy(pBaverage);  //�ӵ㶹��
	pBaverage = &soy;
	// 0.89 + 0.20 + 0.15 = 1.24
	cout << pBaverage->getDescription() << " $" << pBaverage->cost() << endl;
	return 0;
}