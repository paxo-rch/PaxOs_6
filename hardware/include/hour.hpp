#ifndef HOUR_HPP
#define HOUR_HPP

#include "Sim800L.h"

void getHour(int *hours, int *minutes);

#include "../../graphics/graphics.hpp"

#include "phone.hpp"


int ACTUAL_HOUR = 0;
int ACTUAL_MINUTE = 0;

byte update_hour()
{
    int day,month,year,minute,second,hour;
    SIM.RTCtime(&day,&month,&year,&hour,&minute,&second);
    ACTUAL_HOUR=hour;
    ACTUAL_MINUTE=minute;

    if(!isScreenBarEnable)
        return 0;

    String hourText="";
    if(hour<10)
        hourText +=  "0" + String(hour);
    else
        hourText += String(hour);
    hourText += ":";
    if(minute<10)
        hourText +=  "0" + String(minute);
    else
        hourText += String(minute);

    tft.fillRoundRect(120,-10,145,35,15,0x0000);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString(hourText, 160, -1, 4);
    tft.setTextColor(0x16C2);
    tft.drawCentreString(String(battery::getLevel()) + "%", 230, -1, 4);
    return 0;
}

void getHour(int *hours, int *minutes)
{
    *hours = ACTUAL_HOUR;
    *minutes = ACTUAL_MINUTE;
}

#endif