#ifndef LABEL_HPP
#define LABEL_HPP

class Label : public GUI
{
public:
    Label(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    void draw();
    void update() { draw(); }
    void remove() {}

    void setText(String text) { this->text = text; }
    String getText() { return this->text; }
    void addText(String toAdd) { this->text += toAdd; }
    int getHeightOfText();
    void clearZone() { tft.fillRect(getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(), getBackgroundColor()); }

    void setTextColor(color_t textColor) { this->textColor = textColor; }
    color_t getTextColor() { return this->textColor; }

private:
    void drawText(String line, int counter);

    String text = "";
    color_t textColor = 0x0000;
};

#include "label.cpp"

#endif