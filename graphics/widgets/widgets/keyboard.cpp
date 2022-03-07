#ifndef Keyboard_CPP
#define Keyboard_CPP

#include "../../screen/screen.hpp"

#include "keyboard.hpp"

Keyboard::Keyboard(uint16_t textColor, uint16_t backgroundColor)
{
    drawForce(1);
}

void Keyboard::draw()
{
    if(!alreadyDrawed)
        drawForce(1);

    alreadyDrawed = true;
}

void Keyboard::drawForce(bool all)
{
    if (all)
        tft.fillRoundRect(5, 307, 310, 170, 15, 0x4A69);
    for (byte j = 0; j < 3; j++)
    {
        for (byte i = 0; i < 10; i++)
        {
            tft.fillRoundRect(12 + i * 30, 313 + j * 40, 28, 35, 10, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString(String(alphabet[mode][j][i]), 26 + i * 30, 322 + j * 40, 4);
        }
    }

    tft.fillRoundRect(40, 433, 240, 35, 10, 0x7BEF);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("espace", 160, 442, 4);

    tft.fillRoundRect(282, 433, 28, 35, 10, 0x7BEF);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("S", 296, 442, 4);

    tft.fillRoundRect(12, 433, 27, 35, 10, 0x7BEF);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("/\\", 25, 442, 4);
}

bool Keyboard::isTouch()
{
    if (isScreenTouched())
    {
        TFT_getTouch();

        for (byte j = 0; j < 3; j++)
        {
            for (byte i = 0; i < 10; i++)
            {
                if (12 + i * 30 < tx && tx < 40 + i * 30 && 313 + j * 40 < ty && ty < 348 + j * 40)
                {
                    tft.fillRoundRect(12 + i * 30, 313 + j * 40, 28, 35, 10, 0x9CF3);
                    tft.setTextColor(0xFFFF);
                    tft.drawCentreString(String(alphabet[mode][j][i]), 26 + i * 30, 322 + j * 40, 4);
                    while (isScreenTouched())
                        ;
                    tft.fillRoundRect(12 + i * 30, 313 + j * 40, 28, 35, 10, 0x7BEF);
                    tft.setTextColor(0xFFFF);
                    tft.drawCentreString(String(alphabet[mode][j][i]), 26 + i * 30, 322 + j * 40, 4);
                    text += alphabet[mode][j][i];
                    return 1;
                }
            }
        }

        if (40 < tx && tx < 280 && 433 < ty && ty < 468)
        {
            tft.fillRoundRect(40, 433, 240, 35, 10, 0x9CF3);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("espace", 160, 442, 4);
            while (isScreenTouched())
                ;
            tft.fillRoundRect(40, 433, 240, 35, 10, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("espace", 160, 442, 4);
            text += " ";
            return 1;
        }

        if (282 < tx && tx < 310 && 433 < ty && ty < 468)
        {
            tft.fillRoundRect(282, 433, 28, 35, 10, 0x9CF3);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("S", 296, 442, 4);
            while (isScreenTouched())
                ;
            tft.fillRoundRect(282, 433, 28, 35, 10, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("S", 296, 442, 4);
            text = text.substring(0, text.length() - 1);
            return 1;
        }

        if (12 < tx && tx < 50 && 433 < ty && ty < 468)
        {
            tft.fillRoundRect(12, 433, 27, 35, 10, 0x9CF3);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("/\\", 25, 442, 4);
            mode++;
            if (mode == 3)
                mode = 0;
            while (isScreenTouched())
                ;
            drawForce(0);
            return 1;
        }
    }
    return 0;
}

bool Keyboard::isEnd()
{
    return 0;
}

String Keyboard::getString()
{
    return text;
}

void Keyboard::setString(String newString)
{
    text = newString;
}

#endif /* Keyboard_CPP */