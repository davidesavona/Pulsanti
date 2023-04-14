#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include "wiringPi.h"

class button
{
public:
    button();
    ~button();
    void initButton(short gpioPin);
    bool state();
    
private:
    short pin=-1;
    bool flag=1;
    int debounceCounter=0;

};

#endif