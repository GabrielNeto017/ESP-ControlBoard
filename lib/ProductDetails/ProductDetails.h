/*
 * Author: Rodrigo Guerra
 * Date: 27/05/2021
 *
 */

#ifndef _Details_H
#define _Details_H

#include <Arduino.h>


uint32_t id = ESP.getEfuseMac();
String ID = String(id);




/*
#define Company_Name "Exsto Tecnologia"
#define Product_Name "ESP32"
#define Serial_Number "12345678"
#define Software_Version "v0.1"
*/


//String chipId = ;
//Serial_Number = chipId;

#endif