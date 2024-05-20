#include "Commands.h"

Commands::Commands()
{
	commands = nullptr;
	setCurrent_command(0);
	setCommands_size(0);
}

Commands::Commands(string* commandArray, unsigned size)
{
	setCurrent_command(0);
	setCommands_size(0);
	for (unsigned i = 0; i < size; i++)
	{
		setCommands(commandArray[i]);
	}
}

Commands::~Commands()
{
	delete[] commands;
}

unsigned Commands::Funcion_number_from_command(string receivedCommand)
{
	for (unsigned i = 0; i < getCommands_Size(); i++)
	{
		if (receivedCommand.compare(getCommand(i)))
		{
			return i;
		}
	}
	return -1;//throw unhandled expression
}

void Commands::setCommands(string command)
{
	if (command == "" || command == " " || command == "\n" || command == "\t")
	{
		return;
	}
	setCommands_size(getCommands_Size() + 1);
	string* str = new string[getCommands_Size()];
	for (unsigned i = 0; i < getCommands_Size() - 1; i++)
	{
		str[i] = getCommand(i);
	}
	delete[] commands;
	str[getCommands_Size() - 1] = command;
	commands = str;
}

unsigned Commands::getCurrent_command()
{
	return current_command;
}

unsigned Commands::getCommands_Size()
{
	return commands_size;
}

string Commands::getCommand()
{
	return commands[getCurrent_command()];
}

string Commands::getCommand(unsigned index)
{
	return commands[index];
}

void Commands::setCurrent_command(unsigned element)
{
	current_command = element;
}

void Commands::setCommands_size(unsigned size)
{
	commands_size = size;
}
