
/*
===============================================================================
 Name        : New_ControlBoard
 Author      : Gabriel Neto
 Version     : v1.0
 Description : Placa de controle
===============================================================================
*/

#include <Arduino.h>
#include <PinDefinition.h>
#include <GPIO.h>
#include <SO.h>
#include <Serial.h>
#include <Queue.h>
#include <AnalogWrite.h>

// Wifi Includes
#include <WifiSO.h>




/*
============================================
Moved to "PinDefinition.h"

#define Company_Name "Exsto Tecnologia"
#define Product_Name "ESP32/1  "
#define Serial_Number "--------"
#define Software_Version "v1.0"

============================================
*/





void setup()
{
  setCpuFrequencyMhz(240);
  
  DigitalOutput_Init();
  DigitalInput_Init();
  AnalogInput_Init();
  AnalogOutput_Init();
  
  Serial_Init();
  Queue_Init();
  Wifi_Init();
  SO_CreateTasks();
}

void loop() {
  
}
