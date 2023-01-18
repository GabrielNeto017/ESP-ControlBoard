


#ifndef _WIFISO_H
#define _WIFISO_H


#include<Arduino.h>
#include<Queue.h>

void Wifi_Init();
void Read_Static_IP();
String Wifi_ProcessLoop();
void InitializeWifiAP(void *pvParameters);
void ReplyToClient(String Response);


#endif