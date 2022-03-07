/* GUI SYSTEM */

#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "screen/screen.hpp" // graphics library
#include <vector>

typedef uint16_t color_t;
typedef byte Alignment;

#define CONTROL_BAR_SIZE 25

class Gauss // widget system
{
    public:
    //Gauss(); // constructor
    ~Gauss();

    virtual void draw();        // draw objet
    virtual void update();      // update objet
    virtual bool isFocuced();   // return true if is touched

    void drawAll();             // draw all childs
    void addChild(Gauss *child);// add child
    void removeChilds();        // remove all children
    void setParent(Gauss *parent);  // set parent

    uint16_t getX();            // get relative x
    uint16_t getY();            // get relative y
    uint16_t getWidth();        // get width
    uint16_t getHeight();       // get height

    uint16_t getAbsoluteX();    // get absolute x
    uint16_t getAbsoluteY();    // get absolute y

    uint16_t getMarginX();      // get margin x
    uint16_t getMarginY();      // get margin y

    uint16_t getPaddingX();     // get padding x
    uint16_t getPaddingY();     // get padding y

    color_t getColor();         // get color
    color_t getBackgroundColor();   // get background color
    color_t getBorderColor();   // get border color

    uint16_t getBorderSize();   // get border size

    Alignment getAlignment(); // get alignment


    void setX(uint16_t x); // set relative x
    void setY(uint16_t y); // set relative y
    void setWidth(uint16_t width)   // set width
    void setHeight(uint16_t height) // set height

    void setMarginX(uint16_t marginX);  // set margin x
    void setMarginY(uint16_t marginY);  // set margin y

    void setPaddingX(uint16_t paddingX);// set padding x
    void setPaddingY(uint16_t paddingY);// set padding y

    void setColor(color_t color);
    void setBackgroundColor(color_t backgroundColor);
    void setBorderColor(color_t borderColor);

    void setBorderSize(uint16_t borderSize); // set border size

    void setTheme(byte theme);

    void setAlignment(uint16_t alignment); // set alignment

    void setRadius(uint16_t radius); // set radius

    private:
    uint16_t x, y = 0;                      // position
    uint16_t width, height = 0;             // sizes
    uint16_t marginX, marginY = 0;          // margin
    uint16_t paddingX, paddingY = 0;        // padding

    color_t color = color_theme[DEFAULT_THEME][0];
    color_t backgroundColor = color_theme[DEFAULT_THEME][1];
    color_t borderColor = color_theme[DEFAULT_THEME][2];

    uint16_t borderSize = DEFAULT_BORDER_SIZE;

    Alignment alignment = DEFAULT_ALIGNEMENT;

    uint16_t radius = DEFAULT_RADIUS;


    protected:
    std::vector<Gauss *> children;
    Gauss *parent = nullptr;
};

#include "gauss.cpp"

#include "gauss/button.hpp"

#endif /* GAUSS_HPP */