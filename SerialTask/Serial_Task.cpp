#include "Serial_Task.h"

MenuHandler* init(MenuHandler* head) {
	if (head != nullptr) {
		delete head;
	}
	head = new MenuHandler();
//	head->addFunctions("help", help);
	head->addFunctions("print", print);
	head->addFunctions("hardreset", hardreset);
	MenuHandler* setparams = new MenuHandler();
	setparams->addFunctions("temp", temp);
	setparams->addFunctions("clock", clock);
	MenuHandler* wifimenu= new MenuHandler();
	wifimenu->addFunctions("ip", ip);
	wifimenu->addFunctions("host", host);
	wifimenu->addFunctions("pass", pass);
	wifimenu->addFunctions("user", user);
	wifimenu->addFunctions("wifiswitch", Enable);
	setparams->addSideMenus("wifi", wifimenu);
	head->addSideMenus("set", setparams);
	return head;
}
bool system(MenuHandler *&head, SerialPortHandler *&IO) {
	string a = "";
	MenuHandler* tmp=nullptr;
	bool(*func)(void*) = nullptr;
	if (!IO->useStack(&a)) {
		IO->checkInput(a, "Input:");
		return true;
	}
	if (!head->menu(&a, tmp, &func)) {//quit
		return false;
	}
	if(tmp == nullptr && func == nullptr ) {//cancel
		if (a != "") {
			tmp = head;
			print((void*)&a);
		}
		else {
			head = tmp;
		}
		return true;
	}
	else if (func == nullptr) {//next menu
		head = tmp;
		return true;
	}
	else if (tmp == nullptr) {
		if (!IO->useStack(&a)) {
			if (!IO->getdata(&a)) {
				head = tmp;
			}
			func((void*)&a);
		}
	}
	return true;
}
void SerialTask(void* params) {
	MenuHandler* head = nullptr;
	MenuHandler* tmp = nullptr;
	SerialPortHandler* IO = new SerialPortHandler();
	head = init(head);
	tmp = head;
	while (true) {
		if (!system(head, IO)) {
			break;
		}
		if (head == nullptr) {
			head = tmp;
		}
	}
	if (head != nullptr) {
		delete head;
	}
	delete IO;
	//_CrtDumpMemoryLeaks();
	//vTaskDelete(NULL);
}