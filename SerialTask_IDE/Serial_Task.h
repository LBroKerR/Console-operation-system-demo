#pragma once
#ifndef SERIAL_TASK_H
#define SERIAL_TASK_H

#include "MenuHandler.h"
#include "SerialPortHandler.h"
#include "MenuFunctions.h"
#include "Arduino.h"
MenuHandler* init(MenuHandler* head);
bool system(MenuHandler *&head, SerialPortHandler *&IO);
void SerialTask(void* params);

#endif // SERIAL_TASK_H
