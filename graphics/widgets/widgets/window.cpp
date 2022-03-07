#ifndef GUI_WINDOW_CPP
#define GUI_WINDOW_CPP

#include "../../screen/screen.hpp"

#include "window.hpp"

void Window::draw()
{
    paddingY = 25;
    tft.fillRect(getAbsoluteX() + getpaddingX(), getAbsoluteY() + getpaddingY(), getWidth(), getHeight(), getBackgroundColor());
}

void Window::update()
{

}

void Window::remove()
{

}

#endif