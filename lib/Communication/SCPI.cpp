/**
  @file: SCPI.cpp
  @class:SCPI

  @author: Gabriel Neto
  @date: 12/12/2022

  @brief: Communicate using SCPI Commands with Computer
 */

/*********************************************************
    Includes
*********************************************************/
#include <Arduino.h>
#include <PinDefinition.h>
#include <pisca.h>
#include <serial.h>
#include <ProductDetails.h>
#include <Queue.h>
#include <CommunicationHandler.h>
#include <SCPI.h>
#include <esp32-hal-ledc.h>
//#include <AnalogWrite.h>

/*********************************************************
    private types.
*********************************************************/
//PiscaLed p(PIN_DO3, 200);
//PiscaLed led2(PIN_DO2, 50);



void Send_Reply(String TXreply);
DataRxForm SCPIData;
DataRxForm AnalogOutput;

String Data;

/*********************************************************
    private variable.
*********************************************************/

/*********************************************************
    private functions prototypes.
*********************************************************/
void SCPI_IDN();
void DigitalInput();
void ACTION();
void AnalogInput();
void MEASURE();


String LEITURA_A;
int leitura=0;
int leituraAI0=0;
int calc = 0;


/*********************************************************
    Receive Data
*********************************************************/

void SCPI(void *pvParameters)
{
    while (true)
    {
        
        SCPIData = Read_QueueRx();
        Data=SCPIData.Message;
       
        if(!Data.isEmpty()){

        } 
        
        if (Data == "*IDN?")
        {
            //Serial.println("-----------------");
            SCPI_IDN();
            
        }

        if(!strncmp(Data.c_str(), "ACTI", 4))
        {   
            ACTION();
        }

        if(!strncmp(Data.c_str(), "MEAS", 4))
        {   
            MEASURE();
        }

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

/*********************************************************
    Process Data
*********************************************************/

/**
Identification (IDN) Process

 @param object pointer
 @return void
 @author Gabriel Neto
 @date   01/12/2022
 */

void SCPI_IDN()
{
    String IDN;

    IDN.clear();

    IDN.concat(Company_Name);
    IDN.concat(",");
    IDN.concat(Product_Name);
    IDN.concat(",");
    IDN.concat(Serial_Number);
    IDN.concat(",");
    IDN.concat(Software_Version);
    IDN.concat("\n");


    Send_Reply(IDN);
}

void DigitalInput()
{
    String LEITURA_D;

    //LEITURA_D.clear();

    LEITURA_D.concat(digitalRead(PIN_DO4));
    LEITURA_D.concat(digitalRead(PIN_DO5));
    LEITURA_D.concat(digitalRead(PIN_DO6));
    LEITURA_D.concat(digitalRead(PIN_DO7));
    LEITURA_D.concat(0);
    LEITURA_D.concat(0);
    LEITURA_D.concat(0);
    LEITURA_D.concat(0);
    LEITURA_D.concat("\n");
    Send_Reply(LEITURA_D);
}

void AnalogOutputVoid()
{
    String mult;
    mult.concat(Data[14]);
    mult.concat(Data[15]);
    mult.concat(Data[16]);
    calc = mult.toInt();  //0-100 conversion
}

void AnalogInput()
{
    Send_Reply(LEITURA_A);
}




void Send_Reply(String TXreply){

DataTxForm SCPIReply;

strcpy(SCPIReply.Message, TXreply.c_str());
//Serial.printf(SCPIReply.Message);
SCPIReply.ID = SCPIData.ID;
SCPIReply.client = SCPIData.client;
Write_QueueTx(SCPIReply);


}

void ACTION(){

    //DIGITAL OUTPUTS
    if(!strncmp(Data.c_str(), "ACTI:DIGI:DO0 ", 14))
        {   
            if(!strncmp(Data.c_str(), "ACTI:DIGI:DO0 1", 15)){
                digitalWrite(PIN_DO0, HIGH);
            }
            else{
                digitalWrite(PIN_DO0, LOW);
            }
        }
    else  if(!strncmp(Data.c_str(), "ACTI:DIGI:DO1 ", 14))
        {   
            if(!strncmp(Data.c_str(), "ACTI:DIGI:DO1 1", 15)){
                digitalWrite(PIN_DO1, HIGH);
            }
            else{
                digitalWrite(PIN_DO1, LOW);
            }
        }     
    else  if(!strncmp(Data.c_str(), "ACTI:DIGI:DO2 ", 14))
        {   
            if(!strncmp(Data.c_str(), "ACTI:DIGI:DO2 1", 15)){
                digitalWrite(PIN_DO2, HIGH);
            }
            else{
                digitalWrite(PIN_DO2, LOW);
            }
        }    
    else  if(!strncmp(Data.c_str(), "ACTI:DIGI:DO3 ", 14))
        {   
            if(!strncmp(Data.c_str(), "ACTI:DIGI:DO3 1", 15)){
                digitalWrite(PIN_DO3, HIGH);
            }
            else{
                digitalWrite(PIN_DO3, LOW);
            }
        }  

    //ANALOG OUTPUTS
    if(!strncmp(Data.c_str(), "ACTI:ANAL:AO0 ", 14))
        {  
            AnalogOutputVoid();
            analogWrite(PIN_ADC2, calc*2.5);
        }
     else  if(!strncmp(Data.c_str(), "ACTI:ANAL:AO1 ", 14))
        {   
            AnalogOutputVoid();
            analogWrite(PIN_ADC3, calc*2.5);
        } 
}


void MEASURE(){

    if(!strncmp(Data.c_str(), "MEAS:DINP?", 10))
        {   
            DigitalInput();
        }

    else if(!strncmp(Data.c_str(), "MEAS:ANAL:", 10))
    {
        if(!strncmp(Data.c_str(), "MEAS:ANAL:CH0?", 14))
        {
            LEITURA_A.clear();
            LEITURA_A.concat(analogRead(PIN_ADC0)/40.95);
            LEITURA_A.concat("\n");
            AnalogInput();
        }
        if(!strncmp(Data.c_str(), "MEAS:ANAL:CH1?", 14))
        {
            LEITURA_A.clear();
            LEITURA_A.concat(analogRead(PIN_ADC1)/40.95);
            LEITURA_A.concat("\n");
            AnalogInput();
        }
    }

}


