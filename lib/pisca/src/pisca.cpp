

#include <Arduino.h>
#include "pisca.h"



PiscaLed::PiscaLed(int pino,int tempo){
_pino=pino;
_tempo=tempo;
}

void PiscaLed::Blink(){
digitalWrite(_pino,HIGH);
vTaskDelay(pdMS_TO_TICKS(pdMS_TO_TICKS(_tempo))/2);;
digitalWrite(_pino,LOW);
vTaskDelay(pdMS_TO_TICKS(pdMS_TO_TICKS(_tempo))/2);;
}