#ifndef LABEL_CPP
#define LABEL_CPP

#include "label.hpp"
#include "../../screen/screen.hpp"

Label::Label(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    setX(x);
    setY(y);
    setHeight(height);
    setWidth(width);
    setMarginX(0);
    setMarginY(0);
    setPaddingX(0);
    setPaddingY(0);
}

void Label::drawText(String line, int counter)
{
    tft.setTextColor(textColor);
    switch (alignment)
    {
    case LEFT_ALIGNMENT:
        tft.setTextDatum(TL_DATUM);
        tft.drawString(line, getAbsoluteX(), getAbsoluteY() + (tft.fontHeight() + 5) * counter , 4);
        break;
    case RIGHT_ALIGNMENT:
        tft.setTextDatum(TR_DATUM);
        tft.drawString(line, getAbsoluteX() + width, getAbsoluteY() + (tft.fontHeight() + 5) * counter , 4);
        break;
    case CENTER_ALIGNMENT:
        tft.setTextDatum(TC_DATUM);
        tft.drawCentreString(line, getAbsoluteX() + width/2, getAbsoluteY() + (tft.fontHeight() + 5) * counter , 4);
        break;
    }
}

/*void Label::draw()
{
    String line = "";
    int lineCounter = 0;
    tft.setTextColor(0x0000);
    tft.setFreeFont(&FreeMono12pt7b);

    for (int i = 0; i < text.length(); i++)
    {
        for(int li = 0; tft.textWidth(line) < width && i < text.length(); i++)
        {
            line += text[i];
            if(line[li] == '\n')
            {
                line = line.substring(0, line.length() - 1);
                break;
            }
            li++;
        }

        String mem = line;

        for(;line.length() > 0 && text[i] != ' ' && text[i] != '\n' && i < text.length(); i--)
        {
            line = line.substring(0, line.length() - 1);
        }

        if(line.length() == 0)
        {
            line = mem;
            i+=mem.length();
        }
        
        drawText(line, lineCounter);
        line = "";
        lineCounter++;
    }
}*/

void Label::draw()
{
    int lineCounter = 0;
    int actualIndex = 0;
    String line = "";
    String txt = text;

    while(actualIndex < txt.length())
    {
        while(actualIndex < txt.length() && tft.textWidth(line) < width)
        {
            line+=txt[actualIndex];
            actualIndex++;

            if(txt[actualIndex]=='\n')
                break;
        }
        if(actualIndex < txt.length() && txt[actualIndex]!='\n' && line.length() != 0 && line.indexOf(" "))
        {
            while(actualIndex < txt.length() && line[line.length()-1]!=' ')
            {
                actualIndex--;
                line=line.substring(0, line.length() - 1);
            }
            lineCounter++;
        }
        else
        {
            lineCounter++;
        }
        drawText(line, lineCounter-1);
        txt=txt.substring(actualIndex, txt.length());
        actualIndex=0;
        line="";
    }
}

int Label::getHeightOfText()
{
    String line = "";
    int lineCounter = 0;
    tft.setTextColor(0x0000);
    tft.setFreeFont(&FreeMono12pt7b);

    for (int i = 0; i < text.length(); i++)
    {
        for(int li = 0; tft.textWidth(line) < width && i < text.length(); i++)
        {
            line += text[i];
            if(line[li] == '\n')
            {
                line = line.substring(0, line.length() - 1);
                break;
            }
            li++;
        }

        String mem = line;

        for(;line.length() > 0 && text[i] != ' ' && text[i] != '\n' && i < text.length(); i--)
        {
            line = line.substring(0, line.length() - 1);
        }

        if(line.length() == 0)
        {
            line = mem;
            i+=mem.length();
        }
        
        line = "";
        lineCounter++;
    }
    return (tft.fontHeight() + 5) * lineCounter;
}

#endif