/*********************************************************
    Includes
*********************************************************/
#include <Arduino.h>
#include "GPIO.h"
#include <PinDefinition.h>



/*********************************************************
    private types.
*********************************************************/

/*********************************************************
    private variable.
*********************************************************/

/*********************************************************
    private functions prototypes.
*********************************************************/

/*********************************************************
    private functions.
*********************************************************/

void DigitalOutput_Init()
{
    pinMode (PIN_DO0,OUTPUT);
    pinMode (PIN_DO1,OUTPUT);
    pinMode (PIN_DO2,OUTPUT);
    pinMode (PIN_DO3,OUTPUT);
}


void DigitalInput_Init()
{
    pinMode (PIN_DO4,INPUT_PULLDOWN);
    pinMode (PIN_DO5,INPUT_PULLDOWN);
    pinMode (PIN_DO6,INPUT_PULLDOWN);
    pinMode (PIN_DO7,INPUT_PULLDOWN);
}


void AnalogInput_Init()
{
    pinMode(PIN_ADC0,INPUT);
    pinMode(PIN_ADC1,INPUT);
}

void AnalogOutput_Init()
{
    pinMode(PIN_ADC2, OUTPUT);
    pinMode(PIN_ADC3, OUTPUT);
}

