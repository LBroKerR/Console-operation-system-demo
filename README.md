# Console-operation-system-demo
Menu will created with function array. 
Commands class will store the function names, and the indexes of these will be the key to the next function.
Could be use maps, but it will be upload to a microcontroller, to handle configuration via serial port.

Still working On! 

Working as a consol app at the moment.
Complex menu system can be build via handlers. and SerialTask contain mine.

TO DO:{
  Integrate to esp32! done! Look after in SerialTask_IDE folder.
  Change Serial_Task.h and .cpp to OOP cpp class, which use the clean code steps!
  Create interupt in the new SerialTaskHandler objet for get data frame from serial port if avaible! 
}

IF YOU USE:{
  Create external function in Menufunction.h, and .cpp
  Build up the menu system in Serial_Task.cpp init function. //Use it as I did. Use my code as an example! 
}
