#include "EEPROMHandler.h"
//private functions:

  bool isnumber(String str){
    bool decimalPointFound = false;
    int len = str.length();
    if (len == 0) {
      return false;
    }
    int startIndex=0;
    if(str[0]=='-'){ // Allow first character to be a negative sign
      startIndex=1;
    }
    for (int i = startIndex; i < len; i++) {
      if (str[i] == '.') {
        if (decimalPointFound) {// More than one decimal point
          return false;
        }
        decimalPointFound = true;
      } 
      else if (!isDigit(str[i])) {// Not a digit or decimal point
        return false;
      }
    }
    return true;//if all character correctly create a number, int, uint, double, float
  }

//public functions:
        //need to check all data before dot(.) 
        //is it number? smaller then 255, bigger then 0? need?>>if smaller then 100 has 0 before the number?
        //return false, if not correct form, or data/ nullptr comes
        //return true, if EEPROM.write.. successfully done
bool check_IP_datagramm(void* param){
  String *str = (String*)param;
  if (str == nullptr) {
    return false;
  }
    int octets = 0, value = 0;
    for (int i = 0; i < str->length(); i++) {
        char c = (*str)[i];
        if (c == '.') {
            if (++octets > 3 || value > 255) return false;
            value = 0;
        } else if (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
        } else {
            return false;
        }
    }
    return (octets == 3 && value <= 255);
}

    bool check_host_datagramm(void* param){
        String *str=(String*)param;
        unsigned host=0;
        if(str==nullptr){
          return false;
        }
        if(!isnumber(*str)){
          return false;
        }
        host=str->toInt();
        if(host<1024 || host >-1){
          return false;
        }
        EEPROM.begin(EEPROM_SIZE);
        EEPROM.writeUInt(HOST,host);
        EEPROM.commit();
        EEPROM.end();
        return true;
    }

    bool check_pass_datagramm(void* param){
        String *str=(String*)param;
        if(str==nullptr){
            return false;
        }
        char tmp;
        unsigned address=PW;
        if(str->length()<=10){
            EEPROM.begin(EEPROM_SIZE);
            for(unsigned i=0; i< 10; i++){
              tmp=(*str)[i];
              EEPROM.writeChar(address, tmp);
              address++;
            }
            EEPROM.commit();
            EEPROM.end();
            return true;
        }
        return false;
    }

    bool check_user_datagramm(void* param){
        String *str=(String*)param;
        if(str==nullptr){
            return false;
        }
        if(str->length()<=10){
            EEPROM.begin(EEPROM_SIZE);
            EEPROM.writeString(USER,*str);
            EEPROM.commit();
            EEPROM.end();
        }
        return true;
    }

    bool check_switch_datagramm(void* param){
        String *str=(String*)param;
        if(str==nullptr){
            return false;
        }
        if(*str=="enable"){
            EEPROM.begin(EEPROM_SIZE);
            EEPROM.writeBool(ENABLE, true);
        }
        else if(*str=="disable"){
            EEPROM.begin(EEPROM_SIZE);
            EEPROM.writeBool(ENABLE, false);
        }
        else{
            return false;
        }   
        EEPROM.commit();
        EEPROM.end();
        return true;
    }

    bool check_temp_datagramm(void* param){
        String *str=(String*)param;
        double temp=0.0;
        if(str==nullptr){
            return false;
        }
        if(!isnumber(*str)){
          return false;
        }
        temp=str->toDouble();
        if(temp>=-10 && temp <=10){
          EEPROM.begin(EEPROM_SIZE);
          EEPROM.writeDouble(TMPOFFSET,temp);
          EEPROM.commit();
          EEPROM.end();
          return true;
        }
        return false;
    }
    bool write_out_clock(unsigned hour, unsigned min){
        EEPROM.begin(EEPROM_SIZE);
        EEPROM.writeUInt(HOUR, hour);
        EEPROM.writeUInt(MIN, min);
        EEPROM.commit();
        EEPROM.end();
        return true;
    }
    bool check_clock_datagramm(void* param){
        String* str = (String*)param;
        if (str == nullptr || str->length() < 5) {
            return false;
        }
        unsigned hour = 0, min = 0;
        char* endptr;
        hour = strtol(str->c_str(), &endptr, 10);
        if (endptr == str->c_str() || hour >= 24) {
            return false; 
        }
        min = strtol(endptr, &endptr, 10);
        if (endptr == str->c_str() || min >= 60) {
            return false; 
        }
        return write_out_clock(hour, min);
    }
