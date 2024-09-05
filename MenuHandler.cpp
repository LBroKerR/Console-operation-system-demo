#include "MenuHandler.h"


MenuHandler::MenuHandler() {
	MenuCommands = new Commands();
	FunctionCommands = new Commands();
	SideMenu = nullptr;
	funcs = nullptr;
	Menus_Elems=0;
	Funcs_Elems=0;
}


MenuHandler::MenuHandler(string* param1, unsigned size1, string* param2, unsigned size2) {
	MenuCommands = new Commands(param1, size1);
	FunctionCommands = new Commands(param2, size2);
	SideMenu = nullptr;
	funcs = nullptr;
	Menus_Elems = size1;
	Funcs_Elems = size2;
}


MenuHandler::~MenuHandler(){
	if (MenuCommands != nullptr) {
		delete MenuCommands;
		MenuCommands = nullptr;
	}
	if (FunctionCommands != nullptr) {
		delete FunctionCommands;
		FunctionCommands = nullptr;
	}
	if (funcs != nullptr){
		delete[] funcs;
		funcs = nullptr;
	}
	if (SideMenu != nullptr) {
		for (unsigned i = 0; i < Menus_Elems; i++) {
			delete SideMenu[i];
		}
		delete[] SideMenu;
	}
}

/// <decodeCommand>
/// find the first space in the str text
/// separate the first section before the space, than check if its valid command
/// if valid second section of the original text will return, and the index of the command place in the command list.
/// if not, return an empty string.
/// <decodeCommand>

/*string MenuHandler::decodeCommand(string str, int* index) {
	string others, first;
	size_t pos = str.find(" ");
	if (pos != string::npos) {
		first = str.substr(0, pos);
		others = str.substr(pos + 1);
		str = others;
	}
	else {
		first = str;
		str = "";
	}
	if (!this->commands->Funcion_number_from_command(first, (unsigned*)index)) {
		*index = -1;
	}
	return str;
}*/
int MenuHandler::decodeCommand(string str, int* index) {
	if(MenuCommands->Funcion_number_from_command(str,(unsigned*)index)){
		return MENU;
	}
	else if (FunctionCommands->Funcion_number_from_command(str, (unsigned*)index)) {
		return FUNC;
	}
	else if (str == "cancel") {
		return CANCEL;
	}
	else if (str == "quit") {
		return QUIT;
	}
	return ERROR;
}
/// <menu>
/// check param if its a command or not
/// if nextmenu command-> call it, menus stored in dynamic pointers
/// if function command then call it, function stored in function pointers
/// call with 1 word and with 2 nullptr
/// will be prev if both param still be nullptr at the end
/// will be quit if 
/// </menu>
bool MenuHandler::menu(string *str, MenuHandler *menu, void (**func)(void*)) {
	if (str == nullptr ){
		return true;
	}
	int command = -1;
	switch (decodeCommand(*str, &command)) {
	case MENU: menu = SideMenu[command];break;//
	case FUNC: *func = funcs[command].getFunc(); break;//virtual functions array!!! 
	case CANCEL: return true;
	case QUIT: return false;
	default:cout << "incorrect command!"; //log error
	}
	return true;
}
/// <addSideMenus>
/// add menu to the end of the exist menu array, or create 1 for the first one. and add it command to the end of the commands array
/// </addSideMenus>

bool MenuHandler::addSideMenus(string CallName, MenuHandler* sidemenus){
	if (CallName == "" || CallName == " " || CallName == "\t"){
		return false;
	}
	MenuHandler** tmp = new MenuHandler*[Menus_Elems + 1];
	if (SideMenu != nullptr && Menus_Elems > 0){
		for (unsigned i = 0; i < Menus_Elems; i++){
			tmp[i] = SideMenu[i];
		}
		delete[] SideMenu;
	}
	tmp[Menus_Elems] = sidemenus;
	SideMenu = tmp;
	Menus_Elems++;
	MenuCommands->setCommands(CallName);
	return true;
}
/// <addFunctions>
/// same as addSideMenus, just with function 
/// </addFunctions>
bool MenuHandler::addFunctions(string CallName, void(*func)(void*))
{
	if (CallName == "" || CallName == " " || CallName == "\t") {
		return false;
	}
	Functions* tmp = new Functions[Funcs_Elems + 1];
	if (func != nullptr && Funcs_Elems>0){
		for (unsigned i = 0; i < Funcs_Elems; i++) {
			tmp[i] = funcs[i];
		}
		delete[] funcs;
	}
	tmp[Funcs_Elems].setFunc(func);
	FunctionCommands->setCommands(CallName);
	funcs = tmp;
	Funcs_Elems++;
	return true;
}
