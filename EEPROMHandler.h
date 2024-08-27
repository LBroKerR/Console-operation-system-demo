#pragma once

/// <basics>
///  carefully choosing the EEPROM size and minimalizing write operations, you can effectively use the emulated EEPROM for storing persistent data on the ESP32.
/// ESP32 do not has EEPROM directly, it is emulated in flash memory.
/// Flash memory is 4-16 MB, it is depend on used modell.
/// get to know where is the free memory space!!! 

/// stored data in eeprom:(recommended, if it is not a 1 byte data)
/// 
///		0. #include <EEPROM.h>
///		1. size of the data -> x bytes
///		2. data -> y bytes
/// 
/// write:
/// 
///		address -> start point of data frame
///		data -> x bytes
/// 
/// read:
/// 
///		read from address
/// 
/// Warnings: 
/// 
///		each type of data stored differently
///		eeprom storing data byte by byte
///		Therefor becarefull about how you store a data.
///		Think about the size of data type, for example float is 32 bit, or 4 bytes. 
///		This means that float needs minimum of 5 byte to store, 1 for the size, 4  for the dataframe.
/// 
/// bonus:
/// 
///		Callculate the minimum needed size of the eeprom, and define it at the starting point!
///		sort local datas in order of importance, and pick few data which need to run the device perfectly after a hard reset, or power lost.
///		Callculate each data size and store it  in  recommeneded way
/// 
///		store the address of the datas, or define each datas starting points(address).
/// 
/// data types:
/// 
///		bool:			1 byte
///		int:			4 bytes
///		unsigned int:		4 bytes
///		double:			8 bytes
///		float:			4 bytes
///		char:			1 byte
///		string:			24 bytes
///		array-s:		as many as the number of data stored in the array, and specified by the data type.
/// 
/// stored data:							unit(s)/byte(s)
/// 
///		char array: 
/// 
///		>*	IP: 255.255.255.255 -> 1+15 char	16x1
///		>*	SSID: 1+ max 10 char			11x1
///		>*	PassWord: 1+ max 10 char		11x1
/// 
///		int:
/// 
///		>*	host					1x4
///		>	active program index			1x4
///		>	clock: hour and minute			2x4
///		
///		float:
/// 
///		*	temperature offset	1		1x4
///		>	temperature offset	2		1x4
///		*	humidity offset		1		1x4
///		>	humidity offset		2		1x4
///		>	5x24 programable data			120x8
/// 
///		Summa for a minimum EEPROM size:
/// 
///			EspTouch(>):  						
///			EspCarryable(*):					
/// 
///			
/// </basics>


/// <defines>
/// 
/// memory accesspoints for each data defined in a <file_name>.cpp
/// 
/// #define IP	
/// #define SSID
/// #define PW
/// #define HOST
/// 
/// #define ACTIVEPROG
/// #define PROGS
/// 
/// #define HOUR
/// #define MINUTE
/// 
/// #define TMP_OFFSET //espcarry
/// 
/// #define TMP_OFFSET //esptouch
/// 
/// </defines>

/// <example code>
/// 
/// #include <EEPROM.h>
/// 
/// // Define the EEPROM size (in bytes)
/// #define EEPROM_SIZE 1024  // For example, 1 KB
/// 
/// void main(){
/// Serial.begin(115200);
///
///  // Initialize EEPROM with the defined size
/// if (!EEPROM.begin(EEPROM_SIZE)) {
///	 Serial.println("Failed to initialize EEPROM"); //-> log out to a file with date, Then reset board!
///	 return;
/// }
///
/// // Example write and commit
/// EEPROM.write(0, 123);  // Write a value to the EEPROM
/// EEPROM.commit();  // Commit the changes/save
///
/// // Example read
/// int value = EEPROM.read(0);  // Read the value back
/// Serial.print("Read value: ");
/// Serial.println(value);
/// }
/// </example code>


#include <EEPROM.h>
#include "Commands.h"

//addresses about where the data frame start in the "eeprom"
 #define EEPROM_SIZE 0x0400 // 1024 bytes

 #define FPROG1	     0x0000	// daily programs addresses
 #define FPROG2	     0x00C0	// contain 24 double data/ daily program. 
 #define FPROG3	     0x0180
 #define FPROG4	     0x0240
 #define FPROG5	     0x0301
 
 #define USER	     0x03C0	// wifi data addresses
 #define PW	     0x03C8
 #define IP	     0x03D0
 #define HOST	     0x03E0
 #define ENABLE	     0x03E4

 #define HOUR	     0x03E5	// other data addresses
 #define MIN	     0x03E9
 #define PROG	     0x03ED	//active prog
 #define TMPOFFSET   0x03F1
// will be used in ARDUINO IDE => have to change std::string to String
class EEPROMHandler
{
	Commands mainCommands, sideCommand, UnderSideCommand;


	string decodeCommand(string, unsigned*, Commands list); //return data, and return path in paramlist
	void checkInput(string*, string);
	void UnderSideMenu( string); 
	void setMenu( string);
	void resetMenu(string);
	void mainMenu();// if "TO DO" done than return true;

	void prints(string);
	void prints();//data param)

public:
	EEPROMHandler();
	~EEPROMHandler();

	void AutoSave();
	bool checkSerial(); //if keyword -> menu(); return true; else return false;

};

