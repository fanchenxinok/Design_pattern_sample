#include <iostream>
using namespace std;

class Command
{
public:
	virtual void excute() = 0;
	virtual void undo() = 0; //撤销操作
	int commandType; //命令类型 0: off; 1: on; 其他自行定义
};

/* 电灯开关相关类 */
class Light
{
public:
	void on(){
		cout << "Light is On" << endl;
	}

	void off(){
		cout << "Light is Off" << endl;
	}
};

class LightCommand : public Command
{
public:
	LightCommand(Light *pLight, int cmd)
	{
		commandType = cmd;
		pLight_m = pLight;
	}

	void excute()
	{
		if(pLight_m){
			switch(commandType){
			case 0:
				pLight_m->off();
				break;
			case 1:
				pLight_m->on();
				break;
			default:
				break;
			}
		}
	}

	void undo()
	{
		if(pLight_m){
			switch(commandType){
			case 0:
				pLight_m->on();
				break;
			case 1:
				pLight_m->off();
				break;
			default:
				break;
			}
		}
	}
private:
	Light *pLight_m;
};


/* 空调相关开关类 */
class AirConditioner
{
public:
	AirConditioner()
	{
		temperature = 25;
	}
	
	void RiseTemperature()
	{
		temperature++;
		cout << "Rise Temperature is " << temperature << " degree" << endl;
	}

	void ReduceTemperature()
	{
		temperature--;
		cout << "Reduce Temperature is " << temperature << " degree" << endl;
	}

	void Temperature()
	{
		temperature++;
		cout << "add Temperature is " << temperature << " degree" << endl;
	}

	void on()
	{
		cout << "air conditioner is on" << endl;
		cout << "current temperature is " << temperature << " degree" << endl;
	}

	void off()
	{
		cout << "air conditioner is off" << endl;
	}
private:
	int temperature;
};

class AirConditonerCommand : public Command
{
public:
	AirConditonerCommand(AirConditioner *pAirConditioner, int cmd)
	{
		commandType = cmd;
		pAirConditioner_m = pAirConditioner;
	}

	void excute()
	{
		if(pAirConditioner_m){
			switch(commandType){
			case 0:
				pAirConditioner_m->off();
				break;
			case 1:
				pAirConditioner_m->on();
				break;
			case 2:
				pAirConditioner_m->RiseTemperature();
				break;
			case 3:
				pAirConditioner_m->ReduceTemperature();
				break;
			default:
				break;
			}
		}
	}

	void undo()
	{
		if(pAirConditioner_m){
			switch(commandType){
			case 0:
				pAirConditioner_m->on();
				break;
			case 1:
				pAirConditioner_m->off();
				break;
			case 2:
				pAirConditioner_m->ReduceTemperature();
				break;
			case 3:
				pAirConditioner_m->RiseTemperature();
				break;
			default:
				break;
			}
		}
	}
private:
	AirConditioner *pAirConditioner_m;
};

/* 控制多个电器的命令 */
class MutilCtrlCommand : public Command
{
public:
	MutilCtrlCommand(Command **pCmds, int n)
	{
		m = n;
		pCommands = pCmds;
	}

	void excute()
	{
		if(pCommands){
			int i = 0;
			for(; i < m; i++){
				pCommands[i]->excute();
			}
		}
	}

	void undo()
	{
		if(pCommands){
			int i = m - 1;
			for(; i >= 0; i--){
				pCommands[i]->undo();
			}
		}
	}

private:
	Command **pCommands;
	int m;
};


class RemoteControl
{
public:
	RemoteControl()
	{
		int i = 0;
		for(; i < 10; i++){
			pOnCommands[i] = NULL;
			pOffCommands[i] = NULL;
			pUpCommands[i] = NULL;
			pDownCommands[i] = NULL;
		}
		pUndoCommand = NULL;
	}

	void setOnOffCommand(int slot, Command *pOnCmd, Command *pOffCmd)
	{
		if(slot >= 0 && slot < 10){
			pOnCommands[slot] = pOnCmd;
			pOffCommands[slot] = pOffCmd;
		}
	}

	void setUpDownCommand(int slot, Command *pUpCmd, Command *pDownCmd)
	{
		if(slot >= 0 && slot < 10){
			pUpCommands[slot] = pUpCmd;
			pDownCommands[slot] = pDownCmd;
		}
	}

	void OnButtonPushed(int slot)
	{
		if(pOnCommands[slot]){
			pOnCommands[slot]->excute();
			pUndoCommand = pOnCommands[slot];
		}
		else{
			cout << "No Ack" << endl;
		}
	}

	void OffButtonPushed(int slot)
	{
		if(pOffCommands[slot]){
			pOffCommands[slot]->excute();
			pUndoCommand = pOnCommands[slot];
		}
		else{
			cout << "No Ack" << endl;
		}
	}

	void UpButtonPushed(int slot)
	{
		if(pUpCommands[slot]){
			pUpCommands[slot]->excute();
			pUndoCommand = pUpCommands[slot];
		}
		else{
			cout << "No Ack" << endl;
		}
	}

	void DownButtonPushed(int slot)
	{
		if(pDownCommands[slot]){
			pDownCommands[slot]->excute();
			pUndoCommand = pDownCommands[slot];
		}
		else{
			cout << "No Ack" << endl;
		}
	}

	void UndoButtonPushed()
	{
		if(pUndoCommand){
			pUndoCommand->undo();
			pUndoCommand = NULL;
		}
		else{
			cout << "No Ack" << endl;
		}
	}
private:
	Command* pOnCommands[10];
	Command* pOffCommands[10];
	Command* pUpCommands[10];
	Command* pDownCommands[10];
	Command *pUndoCommand;
};

int main()
{
	RemoteControl remoteCtrl;

	Light light;
	LightCommand lightOffCtrl(&light, 0);
	LightCommand lightOnCtrl(&light, 1);
	remoteCtrl.setOnOffCommand(0, &lightOnCtrl, &lightOffCtrl);
	remoteCtrl.OnButtonPushed(0);
	remoteCtrl.UndoButtonPushed();
	remoteCtrl.OffButtonPushed(0);

	AirConditioner airConditioner;
	AirConditonerCommand airConditionerOffCtrl(&airConditioner, 0);
	AirConditonerCommand airConditionerOnCtrl(&airConditioner, 1);
	AirConditonerCommand airConditionerUpCtrl(&airConditioner, 2);
	AirConditonerCommand airConditionerDownCtrl(&airConditioner, 3);
	remoteCtrl.setOnOffCommand(1, &airConditionerOnCtrl, &airConditionerOffCtrl);
	remoteCtrl.setUpDownCommand(1, &airConditionerUpCtrl, &airConditionerDownCtrl);
	remoteCtrl.OnButtonPushed(1);
	remoteCtrl.OffButtonPushed(1);
	remoteCtrl.UpButtonPushed(1);
	remoteCtrl.DownButtonPushed(1);

	remoteCtrl.OnButtonPushed(2);
	remoteCtrl.OffButtonPushed(2);

	Command *OnCmds[2] = {NULL};
	OnCmds[0] = &lightOnCtrl;
	OnCmds[1] = &airConditionerOnCtrl;
	MutilCtrlCommand mutilOnCtrl(OnCmds, 2);
	remoteCtrl.setOnOffCommand(3, &mutilOnCtrl, NULL);
	remoteCtrl.OnButtonPushed(3);
	remoteCtrl.UndoButtonPushed();
	return 0;
}