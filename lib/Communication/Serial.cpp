/*********************************************************
    Includes
*********************************************************/
#include <Arduino.h>
#include "Serial.h"

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

void Serial_Init()
{
    Serial.begin(115200); //Baud Rate of Serial Monitor
    
}

String Serial_ProcessLoop()
{
    if (Serial.available() > 0)
    {
        String SCPIBuffer;
        char caractere;
        
        // Enquanto receber algo pela serial
        while (Serial.available() > 0)
        {
            SCPIBuffer = Serial.readStringUntil('\n');
            //SCPIBuffer = Serial.readString();
            //SCPIBuffer.trim();
        }
       
        return SCPIBuffer;
    }

    

    else return {};
}