#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

class Window : public GUI
{
    void draw();
    void update();
    void remove();
};

#include "window.cpp"

#endif