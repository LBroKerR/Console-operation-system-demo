#pragma once

#include <iostream>
#include <string>
using namespace std;
class Commands
{
	string* commands;
	unsigned current_command;
	unsigned commands_size;

public:

	Commands();
	Commands(string* commandArray, unsigned size);
	~Commands();
	bool Funcion_number_from_command(string receivedCommand);
	void setCommands(string command);
	unsigned getCurrent_command();

private:

	unsigned getCommands_Size();
	string getCommand();
	string getCommand(unsigned index);

	void setCurrent_command(unsigned element);
	void setCommands_size(unsigned size);
};

