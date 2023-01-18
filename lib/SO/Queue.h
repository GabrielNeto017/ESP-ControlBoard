/*
 * Author: Rodrigo Guerra
 * Date: 02/07/2021
 *
 */

#ifndef _QUEUE_H
#define _QUEUE_H

#include<Arduino.h>
#include <AsyncTCP.h>

#define USB 0
#define WIFI 1
#define ETHERNET 2


struct DataRxForm{
    char Message[60];
    uint8_t ID;
    AsyncClient client;

};


struct DataTxForm{
    char Message[60];
    uint8_t ID;  //0 Serial   1 Wifi    2 Ethernet
    AsyncClient client;

};


void Queue_Init();
void Write_QueueRx(DataRxForm QueueRxData);
struct DataRxForm Read_QueueRx();

void Write_QueueTx(DataTxForm QueueTxData);
struct DataTxForm Read_QueueTx();





#endif