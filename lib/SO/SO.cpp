/**
  @file: SO.cpp
  @class:SO

  @author: Gabriel Neto
  @date: 12/12/2021

  @brief: Create tasks and attach to desired core, this is the brain off everything

 */

/*********************************************************
    Includes
*********************************************************/
#include "SO.h"
#include <Arduino.h>
#include <PinDefinition.h>
#include <SCPI.h>
#include <pisca.h>
#include <CommunicationHandler.h>
#include <WifiSO.h>
/*********************************************************
    private constants.
*********************************************************/
static uint8_t CoreZero = 0;
static uint8_t CoreOne = 1;

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

/**
 Create tasks and attatch de desired core. Renmember to use a delay after create a task, it's a good pratice

 @param void
 @return void
 @author gabriels
 @date   18/12/2017
 */

/*xTasCreatePinnedToCore(
pvTaskCode          //função que implementa a tarefa
Name                //Nome da tarefa
usStackDepht        //Número de palavras a serem alocadas para uso com a pilha de tarefa
uxPriority          //Prioridade da tarefa (0 a N)
*pxCreatedTask      //Referência passada para a tarefa (pode ser null) handle
Xcore Id            //núcleo que irá executar a tarefa
)*/

void SO_CreateTasks()
{

    xTaskCreatePinnedToCore(
         SCPI,
        "SCPI",
        16384,
        NULL,
        3,
        NULL,
        CoreZero);

    delay(500);



    xTaskCreatePinnedToCore(
        InterfaceRead,
        "InterfaceRead",
        8192,
        NULL,
        4,
        NULL,
        CoreOne);

    delay(500);



    xTaskCreatePinnedToCore(
        InterfaceWrite,
        "InterfaceWrite",
        8192,
        NULL,
        3,
        NULL,
        CoreOne);

    delay(500);


   xTaskCreatePinnedToCore(
        InitializeWifiAP,
        "InitializeWifiAP",
        8192,
        NULL,
        10,
        NULL,
        CoreOne);

    delay(500);

    
    
}







