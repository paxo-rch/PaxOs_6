#ifndef WIDGET_BUTTON_HPP
#define WIDGET_BUTTON_HPP

class NewButton : public Gauss
{
    public:
    void draw();
    void update();
    bool isFocuced();

    bool isPressed();
    bool isReleased();

    private:
    String text = "";
};

void NewButton::draw()
{
    
}

#endif