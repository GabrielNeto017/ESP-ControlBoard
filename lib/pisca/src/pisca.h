/*
 * Author: Rodrigo Guerra
 * Date: 27/05/2021
 *
 */


#ifndef _PISCA_H
#define _PISCA_H

#include<Arduino.h>

class PiscaLed{

private:
int _pino=0;
int _tempo=0;


public:

    PiscaLed(int pino, int tempo);
    void Blink();


};


#endif





