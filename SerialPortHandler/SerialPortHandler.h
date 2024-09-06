#pragma once

#include <iostream>

using namespace std;

class SerialPortHandler
{
	unsigned stackSize;
	string *stackData;

	void CalculateSize( string);
	void startpoints(string, unsigned*);
	void ConvertToStack(string); //string decodeCommand(string, unsigned*); //return data, and return path in paramlist 

public:
	SerialPortHandler();
	~SerialPortHandler();
	bool useStack(string*);
	void checkInput(string, string);
	bool getdata(string*);

	void prints(string);
	void printshelp();//data param)
};

