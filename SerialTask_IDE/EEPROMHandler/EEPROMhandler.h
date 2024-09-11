#pragma once
#ifndef EEPROMHANDLER_H
#define EEPROMHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE  0x0400 // 1024 bytes
                            //dpuble array
#define FPROG1	     0x0000	// daily programs addresses
#define FPROG2		 0x00C0	// contain 24 double data/ daily program. 
#define FPROG3	     0x0180
#define FPROG4	     0x0240
#define FPROG5	     0x0301
#define PSIZE        0x0018
#define NEXT         0x0009
                            //char*
#define USER	     0x03C0	// wifi data addresses
#define PW		     0x03C8
#define IP		     0x03D0
#define HOST	     0x03E0 //unsigned
#define ENABLE	     0x03E4 // bool
#define IPSIZE       0x000F

#define HOUR	     0x03E5	// other data addresses // unsigned
#define MIN			 0x03E9 // unsigned
#define PROG	     0x03ED	//active prog // unsigned
#define TMPOFFSET    0x03F1 //double

class EEPROMHandler {

  bool isnumber(String);

public:
    EEPROMHandler();
    ~EEPROMHandler();

    bool check_IP_datagramm(void* param);
    bool check_host_datagramm(void* param);
    bool check_pass_datagramm(void* param);
    bool check_user_datagramm(void* param);
    bool check_switch_datagramm(void* param);
    bool check_temp_datagramm(void* param);
    //auto and manualy override enabled.
    bool write_out_clock(unsigned, unsigned);
    bool check_clock_datagramm(void* param);
    //autosave
    bool write_out_active_program_number(unsigned param);
    bool write_out_full_program(unsigned index, double* program);

    bool getSwitch();
    unsigned getActiveprog();
    void getClock(unsigned*, unsigned*);
    double* getProgram(unsigned);
    double getOffset();
    unsigned getHost();
    String getUser(unsigned size);
    String getPASS(unsigned size);
    String getIP();
};


#endif //EEPROMHANDLER_H
