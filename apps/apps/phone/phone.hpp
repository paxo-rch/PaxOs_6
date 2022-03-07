#ifndef PHONE_APP_HPP
#define PHONE_APP_HPP

#include "../../../graphics/graphics.hpp"

class AppPhone : public App
{
    public:
    String getName() { return "phone"; }
    String getLogo() { return "/paxo/apps/phone/logo.bmp"; };
    void run();
    void restore(){}
    void quit(){}

    bool call(String bruteNumber);

    void drawGui();

    private:
    String lastNumber = "";
};

#include "phone.cpp"

#endif // PHONE_APP_HPP