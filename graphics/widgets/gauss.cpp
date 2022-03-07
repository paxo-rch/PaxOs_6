#ifndef GAUSS_CPP
#define GAUSS_CPP

#include "gauss.hpp"

void Gauss::~Gauss()
{
    for(int i = 0; i < children.size(); i++)
    {
        if(children[i] != nullptr)
            delete children[i];
    }
}

void Gauss::drawAll()
{
    draw();
    for (int i = 0; i < children.size(); i++)
    {
        if(children[i] != nullptr)
            children[i]->drawAll();
    }
}

void Gauss::addChild(Gauss *child)
{
    children.push_back(child);
    child->setParent(this);
}

void Gauss::removechildren()
{
    for (int i = 0; i < children.size(); i++)
    {
        if(children[i] != nullptr)
            delete children[i];
    }
    for (; children.size();)
    {
        children.erase(children.begin());
    }
}

void Gauss::setParent(Gauss *parent)
{
    this->parent = parent;
}

uint16_t Gauss::getX()
{
    return this->x;
}

uint16_t Gauss::getY()
{
    return this->y;
}

uint16_t Gauss::getWidth()
{
    return this->width;
}

uint16_t Gauss::getHeight()
{
    return this->height;
}

uint16_t Gauss::getAbsoluteX()
{
    if(parent==nullptr)
        return this->getMarginX() + x;
    else
        return parent->getAbsoluteX() + parent->getPaddingX() + this->getMarginX() + x;
}

uint16_t Gauss::getAbsoluteY()
{
    if(parent==nullptr)
        return this->getMarginY() + y;
    else
        return parent->getAbsoluteY() + parent->getPaddingY() + this->getMarginY() + y;
}

uint16_t Gauss::getMarginX()
{
    return this->marginX;
}

uint16_t Gauss::getMarginY()
{
    return this->marginY;
}

uint16_t Gauss::getPaddingX()
{
    return this->paddingX;
}

uint16_t Gauss::getPaddingY()
{
    return this->paddingY;
}

color_t Gauss::getColor()
{
    return this->color;
}

color_t Gauss::getBackgroundColor()
{
    return this->backgroundColor;
}

color_t Gauss::getBackgroundColor()
{
    return this->backgroundColor;
}

uint16_t Gauss::getBorderSize()
{
    return this->borderSize;
}

Alignment Gauss::getAlignment()
{
    return this->alignment;
}

void Gauss::setX(uint16_t x)
{
    this->x=x;
}

void Gauss::setY(uint16_t y)
{
    this->y=y;
}

void Gauss::setWidth(uint16_t width)
{
    this->width=width;
}

void Gauss::setHeight(uint16_t height)
{
    this->height=height;
}

void Gauss::setMarginX(uint16_t marginX)
{
    this->marginX=marginX;
}

void Gauss::setMarginY(uint16_t marginY)
{
    this->marginY=marginY;
}

void Gauss::setPaddingX(uint16_t paddingX)
{
    this->paddingX=paddingX;
}

void Gauss::setPaddingY(uint16_t setPaddingY)
{
    this->paddingY=paddingY;
}

void Gauss::setColor(color_t color)
{
    this->color=color;
}

void Gauss::setBackgroundColor(color_t backgroundColor)
{
    this->backgroundColor=backgroundColor;
}

void Gauss::setBorderColor(color_t setBorderColor)
{
    this->borderColor=borderColor;
}

void Gauss::setBorderSize(uint16_t borderSize)
{
    this->borderSize=borderSize;
}

void Gauss::setTheme(byte theme)
{
    color = color_theme[theme][0];
    backgroundColor = color_theme[theme][1];
    borderColor = color_theme[theme][2];

    for(int i = 0; i < children.length(); i++)
    {
        if(children[i]!=nullptr)
            children[i]->setTheme(theme);
    }

    drawAll();
}

void Gauss::setAlignment(Alignment alignment)
{
    this->alignment=alignment;
}

void Gauss::setRadius(uint16_t radius)
{
    this->radius=radius;
}


#endif