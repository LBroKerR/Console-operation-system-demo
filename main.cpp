// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SIZE 10
#include <iostream>
#define SET "set"
#define GET "get"
#define QUIT "quit"
#define ADD "add"
using namespace std;
#include "Commands.h"
bool func1(string param)
{
	return true;
}
bool func2(string param)
{
	return true;
}
bool func3(string param)
{
	return true;
}
bool ToFuncs(string param, string func)
{
	if (param.compare(func))
	{
		return false;
	}
	return true;
}
void menu(bool funcs)
{
	string input;
	unsigned i = 1;
	while (i != 0)
	{
		if ((bool)(cin >> input))
		{
			i = 0;
			while (true)
			{
				i += ToFuncs(input, QUIT);
				i += ToFuncs(input, SET);
				i += ToFuncs(input, GET);
				i += ToFuncs(input, ADD);
			}
		}
	}
}
int main()
{
	//bool (*allfuncs[3])(string);
	//allfuncs[0] = func1;
	//allfuncs[1] = func2;
	//allfuncs[2] = func3;
	//menu(allfuncs);
	string test[] = {"Start", "Stop", "End"};
	string input = "";
	Commands *engine1=new Commands(test,3);
	cin >> input;
	engine1->setCommands(input);
	do
	{
		cin >> input;
		if (engine1->Funcion_number_from_command(input))
		{
			cout << engine1->getCurrent_command();
		}

	} while (engine1->getCurrent_command()!=2);

	return 0;
}