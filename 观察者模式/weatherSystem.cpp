#include <iostream>
#include <vector>
#include <list>
using namespace std;
/*******************************************************
实现需求：
WeatherData 类负责收集天气数据，当有数据更新通知报告
板更新数据，布告板可以有多个，可以创建也可以删除。
********************************************************/
typedef enum
{
	FALSE = 0,
	TRUE = 1
}BOOL;

class Subject;

/* 观察者类 */
class Observer
{
public:
	virtual void update(Subject *pSbj) = 0;
};

/* 显示类 */
class Display
{
public:
	virtual void display() = 0;
};

/* 主题类 */
class Subject
{
public:
	virtual void registerObserver(Observer *pObs) = 0; //注册观察者
	virtual void removeObserver(Observer *pObs) = 0; //删除观察着
	virtual void notifyObservers() = 0;
};

/* 天气数据类 */
class WeatherData : public Subject
{
public:
	WeatherData() { }
	~WeatherData() { }
	void registerObserver(Observer *pObs);
	void removeObserver(Observer *pObs);
	void notifyObservers();
	void setChange(); 
	void measurementsChanged();
	void setMeasurements(float temperature, float humidity, float pressure);

	const float getTemperature() { return temperature; }
	const float getHumidity() { return humidity; }
	const float getPressure() { return pressure; }
private:
	list<Observer*> observers;
	float temperature;
	float humidity;
	float pressure;
	BOOL  needChange;
};

void WeatherData::registerObserver(Observer *pObs)
{
	observers.push_back(pObs);
	return;
}

void WeatherData::removeObserver(Observer *pObs)
{
	observers.remove(pObs);
	return;
}

void WeatherData::notifyObservers()
{
	if(needChange == TRUE){
		list<Observer*>::iterator it = observers.begin();
		for(; it != observers.end(); it++){
			if(*it != NULL){
				Observer* pObs = (Observer*)(*it);
				pObs->update(this);
			}
		}
		needChange = FALSE;
	}
}

void WeatherData::setChange()
{
	needChange = TRUE;
}

void WeatherData::measurementsChanged()
{
	notifyObservers();
}

void WeatherData::setMeasurements(float temperature, float humidity, float pressure)
{
	this->temperature = temperature;
	this->humidity = humidity;
	this->pressure = pressure;
	measurementsChanged();
}

/* 当前状况布告板 */
class CurConditionDisplay : public Observer, Display
{
public:
	CurConditionDisplay(Subject *pSj)
	{
		this->m_pSj = pSj;
	}
	~CurConditionDisplay(){}
	void update(Subject *pSj);
	void unUpdate();
	void display();
private:
	float temperature;
	float humidity;
	Subject *m_pSj;
};

void CurConditionDisplay::update(Subject *pSj)
{
	if(pSj != NULL){
		WeatherData *pWeatherData = (WeatherData*)pSj;
		this->temperature = pWeatherData->getTemperature();
		this->humidity = pWeatherData->getHumidity();
		display();
	}
	else if(m_pSj != NULL){
		WeatherData *pWeatherData = (WeatherData*)m_pSj;
		this->temperature = pWeatherData->getTemperature();
		this->humidity = pWeatherData->getHumidity();
		display();	
	}
	return;
}

void CurConditionDisplay::unUpdate()
{
	if(!m_pSj) return;
	m_pSj->removeObserver(this);
}

void CurConditionDisplay::display()
{
	cout << "Current temperature: " << temperature << " degrees." << endl; 
	cout << "Current humidity: " << humidity << "." << endl; 
}

int main()
{
	WeatherData weatherCenter;
	CurConditionDisplay curConditionDisplay(&weatherCenter);
	weatherCenter.registerObserver(&curConditionDisplay);

	//curConditionDisplay.unUpdate();
	weatherCenter.setChange();
	weatherCenter.setMeasurements(30.5, 40.2, 15);
	weatherCenter.setChange();
	weatherCenter.setMeasurements(24.5, 33.66, 45);
	weatherCenter.setChange();
	weatherCenter.setMeasurements(54.23, 40.25, 75);
	return 0;
}