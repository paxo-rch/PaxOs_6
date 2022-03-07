#ifndef MESSAGE_UTILS_HPP
#define MESSAGE_UTILS_HPP

#include "../../files/files_manager.hpp"

class Message
{
    public:
    int getNumberConversation();
    String getNameOfConversation();
    String getConversation(int index);
    void writeMessage(String message, int index);
    void newConversation(String number, message);
    void saveMessage(String message, String number);

    private:
    String path = "/paxo/apps/messages/chat";
};

int Message::getNumberConversation()
{
    File directory = SD.open("/paxo/apps/messages/chat");
    int i = 0;
    File entry = directory.openNextFile();
    for (;entry;)
    {
        i++;
        entry.close();
        entry = directory.openNextFile();
    }
    directory.rewindDirectory();
    directory.close();
    return i;
}

String Message::getNameOfConversation()
{
    File root = SD.open("/paxo/apps/messages/chat");
    if (!root)
    {
        return "-1";
    }
    if (!root.isDirectory())
    {
        return "-1";
    }

    File file = root.openNextFile();

    for (int i = 0;file;i++)
    {
        if (!file.isDirectory())
        {
            if(i==index)
            {
                String str = readFile(file.name());
                String name = "";
                for(int j = 0;; j++)
                {
                    if(str[j] != ':')
                        name += str[j];
                    else
                        return name;
                }
            }
        }
        file = root.openNextFile();
    }
    return "-1";
}

String Message::getConversation(int index)
{
    File root = SD.open("/paxo/apps/messages/chat");
    if (!root)
    {
        return "-1";
    }
    if (!root.isDirectory())
    {
        return "-1";
    }

    File file = root.openNextFile();

    for (int i = 0;file;i++)
    {
        if (!file.isDirectory())
        {
            if(i==index)
                return readFile(file.name());
        }
        file = root.openNextFile();
    }
    return "-1";
}

void Message::writeMessage(String number, String message, bool whoSendTheMessage) // 0 = me ; 1 = other
{
    File root = SD.open("/paxo/apps/messages/chat");

    File file = root.openNextFile();

    for (int i = 0;file;i++)
    {
        if (!file.isDirectory())
        {
            if(i==index)
            {
                String str = readFile(file.name());
                String name = "";
                for(int j = 0;; j++)
                {
                    if(str[j] != ':')
                        name += str[j];
                    else
                        return name;
                }
                if(number==name)
                {
                    Serial.println("\nSave in " + file.name());
                    if(whoSendTheMessage==0)
                        appendFile(file.name(), "\n~MB~" + message + "~ME~"); // M = me | B = begin | E = end
                    if(whoSendTheMessage==1)
                        appendFile(file.name(), "\n~OB~" + message + "~OE~"); // O = other
                }
                return;
            }
        }
        file = root.openNextFile();
    }
}

void Message::newConversation(String number, message)
{

}

void Message::saveMessage(String message, String number)
{

}

Message SMS;

#endif