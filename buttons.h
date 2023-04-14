#ifndef BUTTONS_H
#define BUTTONS_H

#pragma once
#include "wiringPi.h"

class buttons
{
public:
    buttons();
    ~buttons();
    void initButtons();
    bool state();
private:
    short button_1=22;
    bool flag=1;
    int debounceCounter=0;

};

#endif