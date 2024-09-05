// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MenuHandler.h"
#include "SerialPortHandler.h"
using namespace std;
void law(void* param) {
	string str = *(string*)param;
	cout << "The law is " << str <<"if im here." << endl;
}
void vonat(void* param) {
	string str = *(string*)param;
	cout << "The train new name is: " << str << endl;
}
void alma(void* param) {
	string str = *(string*)param;
	cout << "The apple funcs get the input: " << str << endl;
}
MenuHandler* init(MenuHandler* head) {
	head = new MenuHandler();
	MenuHandler* side = new MenuHandler();
	side->addFunctions("law", law);
	head->addSideMenus("setparams", side);
	head->addFunctions("apple", alma);
	head->addFunctions("train", vonat);
	return head;
}

void system(MenuHandler* head, SerialPortHandler* IO){
	string param="";
	MenuHandler* tmp = nullptr;
	MenuHandler* active = head;
	bool notquitting = true;
	void (*func)(void*) = nullptr;
	if (active != nullptr){
		do{
			IO->checkInput(param,"Input:?");
			if (IO->useStack(&param)) {
				notquitting = active->menu(&param, tmp, &func);
				param = "";
				if (tmp != nullptr && notquitting) {
					active = tmp;
					tmp = nullptr;
				}
				else if (func != nullptr && notquitting){
					IO->checkInput(param, "Input:?");
					if (IO->useStack(&param)){
						func((void*)&param);
					}
					func = nullptr;
				}
				else if ( notquitting) {
					active = head;
					tmp = nullptr;
				}
			}
		} while (!notquitting);
	}
}

int main() {
	MenuHandler *menusystem=nullptr;
	SerialPortHandler* IO = new SerialPortHandler();
	menusystem=init(menusystem);
	MenuHandler* tmp = nullptr;
	MenuHandler* tmp1 = nullptr;
	void (*func)(void*) = nullptr;
	string a = "setparams";
	string b = "law";
	string c = "done";
	if (menusystem->menu(&a, tmp, &func)) {
		if (tmp->menu(&b, tmp1, &func))
		{
			tmp1->print();
		}
	}
	delete menusystem;
	delete IO;
	_CrtDumpMemoryLeaks();
	return 0;
}