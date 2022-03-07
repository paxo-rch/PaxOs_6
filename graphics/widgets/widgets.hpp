#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include <stdint.h>
#include <vector>               // vector library
#include "../screen/screen.hpp" // graphics library

using namespace std;

typedef uint16_t color_t;
typedef byte TextAlignment;
#define LEFT_ALIGNMENT 0
#define RIGHT_ALIGNMENT 1
#define CENTER_ALIGNMENT 2

class GUI
{
public:
    //GUI(){}
    virtual ~GUI();

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void remove() = 0;

    void drawAll();

    void addWidget(GUI *widget);
    void removeAllWidgets();

    uint16_t getAbsoluteX() { if (parent != nullptr) return parent->getAbsoluteX() + parent->getMarginX() + getRelativeX() + getMarginX(); else return getRelativeX() + getMarginX();}
    uint16_t getAbsoluteY() { if (parent != nullptr) return parent->getAbsoluteY() + parent->getMarginY() + getRelativeY() + getMarginY(); else return getRelativeY() + getMarginY();}
    uint16_t getRelativeX() { return relativeX; }
    uint16_t getRelativeY() { return relativeY; }
    uint16_t getWidth() { return width; }
    uint16_t getHeight() { return height; }
    uint16_t getMarginX() { return marginX; }
    uint16_t getMarginY() { return marginY; }
    uint16_t getpaddingX() { return paddingX; }
    uint16_t getpaddingY() { return paddingY; }

    void setX(uint16_t value) { relativeX = value; }
    void setY(uint16_t value) { relativeY = value; }
    void setHeight(uint16_t value) { height = value; }
    void setWidth(uint16_t value) { width = value; }
    void setMarginX(uint16_t value) { marginX = value; }
    void setMarginY(uint16_t value) { marginX = value; }
    void setPaddingX(uint16_t value) { paddingX = value; }
    void setPaddingY(uint16_t value) { paddingY = value; }

    void setBackgroundColor(uint16_t color) { backgroundColor = color; }
    uint16_t getBackgroundColor() { return backgroundColor; }

    void setBorderColor(uint16_t color) { borderColor = color; }
    uint16_t getBorderColor() { return backgroundColor; }

    void setAlignment(TextAlignment alignment) { this->alignment = alignment; }
    TextAlignment getAlignment() { return alignment; }

    void setParent(GUI* parent) { this->parent = parent; }

    uint16_t width, height = 0;            // sizes
    uint16_t relativeX, relativeY = 0;     // placement
    uint16_t marginX, marginY = 0;         // margin
    uint16_t paddingX, paddingY = 0;       // padding
    uint16_t backgroundColor = 0xFFFF; // colors
    uint16_t borderColor = 0x0000;
    uint16_t borderSize = 1;                    // border size
    TextAlignment alignment = LEFT_ALIGNMENT; // alignment
protected:
    std::vector<GUI *> widgets; // vector of widgets
    GUI *parent = nullptr;      // parent widget
};

GUI::~GUI()
{
    for (int i = 0; i < widgets.size(); i++)
    {
        if (widgets[i] != nullptr)
            delete widgets[i];
    }
}

void GUI::drawAll()
{
    draw();
    for (int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i] != nullptr)
            widgets[i]->drawAll();
    }
}

void GUI::addWidget(GUI *widget)
{
    widgets.push_back(widget);
    widget->setParent(this);
}

void GUI::removeAllWidgets()
{
    for (int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i] != nullptr)
            delete widgets[i];
        widgets[i]=nullptr;
    }
    widgets.erase(widgets.begin(), widgets.begin() + widgets.size() - 1);
}

#include "widgets/window.hpp"
#include "widgets/label.hpp"
#include "widgets/keyboard.hpp"
#include "widgets/button.hpp"

#endif // WIDGETS_HPP