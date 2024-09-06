#pragma once
#include "../menuhandler/MenuHandler.h"
#include "../SerialPortHandler/SerialPortHandler.h"
#include "MenuFunctions.h"
MenuHandler* init(MenuHandler* head);
bool system(MenuHandler *&head, SerialPortHandler *&IO);
void SerialTask(void* params);
