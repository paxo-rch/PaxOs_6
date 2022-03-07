#ifndef BUTTON_WIDGET_HPP
#define BUTTON_WIDGET_HPP

#include "../widgets.hpp"
#include "../../screen/screen.hpp"


class Button : public GUI
{
    public:
    Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    void draw();
    void update() { draw(); }
    void remove() {}

    void setText(String text) { this->text = text; }
    String getText() { return this->text; }

    void setTextColor(color_t textColor) { this->textColor = textColor; }
    color_t getTextColor() { return this->textColor; }

    bool isPressed();
    bool isReleased();

    private:
    String text = "";
    color_t textColor = 0x0000;
    byte touched = 0;
};

Button::Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
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

void Button::draw()
{
    tft.fillRoundRect(getAbsoluteX() - getWidth()/2, getAbsoluteY() - getHeight()/2, getWidth(), getHeight(), 15, backgroundColor);
    tft.drawRoundRect(getAbsoluteX() - getWidth()/2, getAbsoluteY() - getHeight()/2, getWidth(), getHeight(), 15, borderColor);
    tft.setTextColor(textColor);
    tft.drawCentreString(text, getAbsoluteX(), getAbsoluteY() - tft.fontHeight()/2, 4);
}

bool Button::isPressed()
{
    TFT_getTouch();
    bool buttonState = (isScreenTouched() && getAbsoluteX() - getWidth()/2 < tx && tx < getAbsoluteX() + getWidth()/2 && getAbsoluteY() - getHeight()/2 < ty && ty < getAbsoluteY() + getHeight()/2);
    if(buttonState == 1 && touched == 0) // 0=false  2=touched sut not drawed 3=touched and drawed 4=released
        touched = 2;
    if(touched == 3 && buttonState == 0)
        touched = 4;
    return buttonState;
}

bool Button::isReleased()
{
    
    if(isPressed() && touched == 2)
    {
        tft.fillRoundRect(getAbsoluteX() - getWidth()/2, getAbsoluteY() - getHeight()/2, getWidth(), getHeight(), 15, 0x0000);
        tft.drawRoundRect(getAbsoluteX() - getWidth()/2, getAbsoluteY() - getHeight()/2, getWidth(), getHeight(), 15, borderColor);
        tft.setTextColor(0xFFFF);
        tft.drawCentreString(text, getAbsoluteX(), getAbsoluteY()- tft.fontHeight()/2, 4);
        touched=3;
    }

    if (touched == 4)
    {
        touched = 0;
        draw();
        return 1;
    }
    return 0;
}

#endif