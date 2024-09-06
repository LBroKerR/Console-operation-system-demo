#pragma once

#include <iostream>
#include <string>
using namespace std;
class Commands
{
	string* commands;
	//unsigned current_command;
	unsigned commands_size;

public:

	Commands();
	Commands(string* commandArray, unsigned size);
	~Commands();
	bool Funcion_number_from_command(string receivedCommand, unsigned *index);
	void setCommands(string command);
	void setCommands(string* command, unsigned size);
	string getCommand(unsigned index);

private:

	unsigned getCommands_Size();

	void setCommands_size(unsigned size);
};

