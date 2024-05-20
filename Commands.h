#pragma once

#include <iostream>
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
	unsigned Funcion_number_from_command(string receivedCommand);
	void setCommands(string command);

private:

	unsigned getCurrent_command();
	unsigned getCommands_Size();
	string getCommand();
	string getCommand(unsigned index);

	void setCurrent_command(unsigned element);
	void setCommands_size(unsigned size);
};

