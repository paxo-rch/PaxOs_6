#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "../../../graphics/graphics.hpp"


/***************************************************************/

class CalculatorApp : public App
{
public:
    String getName() { return "calculator"; }
    String getLogo() { return "/paxo/apps/calculator/logo.bmp"; };
    void run();
    void restore(){};
    void quit();

    void buildGui();
private:
    Window* gui = new Window();
};

void CalculatorApp::quit()
{
}

#include "calculator.cpp"


#endif