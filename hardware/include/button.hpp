#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../../system/tasks/system.hpp"

unsigned int button_chrono = 0;

bool isButtonPressed()
{
    bool state = !digitalRead(32);
    if(System::isStandbyON())
        return state;
    if(state == 0)
        button_chrono = millis();
    if(millis() - button_chrono > 400)
    {
        button_chrono = millis();
        System::standbyON();
        button_chrono = millis();
        return 0;
    }
        
    return state;
}

void resetButtonTimer()
{
    button_chrono = millis();
}

#endif