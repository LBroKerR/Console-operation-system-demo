#pragma once

#include "../menuhandler/CommandHandler/Commands.h"
#include "../menuhandler/FunctionHandler/Functions.h"

 #define ERROR		 0		 
 #define MENU		 1		
 #define FUNC		 2	

 #define CANCEL		 3
 #define QUIT		 4
 #define HELP		 5

class MenuHandler
{
	Commands *MenuCommands, *FunctionCommands;
	MenuHandler** SideMenu;
	Functions* funcs;// object to handle via function pointer

	unsigned Menus_Elems;
	unsigned Funcs_Elems;

public:
	MenuHandler();
	MenuHandler(string*, unsigned, string*, unsigned);
	~MenuHandler();

	bool menu(string*, MenuHandler *&menu, bool (**func)(void*));

	bool addSideMenus(string CallName, MenuHandler*);
	bool addFunctions(string CallName, bool (*func)(void*));
	string print();
private:

	int decodeCommand(string, int*); //return data, and return path in paramlist // *
};

