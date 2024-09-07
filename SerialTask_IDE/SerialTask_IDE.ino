#include "Serial_Task.h"


void Taskcore(void* parameters){
  Serial.begin(115200);
  SerialTask(parameters);
  Serial.end();
  vTaskDelete(nullptr);
}

void setup() {
  // put your setup code here, to run once:
  TaskHandle_t Task;
  xTaskCreatePinnedToCore(Taskcore, "Task", 10000, NULL, 1, &Task, 1);
  //esp_reset();
}

void loop() {
  // put your main code here, to run repeatedly:

}
