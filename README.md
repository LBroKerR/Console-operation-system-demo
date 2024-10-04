# Console-operation-system-demo
Menu will created with function array. 
Commands class will store the function names, and the indexes of these will be the key to the next function.
Could be use maps, but it will be upload to a microcontroller, to handle configuration via serial port.


Working as a consol app in windows/linux/mac and integrated to microprocessors.
Complex menu system can be build via handlers. and SerialTask contain mine.
main.cpp only needs for console application.

//ESP32 flashed via Arduino IDE, with setting of the esp32_doit_devkit/esp32 dev module( partition scheme: minimal SPIFFS)
//use simultaneously the in built Serial, and EEPROM will cause the esp32 hardware freezing, and watch dog timer won't reset the board.

IF YOU USE:{
  Create external functions and include it to sourse file, where the menu initialized.(for example: Menufunction.h, and .cpp)
  Build up the menu system in Serial_Task.cpp init function. //Use it as I did. Use my code as an example! 
  Recommended to Install PuTTY for serial communication. if esp32 or other device will run the code!
}
