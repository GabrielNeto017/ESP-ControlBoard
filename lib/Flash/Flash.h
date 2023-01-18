/*
 * Author: Gabriel Neto
 * Date: 12/12/2022
 *
 */



#ifndef _FLASH_H
#define _FLASH_H

#include <Arduino.h>

void WriteFlash(String dado, String key);
String ReadFlash(String key);

#endif