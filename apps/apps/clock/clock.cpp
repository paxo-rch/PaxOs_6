#ifndef CLOCK_APP_CPP
#define CLOCK_APP_CPP

#include "clock.hpp"
#include "../../../graphics/graphics.hpp"


#define SIZEX_BUTTON_CLOCK 200

void ClockApp::run()
{
    menu();
}

void ClockApp::menu()
{
    while(1)
    {
        clearAllScreen(0x0000);
        Button launchClock(160, 100, SIZEX_BUTTON_CLOCK, 40);
        Button launchTimer(160, 150, SIZEX_BUTTON_CLOCK, 40);
        Button launchAlarm(160, 200, SIZEX_BUTTON_CLOCK, 40);
        launchClock.setText("Clock");
        launchTimer.setText("Timer");
        launchAlarm.setText("Alarm");
        launchClock.draw();
        launchTimer.draw();
        launchAlarm.draw();

        while(1)
        {
            if(launchClock.isReleased())
                simpleClock();
            if(launchTimer.isReleased())
                simpleTimer();
            if(launchAlarm.isReleased())
                alarmClock();
            if(reloadGui)
            {
                reloadGui=0;
                break;
            }
        }
    }
}

void ClockApp::simpleClock()
{
    reloadGui=1;

    clearAllScreen(0x0000);
    int hour, minute;
    while(1)
    {
        tft.setTextFont(7);
        tft.setRotation(3);
        tft.setTextSize(3);
        tft.fillScreen(0x0000);

        getHour(&hour, &minute);

        tft.setCursor(10, 70);
        tft.setTextColor(0xFFFF);
        tft.print(hour);
        tft.print(":");
        tft.print(minute);
        tft.setTextFont(1);
        tft.setTextSize(1);
        wait(30000);
    }
    tft.setRotation(0);
    resetScreenTimer();
}

void ClockApp::simpleTimer()
{
    reloadGui=1;

    clearAllScreen(0x0000);
    Button start(240, 450, 100, 40);
    Button clear(80, 450, 100, 40);
    start.setText("start");
    clear.setText("clear");
    start.draw();
    clear.draw();

    long  timer_actu = millis();

    while(1)
    {
        while(1)
        {
            if(start.isReleased())
                break;
            if(clear.isReleased())
            {
                tft.fillRect(100, 90, 120, 40, 0x0000);
                tft.setTextColor(0xFFFF);
                tft.drawCentreString("0", 160, 100, 4);
            }
            timer=millis();
        }

        while(1)
        {
            if(start.isReleased())
                break;
            if(clear.isReleased())
                timer=millis();
            if(timer_actu + 10 < millis())
            {
                tft.fillRect(100, 90, 120, 40, 0x0000);
                tft.setTextColor(0xFFFF);
                double toPrint = (float) (millis() - timer)/1000;
                tft.drawCentreString(String(toPrint), 160, 100, 4);
                timer_actu=millis();
            }
        }
    }
}

void ClockApp::alarmClock()
{
    reloadGui=1;
}


#endif