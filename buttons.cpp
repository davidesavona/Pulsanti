#include "buttons.h"

buttons::buttons()
{

}

buttons::~buttons()
{

}

void buttons::initButtons(){
    pinMode(button_1,INPUT);
    pullUpDnControl(button_1,PUD_UP);
}

bool buttons::state(){
    if(digitalRead(button_1)){
        flag=1;
        debounceCounter=0;
        return false;
    }
    if(!digitalRead(button_1)){
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
