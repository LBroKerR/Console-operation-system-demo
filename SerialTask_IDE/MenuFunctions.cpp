#include "MenuFunctions.h"

// delete all the data from eeprom
bool hardreset(void* param) {
	if (param != nullptr) {
		return false;
	}
	//...
		Serial.println("hardreset");
	return true;
}
// prints menu architecture and navigation hints
bool help(void* param) {
	String str = *(String*)param;
	Serial.println("help"+str);
	return true;
}
//prints anything what it get
bool print(void* param) {
	String str = *(String*)param;
	Serial.println(str);
	return true;
}
// overwrite offset temp data in eeprom
bool temp(void* param) {
	if (param == nullptr) {
		return false;
	}
	double tmp = *(double*)param;
	//...
	Serial.println("temperature");
	return true;
}
// overwrite clock datas in eeprom
bool clock(void* param) {
	if (param == nullptr) {
		return false;
	}
	unsigned tmp = *(unsigned*)param;
	//...
	Serial.println("clock hour min");
	return true;
}
// overwrite ip data in eeprom
bool ip(void* param) {
	if (param == nullptr) {
		return false;
	}
	char* tmp = (char*)param;
	//...
	Serial.println("ip address");
	return true;
}
// overwrite host data in eeprom
bool host(void* param) {
	if (param == nullptr) {
		return false;
	}
	unsigned tmp = *(unsigned*)param;
	//...
	Serial.println("server host");
	return true;
}
// overwrite password data in eeprom
bool pass(void* param) {
	if (param == nullptr) {
		return false;
	}
	char* tmp = (char*)param;
	//...
	Serial.println("wifi pass");
	return true;
}
// overwrite username data in eeprom
bool user(void* param) {
	if (param == nullptr) {
		return false;
	}
	char* tmp = (char*)param;
	//...
	Serial.println("wifi username");
	return true;
}
// overwrite the boolen data which is enable to start wifi task in eeprom
bool Enable(void* param) {
	if (param == nullptr) {
		return false;
	}
	bool tmp = *(bool*)param;
	//...
	Serial.println("is wifi enable?");
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



