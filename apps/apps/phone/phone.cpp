#ifndef APP_PHONE_CPP
#define APP_PHONE_CPP

#include "phone.hpp"
#include "../../../hardware/hardware.hpp"
#include "../../../system/tasks/system.hpp"

bool AppPhone::call(String bruteNumber)
{
    if (bruteNumber[0] != '0' || bruteNumber.length() != 10)
        return 1;
        
    String number = "+33" + bruteNumber.substring(1, bruteNumber.length());

    SIM.print("ATD"+number+";\r\n");

    clearAllScreen(0x0000);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString(number, 160, 40, 4);
    String message="";
    tft.fillRoundRect(10, 400, 300, 70, 15, 0xF924);
    while(1)
    {
        if (isButtonPressed() || (isScreenTouched() && 10 < tx && tx < 310 && 400 < ty && ty < 470))
        {
            SIM.print("ATH\r\n");
            return 0;
        }
        if(SIM.available())
        {
            message += char(SIM.read());
            if(message.indexOf("NO")!=-1)
                return 0;
        }
    }
    SIM.print("ATH\r\n");
    return 0;
}

void AppPhone::run()
{
    drawGui();
    tft.setTextColor(0xFFFF);
    tft.drawCentreString(lastNumber, 160, 30, 4);
    while (true)
    {
        if (isScreenTouched())
        {
            for (int i = 0; i < 9; i++)
            {
                tft.setTextColor(0xFFFF);
                if (10 + i % 3 * 100 < tx && tx < 110 + i % 3 * 100 && 60 + int(i / 3) * 100 < ty && ty < 160 + int(i / 3) * 100) // check 1 to 9 numbers on the keyboard
                {
                    
                    while (isScreenTouched())
                        ;
                    tft.setTextColor(0x0000);
                    tft.drawCentreString(lastNumber, 160, 30, 4);
                    lastNumber += (i+1);
                    break;
                }
            }
            if (110 < tx && tx < 210 && 380 < ty && ty < 480) // check the 0
            {
                while (isScreenTouched())
                        ;
                tft.setTextColor(0x0000);
                tft.drawCentreString(lastNumber, 160, 30, 4);
                lastNumber += "0";
            }

            if (10 < tx && tx < 110 && 380 < ty && ty < 480) // check the clear button
            {
                while (isScreenTouched())
                        ;
                tft.setTextColor(0x0000);
                tft.drawCentreString(lastNumber, 160, 30, 4);
                lastNumber = lastNumber.substring(0, lastNumber.length()-1);
            }

            if (210 < tx && tx < 310 && 380 < ty && ty < 480) // check the call button
            {
                if(call(lastNumber))
                {
                    tft.setTextColor(0xF924);
                    tft.drawCentreString(lastNumber, 160, 30, 4);
                }
                drawGui();
            }

            tft.setTextColor(0xFFFF);
            tft.drawCentreString(lastNumber, 160, 30, 4);
        }
    }
}

void AppPhone::drawGui()
{
    clearAllScreen(0x0000);
    tft.drawRoundRect(10, 100, 300, 380, 30, 0xFFFF);
    for (int i = 0; i < 9; i++)
    {
        tft.setTextColor(0xFFFF);
        tft.drawCentreString(String(i + 1), 60 + i % 3 * 100, 130 + int(i / 3) * 100, 4);
    }
    tft.drawCentreString("0", 160, 430, 4);
}

#endif