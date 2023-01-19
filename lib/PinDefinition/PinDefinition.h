/*
 * Author: Gabriel Neto
 * Date: 12/12/2022
 *
 */

#define Company_Name "Exsto Tecnologia"
#define Product_Name "ESP32/1  "
#define Serial_Number "--------"
#define Software_Version "v1.0"

#ifndef _PINDEFINITION_H
#define _PINDEFINITION_H

#include<Arduino.h>


//AVOID TO USE GPIO6,GPIO7,GPIO8,GPIO9,GPIO10 AND GPIO11 THEY ARE CONNCETED  TO THE INTEGRATED SPI FLASH ON THE ESP-32


//DEFINE SPI1 PINS
#define PIN_SPI1_MISO 19
#define PIN_SPI1_MOSI 23
#define PIN_SPI1_CLK 18
#define PIN_SPI1_CS 5

//DEFINE I2C PINS
#define I2C_SDA 21   
#define I2C_SCL 22   


//DEFINE SPI2 PINS
//#define PIN_SPI2_MISO 12
//#define PIN_SPI2_MOSI 13
//#define PIN_SPI2_CLK 14
//#define PIN_SPI2_CS 15


//DEFINE SERIAL COMUNICATION PINS
#define PIN_RX0 1
#define PIN_TX0 3                               //SEND OUTPUT AT BOOT DON'T USE IT AS GPIO


//DEFITION OF ANALOG READ PINS (CAN BE USED AS GPIO INPUT, IF DESIRED)
#define PIN_ADC0 36
#define PIN_ADC1 39

#define PIN_ADC2 12
#define PIN_ADC3 14

//DEFINITION OF ANALOG WRITE PINS
//#define PIN_DAC0 25
//#define PIN_DAC1 26

//DEFINITION OF GPIO OR PWM PINS
#define PIN_DO0 2                               //IF CONFIGURED AS INPUT AND WITH PULLED UP RESISTOR, IT OUTPUTS PWM SIGNT AT BOOT
#define PIN_DO1 0                               //ON LED BOARD
#define PIN_DO2 4  
#define PIN_DO3 16

#define PIN_DO4 27
#define PIN_DO5 33
#define PIN_DO6 32
#define PIN_DO7 35


//disponíveis: 12, 17, 34





#endif