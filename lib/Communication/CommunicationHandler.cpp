/**
  @file: CommunicationHandler.cpp
  @class:CommunicationHandler

  @author: Gabriel Neto
  @date: 10/01/2023

  @brief:Communicate with Wifi, USB, Ethernet. Write the requests in the QueueRx and read the answers from Queue Tx
 */

/*********************************************************
    Includes
*********************************************************/
#include <Arduino.h>
#include <CommunicationHandler.h>
#include <Serial.h>
#include <Queue.h>
#include <WifiSO.h>

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
    Read Data
*********************************************************/

void InterfaceRead(void *pvParameters) //Core 1 communication process
{
    DataRxForm ReceivedData;

    String SCPI_Message;

    while (true)
    {
        SCPI_Message = Serial_ProcessLoop(); //USB

        if (!SCPI_Message.isEmpty())
        {
            //ReceivedData.Message = SCPI_Message;
            strcpy(ReceivedData.Message,SCPI_Message.c_str());
            ReceivedData.ID = USB;
            ReceivedData.client = 0;         
            Write_QueueRx(ReceivedData);
        }

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

/*********************************************************
    Send Data
*********************************************************/

void InterfaceWrite(void *pvParameters) //Core 1 communication process   O problema está aqui
{
    while (true)
    {
        DataTxForm Response;
        Response = Read_QueueTx();
        String Message;
        Message = Response.Message;

        if (!Message.isEmpty())
        {
            switch (Response.ID)
            {

            case USB:
                Serial.print(Response.Message);
                break;

            case WIFI:
                //Serial.print("ENVIANDO DADOS PARA A ESP....");
                ReplyToClient(Response.Message);
                //Serial.print(Response.Message);
                
                break;

            case ETHERNET:
                //Serial.println(Response.Message);
                break;
            }
            // Serial.println(Response);
            // Wifi_write(Response);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    
}


