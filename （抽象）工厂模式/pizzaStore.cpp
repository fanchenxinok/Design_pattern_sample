#include <iostream>
#include <string>
using namespace std;

/* 原料：面粉 */
class Flour
{
public:
	string getFlourName(){
		return name;
	}
	virtual void setFlourName() = 0;
	string name;
};

//白面粉
class WhiteFlour : public Flour
{
public:
	WhiteFlour(){
		setFlourName();
	}
	void setFlourName(){
		name = "white flour";
	}
};

//黄面粉
class YellowFlour : public Flour
{
public:
	YellowFlour(){
		setFlourName();
	}
	void setFlourName(){
		name = "yellow flour";
	}
};

/* 原料：蔬菜 */
class Vegetable
{
public:
	string getVegetableName(){
		return name;
	}
	virtual void setVegetableName() = 0;
	string name;
};

//土豆
class PotatoVegetable : public Vegetable
{
public:
	PotatoVegetable()
	{
		setVegetableName();
	}
	void setVegetableName(){
		name = "potato";
	}
};

//洋葱
class OnionVegetable : public Vegetable
{
public:
	OnionVegetable()
	{
		setVegetableName();
	}
	void setVegetableName(){
		name = "onion";
	}
};

/* 制作pizza的原料工厂 */
class IngredientFactory
{
public:
	virtual Flour* prepareFlour() = 0;
	virtual Vegetable* prepareVegetable() = 0;
};

/* 上海原料厂 */
class SHIngredientFactory : public IngredientFactory
{
public:
	Flour* prepareFlour(){
		return new WhiteFlour();
	}

	Vegetable* prepareVegetable()
	{
		return new PotatoVegetable();
	}
};

/* 北京原料厂 */
class BJIngredientFactory : public IngredientFactory
{
public:
	Flour* prepareFlour(){
		return new YellowFlour();
	}

	Vegetable* prepareVegetable()
	{
		return new OnionVegetable();
	}
};

class Pizza
{
public:
	virtual ~Pizza()
	{
		//cout << "~Pizza() call!!!!" << endl;
		if(pIngredientFactory){
			delete pIngredientFactory;
			pIngredientFactory = NULL;
		}

		if(pFlour){
			delete pFlour;
			pFlour = NULL;
		}

		if(pVegetable){
			delete pVegetable;
			pVegetable = NULL;
		}
	}
	/* 准备原料需要从原料工厂预定 */
	void prepare()
	{
		if(pIngredientFactory){
			cout << pizzaName() << " preparing...." << endl;
			cout << "need ingredients as: " << endl;
			pFlour = pIngredientFactory->prepareFlour();
			cout << pFlour->getFlourName() << "; ";
			pVegetable = pIngredientFactory->prepareVegetable();
			cout << pVegetable->getVegetableName() << endl;
		}
	}

	void bake(){
		cout <<  pizzaName() << " Pizza baking...." << endl;
	}

	void cut(){
		cout <<  pizzaName() << " Pizza cuting..." << endl;
	}

	void box()
	{
		cout <<  pizzaName() << " Pizza boxing...." << endl;
	}
	virtual const string pizzaName()
	{
		string name = "Normal";
		return name;
	}

	IngredientFactory *pIngredientFactory;
	Flour *pFlour;
	Vegetable *pVegetable;
};

/* pizza 工厂 */
class PizzaStore
{
public:
	Pizza* orderPizza(string type);
	virtual Pizza* createPizza(string type) = 0;
};

Pizza* PizzaStore::orderPizza(string type)
{
	Pizza *pizza;
	pizza = createPizza(type);
	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();
	return pizza;
}

typedef enum{
	CH_BACON_PZ,
	CH_SUASAGE_PZ
}enChPzType;

//创建不同风味的pizza
//中国培根pizza
class ChineseBaconPizza : public Pizza
{
public:
	ChineseBaconPizza(IngredientFactory *pIF){
		pIngredientFactory = pIF;
	}

	const string pizzaName()
	{
		string name = "Chinese Bacon";
		return name;
	}
};

//中国香肠pizza
class ChineseSuasagePizza : public Pizza
{
public:
	ChineseSuasagePizza(IngredientFactory *pIF){
		pIngredientFactory = pIF;
	}

	const string pizzaName()
	{
		string name = "Chinese Suasage";
		return name;
	}
};

class ChinesePizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(string type);
};

Pizza* ChinesePizzaStore::createPizza(string type)
{
	if(type == "bacon"){
		IngredientFactory *pShIngFac = new SHIngredientFactory;
		return new ChineseBaconPizza(pShIngFac);
	}
	else if(type == "suasage"){
		IngredientFactory *pBjIngFac = new BJIngredientFactory;
		return new ChineseSuasagePizza(pBjIngFac);
	}
	else{
		return NULL;
	}
}

int main()
{
	ChinesePizzaStore chinesePizzaStore;
	Pizza *pz = chinesePizzaStore.orderPizza("bacon");
	cout << pz->pizzaName() << " pizza finish!!" << endl;
	delete pz;
	pz = NULL;
	pz = chinesePizzaStore.orderPizza("suasage");
	cout << pz->pizzaName() << " pizza finish!!" << endl;
	delete pz;
	return 0;
}