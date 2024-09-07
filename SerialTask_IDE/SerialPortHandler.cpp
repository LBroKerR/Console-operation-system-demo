#include "SerialPortHandler.h"
//  calculate the number of words in str
void SerialPortHandler::CalculateSize(String str) {
	unsigned size = str.length();
	char tmp;
	bool word = true;
	for (unsigned i = 0; i < size; i++){
		tmp = str[i];
		if (tmp != ' ' && tmp != '\t' && tmp != '\n') {
			if (word) {
				stackSize++;
				word = false;
			}
		}
		else {
			word = true;
		}
	}
}
// searching the first letters of the words in the string
void SerialPortHandler::startpoints(String str, unsigned* entris){
	char tmp=' ';
	bool entry = true; 
	unsigned pos = 0;
	for (unsigned index = 0; index < stackSize; index++){
		for (unsigned i = pos; i < str.length(); i++) {
			tmp = str[i];
			if (tmp != ' ' && tmp != '\t' && tmp != '\n') {
				if (entry) {
					entris[index] = i;
					entry = false;
				}
			}
			else if(!entry){
				pos = i;
				entry = true; break;
			}

		}
	}
}

// place every word in a string, and collect them in a dynamic array
void SerialPortHandler::ConvertToStack(String str) {
	char tmp = ' ';
	unsigned startPoints[5];//stackSize];
	CalculateSize(str);
	startpoints(str, startPoints);
	stackData = new String[stackSize];
	for (unsigned index = 0; index < stackSize; index++) {
		for (unsigned i = startPoints[index]; i< str.length(); i++){
			tmp = str[i];
			if (tmp != ' ' && tmp != '\t' && tmp != '\n') {
				stackData[index] += tmp;
			}
			else {
				break;
			}
		}
	}
}

SerialPortHandler::SerialPortHandler(){
	stackData = nullptr;
	stackSize = 0;
}

SerialPortHandler::~SerialPortHandler(){
	delete[] stackData;
	stackData = nullptr;
}

// pop out the first string from the array, return it, and save the others
bool SerialPortHandler::useStack(String* param) {
	if (stackData == nullptr || stackSize == 0) {
		delete[] stackData;
		stackData = nullptr;
		*param = "";
		return false;
	}
	String str = *stackData;
	String* tmp=nullptr;
	if (stackSize - 1 > 0 ) {
		tmp = new String[stackSize - 1];
		for (unsigned i = 1; i < stackSize; i++) {
			tmp[i-1] = stackData[i];
		}
	}
	delete[] stackData;
	stackData = tmp;
	stackSize--;
	*param = str;
	return true;
}

// Waiting input if needed, and print out the needed text
void SerialPortHandler::checkInput(String command, String print) {
	if (command == "") {
      command=Serial.readString();
      prints(print);
     prints(command);
		//cin >> command;
	}
	ConvertToStack(command);
}

bool SerialPortHandler::getdata(String* param)
{
	if (stackData != nullptr) {
		return false;
	}
	checkInput(*param, "Data input :");
	if (stackSize > 1){
		delete stackData;
		stackSize = 0;
		return false;
	}
	if (useStack(param)) {
		if ( *param != "cancel" ) {
			return true;
		}
	}
	return false;
}

// print up coming text
void SerialPortHandler::prints(String param){
	 Serial.println(param);
}
// print out the commands, and how the menu system is work.
void SerialPortHandler::printshelp(){
	//Serial.println("data params");
	 //cout<< "commands:\n\nmenu:\n\tsetparams\n\thardreset\n\thelp\n\nsetparams menu:\n\ttemp\n\tclock\n\twifimenu\n\nwifimenu:\n\tip\n\thost\n\tpass\n\tuser\n\tswitch\n"<<endl;
	 //cout<<"Menus work with only one command/menu.\n\n Or \n\nUse multiply command and data together, but use space between the commands."<<endl;
}
