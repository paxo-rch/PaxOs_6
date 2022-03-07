#ifndef APP_MESSAGE_HPP
#define APP_MESSAGE_HPP

#include "../../../graphics/graphics.hpp"
#include "../../../files/files_manager.hpp"

class AppMessage : public App
{
    public:
    String getName() { return "message"; }
    String getLogo() { return "/paxo/apps/messages/logo.bmp"; };
    void run();
    void restore(){}
    void quit(){}

    void home();
    void contact();
    void conversation(int index);
    String getContact(String number); // 06.... format

    private:
    String adress = "/paxo/apps/message/";
    Window* gui = new Window();
};

#include "message.cpp"

#endif