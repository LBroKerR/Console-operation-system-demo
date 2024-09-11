#pragma once
#ifndef SERIALTASK_H
#define SERIALTASK_H

#include "Arduino.h"

#include "MenuHandler.h"
#include "SerialPortHandler.h"
#include "EEPROMhandler.h"


class SerialTask{

  MenuHandler* menu;
  SerialPortHandler*IO;
  String incomingData; 

  void init();
  bool system(MenuHandler*&);
  bool getCommand();
  bool getData(String*);

public:
  SerialTask();
  SerialTask(SerialPortHandler *param);
  ~SerialTask();


  void main();
};

#endif // SERIALTASK_H