// will be part of the autosave functions!
    bool write_out_active_program_number(unsigned param){
        EEPROM.begin(EEPROM_SIZE);
        EEPROM.writeUInt(PROG, param);
        EEPROM.commit();
        EEPROM.end();
        return true;
    }

    bool write_out_full_program(unsigned index, double* program){
        unsigned address=0;
        switch (index){
            case 0:address=FPROG1;break;
            case 1:address=FPROG2;break;
            case 2:address=FPROG3;break;
            case 3:address=FPROG4;break;
            case 4:address=FPROG5;break;
            default: return false;
        }
        EEPROM.begin(EEPROM_SIZE);
        for(unsigned i=0; i<PSIZE; i++){
            EEPROM.writeDouble(address, program[i] );
            address+=9;
        }
        
        EEPROM.end();
        return true;
    }

    bool Hardreset(void*param){
       String* str = (String*)param;
       if(str!=nullptr){
          if(*str==getPASS(10)){
            EEPROM.begin(EEPROM_SIZE);
            for(unsigned i=FPROG1; i< EEPROM_SIZE; i++){
              EEPROM.writeBool(i, false);
            }
            EEPROM.commit();
            EEPROM.end();
            return true;
          }
        }
      *str="password hidden!";
      param=str;
      return false;
    }

    bool print(void* param){
        EEPROM.begin(EEPROM_SIZE);
        Serial.println(getIP());
        Serial.println(getPASS(10));
        Serial.println(getHost());
        EEPROM.end();
        return true;
    }

    // return a boolen variable, about to enable or not the wifi task on the device 
    bool getSwitch(){
      EEPROM.begin(EEPROM_SIZE);
      bool param=EEPROM.readBool(ENABLE);
      EEPROM.end();
      return param;
    }

    //return the last active programram index.
    unsigned getActiveprog(){
      EEPROM.begin(EEPROM_SIZE);
        unsigned param =EEPROM.readUInt(PROG);
        EEPROM.end();
        return param;
    }

    //return the last clock numbers
    void getClock(unsigned* hour, unsigned*min){
      EEPROM.begin(EEPROM_SIZE);
      *hour=EEPROM.readUInt(HOUR);
      *min=EEPROM.readUInt(MIN);
      EEPROM.end();
    }

    //return nullptr if index not valid, else return an array which contain 24 double data. 
    //Every data means a temp, and every index means the hour where the data will be actice
    double *getProgram(unsigned index){
        double array[PSIZE]={0.0};
        unsigned address=0;
        switch (index){
            case 0:address=FPROG1;break;
            case 1:address=FPROG2;break;
            case 2:address=FPROG3;break;
            case 3:address=FPROG4;break;
            case 4:address=FPROG5;break;
            default: return nullptr;
        }
        EEPROM.begin(EEPROM_SIZE);
        for (unsigned i = 0; i < PSIZE; i++)
        {
            array[i]=EEPROM.readDouble(address);
            address+=NEXT;
        }
        EEPROM.end();
        return array;
    }

    //return offset to mesure corretly
    double getOffset(){
      EEPROM.begin(EEPROM_SIZE);
       double param = EEPROM.readDouble(TMPOFFSET);
       EEPROM.end();
       return param;
    }

    //return the server host
    unsigned getHost(){
      EEPROM.begin(EEPROM_SIZE);
      unsigned param=EEPROM.readUInt(HOST);
       EEPROM.end();
        return param;
    }

    //return router username 
    String getUser(unsigned size){
        char* str=new char[size];
        unsigned address=USER;
        EEPROM.begin(EEPROM_SIZE);
        for(unsigned i=0; i<size; i++){
            str[i]=EEPROM.readChar(address);
            address++;
        }
        String tmp(*str);
        delete[] str;
        EEPROM.end();
        return tmp;
    }

    //return router pass
    String getPASS(unsigned size){
        char* str=new char[10];
        unsigned address=PW;
          EEPROM.begin(EEPROM_SIZE);
        for(unsigned i=0; i<10; i++){
            str[i]=EEPROM.readChar(address);
            address++;
        }
        String tmp(*str);
        delete[] str;
        EEPROM.end();
        return tmp;
    }

    //return server ip
    String getIP(){
        char* str=new char[IPSIZE];
        unsigned address=IP;
          EEPROM.begin(EEPROM_SIZE);
        for(unsigned i=0; i<IPSIZE; i++){
            str[i]=EEPROM.readChar(address);
            address++;
        }
        String tmp(*str);
        delete[] str;
         EEPROM.end();
        return tmp;
    }