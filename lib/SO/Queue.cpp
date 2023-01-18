/*********************************************************
    Includes
*********************************************************/
#include <Arduino.h>
#include <Queue.h>
#include <SCPI.h>
/*********************************************************
    private types.
*********************************************************/
QueueHandle_t QueueRx = NULL; //declaration of QueueRx
QueueHandle_t QueueTx;

/*********************************************************
    private variable.
*********************************************************/
String SCPIMessageRxOut;
String SCPIMessageTxOut;

DataRxForm standard;


/*********************************************************
    private functions prototypes.
*********************************************************/

/*********************************************************
    private functions.
*********************************************************/

/*********************************************************
    Rx Data SCPI
*********************************************************/

void Write_QueueRx(DataRxForm QueueRxData)
{
    if (xQueueSend(QueueRx, (void *)&QueueRxData, 10) != pdTRUE) 
    {
        //Serial.println("Queue full");
    }

    else
    {
        
    }
}

struct DataRxForm Read_QueueRx() 
{
    static DataRxForm ReadQueue;
    if (xQueueReceive(QueueRx, &ReadQueue, 0) == pdTRUE) 
    {
        //Serial.println(ReadQueue.Message);
        return ReadQueue;
        
   }
    else{

  
    return standard;

    }

      
}

/*********************************************************
  Tx Data SCPI
*********************************************************/

void Write_QueueTx(DataTxForm QueueTxData)
{
    if (xQueueSend(QueueTx, (void *)&QueueTxData, 10) != pdTRUE)
    {
    }
}

DataTxForm Read_QueueTx()
{
    static DataTxForm ReadQueue;

    //check if there is a new data inside the Queue
    if (xQueueReceive(QueueTx,&ReadQueue, 0) == pdTRUE)
    {
        return ReadQueue;
    }

    else
        return {};
}

void Queue_Init()
{
    uint8_t Queue_Size = 60;

    QueueRx = xQueueCreate(Queue_Size, sizeof(DataRxForm)); //Create a queue for receive SCPI without losing Data
    QueueTx = xQueueCreate(Queue_Size, sizeof(DataTxForm));
}


