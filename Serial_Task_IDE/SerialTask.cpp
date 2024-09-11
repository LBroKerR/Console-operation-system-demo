#include "SerialTask.h"

SerialTask::SerialTask(){
  menu = nullptr;
  IO = new SerialPortHandler();
  init();
  incomingData="";
}
SerialTask::SerialTask(SerialPortHandler *param){
  menu = nullptr;
  IO = param;
  init();
  incomingData="";
}

SerialTask::~SerialTask(){
  	delete menu;
	  delete IO;
}

void SerialTask::init() {
	if (menu!= nullptr) {
		delete menu;
	}
	menu = new MenuHandler();
	menu->addFunctions("hardreset", Hardreset);
  menu->addFunctions("parameters", print);
	MenuHandler* setparams = new MenuHandler();
	setparams->addFunctions("temp", check_temp_datagramm);
	setparams->addFunctions("clock", check_clock_datagramm);
	MenuHandler* wifimenu= new MenuHandler();
	wifimenu->addFunctions("ip", check_IP_datagramm);
	wifimenu->addFunctions("host", check_host_datagramm);
	wifimenu->addFunctions("pass", check_pass_datagramm);
	wifimenu->addFunctions("user", check_user_datagramm);
	wifimenu->addFunctions("wifi", check_switch_datagramm);
	setparams->addSideMenus("wifimenu", wifimenu);
	menu->addSideMenus("set", setparams);
}

bool SerialTask::getCommand(){
  if (!IO->useStack(&incomingData)) {
    char ch[50]; 
    unsigned i = 0; 
    Serial.print("\n\rInput available:\n\r");
    while (i<49) {
      if(Serial.available()){
        ch[i] = (char)Serial.read();
        if(ch[i]!='\b'){
          Serial.print(ch[i]);
          if (ch[i] == '\n' || ch[i] == '\r') {
            ch[i] = '\0';
            incomingData = ch;
            IO->checkInput(incomingData, "");
            IO->useStack(&incomingData);
            return true;
          }
        i++;
        }
      }
    }
    return false;
  }
  return true;;
}

bool SerialTask::getData(String*str){
  if(!IO->useStack(str)){
    String tmp="";
      if(Serial.available()>0){
        if(IO->getdata(str)){
          return true;
        }
      }
      return false;
  }
  return true;
}

bool SerialTask::system(MenuHandler*&head) {
  incomingData="";
	MenuHandler* tmp=nullptr;
  bool(*tmpfunc)(void*) = nullptr;
  if(getCommand()){
    if (!head->menu(&incomingData, tmp, &tmpfunc)) {//quit
	    return false;
    }
	if (tmp == nullptr && tmpfunc == nullptr) {
		if (incomingData != "") {//function: help
			tmp = head;
			IO->prints(incomingData);
		}
		else {
			head = tmp; // cancel
		}
		return true;
	}
	else if (tmpfunc == nullptr) {//next menu
		head = tmp;
		return true;
	}
	else if (tmp == nullptr ) {
    if(head!=menu){
      while(!getData(&incomingData) && incomingData!="cancel" && incomingData!="quit" && incomingData!="help"){
        delay(1000);
      }
    }
		if(!tmpfunc((void*)&incomingData)){//do function with 'a' data
      //log error!
      IO->prints((incomingData+="error loged"));
    }
    else{
      IO->prints(incomingData+=" parameter saved");
    }
    head=tmp;
	}
  }
	return true;
}
void SerialTask::main() {
	MenuHandler* tmp = nullptr;
	tmp = menu;
  delay(2000);
  IO->printshelp();
	while (true) {
		if (!system(tmp)) {
			break;
		}
		if (tmp == nullptr) {
      tmp=menu;
		}
    //vTaskDelay(10 / portTICK_PERIOD_MS);
	}
	//_CrtDumpMemoryLeaks();
}