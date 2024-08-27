#include "EEPROMHandler.h"

/// <decodeCommand>
/// find the first space in the str text
/// separate the first section before the space, than check if its valid command
/// if valid second section of the original text will return, and the index of the command place in the command list.
/// if not, return an empty string.
/// <decodeCommand>

string EEPROMHandler::decodeCommand(string str, unsigned*index, Commands list)
{
	size_t pos = str.find(" ");
	string command = str.substr(0, pos);
	string others = str.substr(pos + 1);
	if (!list.Funcion_number_from_command(command, index))
	{
		return "";
	}
	return others;
}

void EEPROMHandler::checkInput(string* command, string print)
{
	if (*command == "")
	{
		prints(print);
		*command=Serial.readString();
	}
}

/// <UnderSideMenu>
/// decode the text witch comes from the serial port
/// than decide next way step based on the result of the search
/// if successfuly find move further, else go back to the mainMenü
/// </UnderSideMenu>
void EEPROMHandler::UnderSideMenu( string command)
{
	unsigned index = -1;
	checkInput(&command, "");
	command = decodeCommand(command, &index, UnderSideCommand);
	switch (index)
	{
	case 0:break; //ip
	case 1:break; //host
	case 2:break; //pass
	case 3:break; //user
	case 4:break; //enable
	default: // error log
	}
}

/// <setMenu>
/// decode the text witch comes from the serial port
/// than decide next way step based on the result of the search
/// if successfuly find move further, else go back to the mainMenü
/// </setMenu>
void EEPROMHandler::setMenu( string commands)
{
	unsigned index = -1;
	checkInput(&commands,"");
	commands = decodeCommand(commands, &index, sideCommand);
	switch (index)
	{
	case 0: break;//tmp
	case 1: break;//clock 
	case 2: UnderSideMenu(commands);
	default: // error log
	}
}

void EEPROMHandler::resetMenu(string command)
{
	unsigned index = -1;
	checkInput(&command, "");
	command = decodeCommand(command, &index, sideCommand);
	// to be continued...
}
/// <mainMenu>
/// decode the text witch comes from the serial port
/// than decide next way step based on the result of the search
/// reset board, after quiting eeprom menu
/// </mainMenu>
void EEPROMHandler::mainMenu()
{
	unsigned index = -1;
	string str = "";
	do
	{
		//cout << "EEPROM menu!" << endl << "Type help to get to know the menu rules!" << endl;
		checkInput(&str,"");
		str = decodeCommand(str, &index, mainCommands);
		switch (index)
		{
		case 0: setMenu(str); break;
		case 1: resetMenu(str); break; 
		case 3:  break; //hard reset
		case 4: prints(""); break; //help
		case 5: prints()//data params); break; //print changable eeprom datas
		default: //log error!
		}
	} while (index != 3);
	esp_restart();
}

void EEPROMHandler::prints(string param)
{
	Serial.println(param);
}

void EEPROMHandler::prints()//data param)
{
	Serial.println("data params");
}

EEPROMHandler::EEPROMHandler()
{
	//begin eeprom
	
}

EEPROMHandler::~EEPROMHandler()
{
	//end eeprom
}

void EEPROMHandler::AutoSave()//data object)
{
}
/// <checkSerial>
/// if text comming via serial insertation, the function will be check it
/// if the text is "BIOS", than return true, all task will be end, than eeprom menu will show in the serial monitor!
/// </checkSerial>
bool EEPROMHandler::checkSerial()
{
	if (Serial.avaible() > 0 )
	{
		string str = Serial.readString();
		if (str.compareTo("BIOS"))
		{
			return true;
		}
	}
	return false;
}
