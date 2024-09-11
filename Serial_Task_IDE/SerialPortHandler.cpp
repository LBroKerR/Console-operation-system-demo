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
  Serial.print("Welcome in BIOS Menu system, where you can set your termostate device!\n\nTo interact with the menu just enter any commands from below!\n\n");
	Serial.print("Commands:\n\nmenu:\n\tset\n\thardreset\n\nset menu:\n\ttemp\n\tclock\n\twifimenu\n\nwifimenu:\n\tip\n\thost\n\tpass\n\tuser\n\twifi\n\ncommands anywhere:\n\tquit\n\tcancel\n\thelp\n\n");
	Serial.print("Menus can be work with only one command/menu.\n\n\t\tOr\n\nUse multiply command and data together, and use space between them.");
  Serial.print("For examle: \n\n\tset wifimenu wifi enable\n\n\t\tOr\n\n\tType one by one and hit enter after typed each command.\n\n");
  Serial.print("help: prints out the active menu commands.\n");
  Serial.print("cancel: returns to the main menu.\n");
  Serial.print("quit: exiting BIOS, and reseting the device!");
}
