#ifndef CALCULATOR_CPP
#define CALCULATOR_CPP

#include "calculator.hpp"
#include <tinyexpr.h> // mathematics library


void CalculatorApp::run()
{
    buildGui();
}

void CalculatorApp::buildGui()
{
    clearAllScreen(0xFFFF);
    Label* label = new Label(10, 30, 300, 100);
    label->setText("entrez le calcul");
    label->setAlignment(CENTER_ALIGNMENT);
    Keyboard* keyboard = new Keyboard();
    keyboard->setMode(2);
    Button calculate(240, 270, 150, 40);
    calculate.setText("calculer");
    calculate.setBackgroundColor(0xBDD7);
    calculate.draw();
    Button clearAll(80, 270, 150, 40);
    clearAll.setText("effacer");
    clearAll.setBackgroundColor(0xBDD7);
    clearAll.draw();

    gui->addWidget(label);
    gui->addWidget(keyboard);

    keyboard->draw();
    label->draw();
    while (1)
    {
        if(keyboard->isTouch())
        {
            label->setText(keyboard->getString());
            label->clearZone();
            gui->drawAll();
        }
        if(calculate.isReleased())
        {
            String str = keyboard->getString();
            if(str.length()!=0)
            {
                char * chr =(char *) malloc(str.length());
                strcpy(chr, str.c_str());
                str = String(te_interp(chr, 0));
                label->setText("= "+str);
                label->clearZone();
                gui->drawAll();
            }
        }
        if(clearAll.isReleased())
        {
            String str = keyboard->getString();
            label->setText("");
            label->clearZone();
            keyboard->setString("");
            gui->drawAll();
        }
    }
    gui->removeAllWidgets();
}

#endif