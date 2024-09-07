#pragma once
#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <Arduino.h>


class SerialPortHandler
{
	unsigned stackSize;
	String *stackData;

	void CalculateSize( String);
	void startpoints(String, unsigned*);
	void ConvertToStack(String); //string decodeCommand(string, unsigned*); //return data, and return path in paramlist 

public:
	SerialPortHandler();
	~SerialPortHandler();
	bool useStack(String*);
	void checkInput(String, String);
	bool getdata(String*);

	void prints(String);
	void printshelp();//data param)
};

#endif // SERIALPORTHANDLER_H
