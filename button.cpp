#include "button.h"

button::button()
{

}

button::~button()
{

}

void button::initButton(short gpioPin){
    pin=gpioPin;
    pinMode(pin,INPUT);
    pullUpDnControl(pin,PUD_UP);
}

bool button::state(){
    if(digitalRead(pin)){
        flag=1;
        debounceCounter=0;
        return false;
    }
    if(!digitalRead(pin)){
                debounceCounter ++;
                if(debounceCounter>100){
                    if(flag){
                       flag=0;
                       return true;
                } else return false;
                }
    }
    return false;
}
