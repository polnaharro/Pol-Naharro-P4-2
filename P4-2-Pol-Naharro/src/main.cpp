#include <Arduino.h>
#define  LED  18
SemaphoreHandle_t Semaphore;
void On(void *pvParameters);
void off(void *pvParameters);
void setup()
{
  Serial.begin(115200);
  pinMode(LED ,OUTPUT);
  Semaphore = xSemaphoreCreateBinary();
  xTaskCreate(On, "ON",10000,NULL,1,NULL);
  xTaskCreate(off, "OFF", 10000,NULL,1,NULL);
  xSemaphoreTake(Semaphore,portMAX_DELAY);
  
}

void loop(){delay(1000);}
void On(void *pvParameters)
{
  for(;;)
  {
   
   Serial.println("on");
   
   digitalWrite(LED,LOW);
   xSemaphoreGive(Semaphore);
   vTaskDelay(1000);
  }
}
void off(void *pvParameters)
{
  for(;;)
  {
    
    Serial.println("off");
    
    digitalWrite(LED,HIGH);
    xSemaphoreGive(Semaphore);
    vTaskDelay(1000);
  }
}