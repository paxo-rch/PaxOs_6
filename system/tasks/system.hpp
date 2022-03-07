#ifndef _SYSTEM_
#define _SYSTEM_

namespace System
{
    byte standby = 0;

    void powerOFF();
    void standbyOFF();
    void standbyON();
    void powerON();
    bool isPowerOn();
    byte isStandbyON();
    void standbyMode()
    {standby=3;}
}

#include "task.hpp"
#include "../../hardware/include/screen_light.hpp"
#include "../../hardware/include/button.hpp"

TaskManager SystemTasks;

bool forceReload = 0;

#include "hardware/hardware.hpp"
#include "../../apps/apps.hpp"


uint32_t chrono_test = 0;
bool state = 0;

bool proof_process()
{
    if (chrono_test + 500 < millis())
    {
        chrono_test = millis();
        if (state == 0)
        {
            tft.fillCircle(315, 3, 3, 0xFFFF);
            state = 1;
        }
        else
        {
            tft.fillCircle(315, 3, 3, 0x0000);
            state = 0;
        }
    }
    return 1;
}


bool BackgroundProcess()
{
    if(System::isStandbyON() == 3)
        System::standbyON();

    proof_process();
    SystemTasks.executeAll();
    
    if(forceReload)// for the macro while(condition && background_process <=1)
    {
        return 0;
    }

    if(System::isStandbyON())
        return 1;

    
    if(isButtonPressed())
        return 0;

    return 1;
}

void System::powerOFF()
{
    while (true)
    {
        
    }
}

void System::standbyOFF()
{
    standby = 0;
    resetButtonTimer();
    resetScreenTimer();
}

void System::standbyON()
{
    if(standby == 1)
    {
        standby = 2;
        return;
    }
    standby = 1;
    
    for(;standby;)
    {
        SCREEN_LIGHT::OFF();
        for(;!isButtonPressed();)
        {
            SystemTasks.executeAll();
            resetButtonTimer();
            resetScreenTimer();
        }

        if(standby == 2)
            standby=1;
        
        resetButtonTimer();
        resetScreenTimer();

        lockedScreen();

        if(standby == 2)
            standby=1;
    }
    standbyOFF();
    forceReload=1;
}

void System::powerON()
{

}



bool System::isPowerOn()
{
    return 1;
}

byte System::isStandbyON()
{
    return standby;
}

#endif