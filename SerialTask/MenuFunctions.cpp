#include "MenuFunctions.h"

// delete all the data from eeprom
bool hardreset(void* param) {
	if (param != nullptr) {
		return false;
	}
	//...
	cout << "hardreset"<<endl;
	return true;
}
// prints menu architecture and navigation hints
bool help(void* param) {
	string str = *(string*)param;
	cout << "help" << endl;
	return true;
}
//prints anything what it get
bool print(void* param) {
	string str = *(string*)param;
	cout << str << endl;
	return true;
}
// overwrite offset temp data in eeprom
bool temp(void* param) {
	if (param == nullptr) {
		return false;
	}
	double tmp = *(double*)param;
	//...
	cout << "temp" << endl;
	return true;
}
// overwrite clock datas in eeprom
bool clock(void* param) {
	if (param == nullptr) {
		return false;
	}
	unsigned tmp = *(unsigned*)param;
	//...
	cout << "clock" << endl;
	return true;
}
// overwrite ip data in eeprom
bool ip(void* param) {
	if (param == nullptr) {
		return false;
	}
	char* tmp = (char*)param;
	//...
	cout << "ip" << endl;
	return true;
}
// overwrite host data in eeprom
bool host(void* param) {
	if (param == nullptr) {
		return false;
	}
	unsigned tmp = *(unsigned*)param;
	//...
	cout << "host" << endl;
	return true;
}
// overwrite password data in eeprom
bool pass(void* param) {
	if (param == nullptr) {
		return false;
	}
	char* tmp = (char*)param;
	//...
	cout << "pass" << endl;
	return true;
}
// overwrite username data in eeprom
bool user(void* param) {
	if (param == nullptr) {
		return false;
	}
	char* tmp = (char*)param;
	//...
	cout << "user" << endl;
	return true;
}
// overwrite the boolen data which is enable to start wifi task in eeprom
bool Enable(void* param) {
	if (param == nullptr) {
		return false;
	}
	bool tmp = *(bool*)param;
	//...
	cout << "switch" << endl;
	return true;
}

void ActiveProg(void* param){
	if (param == nullptr) {
		return;
	}
	unsigned tmp = *(unsigned*)param;
	//...
}

void programs(double* array, unsigned size){

}



