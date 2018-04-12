#include <iostream>
#include <Windows.h> 
using namespace std;
/* 只能有一个实例 */

/* 方案1 */
class singleMode1
{
public:
	static singleMode1* getInstance()
	{
		WaitForSingleObject(hSemaphore,INFINITE);  
		if(pUqInstance == NULL){
			pUqInstance = new singleMode1();
		}
		ReleaseSemaphore(hSemaphore,1,NULL);      //释放信号量资源  
		return pUqInstance;
	}

	void introduceMe(){
		cout << "Hi I am singleMode1." << endl;
	}

private:
	singleMode1(){}
	static singleMode1 *pUqInstance;
	static HANDLE hSemaphore;
};

singleMode1* singleMode1::pUqInstance = NULL;
HANDLE singleMode1::hSemaphore=CreateSemaphore(NULL,1,1,NULL);      //创建信号量，初始为1，最多为1  


/* 方案2 */
class singleMode2
{
public:
	static singleMode2* getInstance()
	{  
		if(pUqInstance == NULL){
			WaitForSingleObject(hSemaphore,INFINITE);
			if(pUqInstance == NULL){
				pUqInstance = new singleMode2();
			}
			ReleaseSemaphore(hSemaphore,1,NULL);      //释放信号量资源  
		}
		return pUqInstance;
	}

	void introduceMe(){
		cout << "Hi I am singleMode2." << endl;
	}

private:
	singleMode2(){}
	static singleMode2 *pUqInstance;
	static HANDLE hSemaphore;
};

singleMode2* singleMode2::pUqInstance = NULL;
HANDLE singleMode2::hSemaphore=CreateSemaphore(NULL,1,1,NULL);      //创建信号量，初始为1，最多为1  

/* 方案3 */
class singleMode3
{
public:
	static singleMode3* getInstance()
	{  
		return pUqInstance;
	}

	void introduceMe(){
		cout << "Hi I am singleMode3." << endl;
	}

private:
	singleMode3(){}
	static singleMode3 *pUqInstance;
};

singleMode3* singleMode3::pUqInstance = new singleMode3();


int main()
{
	singleMode1 *pInstance1 = singleMode1::getInstance();
	pInstance1->introduceMe();
	delete pInstance1;

	singleMode2 *pInstance2 = singleMode2::getInstance();
	pInstance2->introduceMe();
	delete pInstance2;

	singleMode3 *pInstance3 = singleMode3::getInstance();
	pInstance3->introduceMe();
	delete pInstance3;
	return 0;
}