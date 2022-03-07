#ifndef Keyboard_HPP
#define Keyboard_HPP

#include "../../screen/screen.hpp"
#include "../widgets.hpp"
//#include "../../images/images.hpp"

class Keyboard : public GUI
{
public:
    Keyboard(uint16_t textColor, uint16_t backgroundColor);
    Keyboard(){}

    void update(){ draw(); }
    void remove(){}

    bool isTouch();

    void draw();
    void drawForce(bool all);

    bool isEnd();

    String getString();

    void setString(String newString);

    void setMode(byte mode){ this->mode = mode;}

private:
    char *alphabet[3][3] =
        {
            {
             {"azertyuiop"},
             {"qsdfghjklm"},
             {",.wxcvbn!?"}
            },
            {
             {"AZERTYUIOP"},
             {"QSDFGHJKLM"},
             {"',WXCVBN.?"}
            },
            {
             {"1234567890"},
             {"-/:;()$&@\""},
             {".,?!'*+-=~"}
            }
        };

    String text;
    uint8_t mode = 0;
    uint16_t textColor = 0x0000;
    uint16_t backgroundColor = 0xFFFF;
    bool alreadyDrawed = false;
};

#include "keyboard.cpp"

#endif /* Keyboard_HPP */