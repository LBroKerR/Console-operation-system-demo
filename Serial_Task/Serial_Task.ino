#include "SerialTask.h"

void Taskcore(void* parameters){
  SerialTask *bios=new SerialTask();
  bios->main();
  delete bios;
  delay(1000);
  vTaskDelete(nullptr);
}


void setup() {
  // put your setup code here, to run once:
  TaskHandle_t serialTask;
  xTaskCreatePinnedToCore(Taskcore, "serialTask", 10000, NULL, 5, &serialTask, 1);
  //esp_reset();
}

void loop() {
}
  // put your main code here, to run repeatedly:


