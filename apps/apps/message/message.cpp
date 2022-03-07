#ifndef APP_MESSAGE_CPP
#define APP_MESSAGE_CPP

#define SIZE_SPACE_MESSAGE 40

#include "message.hpp"

void AppMessage::run()
{
    home();
}

void AppMessage::home()
{
    while (true)
    {
        clearAllScreen(0xFFFF);
        tft.drawFastHLine(0, 99, 320, 0x0000);
        tft.setTextColor(0x0000);
        tft.drawCentreString(getName(), 160, 40, 4);
        tft.drawFastVLine(160, 100, 480, 0x0000);

        File root = SD.open("/paxo/apps/messages/chat");
        File file = root.openNextFile();

        int conversation_number = 0;

        for (int i = 0;file;i++)
        {
            if (!file.isDirectory())
            {
                String str = readFile(file.name());
                String name = "";
                for(int j = 0;; j++)
                {
                    if(str[j] != ':')
                        name += str[j];
                    else
                    {
                        tft.drawFastHLine(0, 100 + i * SIZE_SPACE_MESSAGE, 320, 0x0000);
                        tft.setTextColor(0x5C9F);
                        tft.drawCentreString(name, 240, 100 + SIZE_SPACE_MESSAGE/4 + i * SIZE_SPACE_MESSAGE, 4);
                        String contact = getContact(name);
                        if(contact != "-1")
                            tft.drawCentreString(contact, 80, 100 + SIZE_SPACE_MESSAGE/4 + i * SIZE_SPACE_MESSAGE, 4);
                        conversation_number++;
                        break;
                    }
                }
            }
            file = root.openNextFile();
        }
        while (true)
        {
            if(isScreenTouched())
            {
                TFT_getTouch();
                
                bool quit = 0;
                for(int i = 0; i<conversation_number; i++)
                {
                    if(100 + (i * SIZE_SPACE_MESSAGE) < ty && ty < 100 + SIZE_SPACE_MESSAGE + (i * SIZE_SPACE_MESSAGE))
                    {
                        conversation(i);
                        quit = 1;
                    }
                }
                if(quit) break;
            }
        }
    }
}

void AppMessage::contact()
{

}

void AppMessage::conversation(int index)
{
    while(1)
    {
        clearAllScreen(0xFFFF);
        tft.setTextColor(0x0000);

        String str = "";
        String phoneNumber = "";

        File root = SD.open("/paxo/apps/messages/chat");
        File file = root.openNextFile();

        for (int i = 0;file;i++)
        {
            if (!file.isDirectory() && i == index)
            {
                String brute_str = readFile(file.name());
                phoneNumber = brute_str.substring(0, brute_str.indexOf(':'));
                str = brute_str.substring(brute_str.indexOf(':') + 1, brute_str.length());
                break;
            }
            file = root.openNextFile();
        }

        Serial.print("\n"+str);

        String conversation = "";
        String buffer_="";

        int pixel_counter = 265;

        for (int i = str.length()-1; i > 0; i--) // parse the file
        {
            buffer_ = str[i] + buffer_;
            if(buffer_.indexOf("~MB~") != -1)
            {
                buffer_ = buffer_.substring(4, buffer_.length()-5);
                Label* bull = new Label(145, 40 + pixel_counter, 180, 40);
                bull->setText(buffer_);
                bull->setTextColor(0xFFFF);
                int sizeOfBull = bull->getHeightOfText();
                pixel_counter-=sizeOfBull;
                bull->setY(pixel_counter + 2);
                if(pixel_counter > 40)
                {
                    tft.fillRoundRect(135, pixel_counter, 180, sizeOfBull, 7, 0x24A7);
                    bull->setBackgroundColor(0x6CDE);
                    bull->draw();
                    pixel_counter -= 5;
                    buffer_="";
                    delete bull;
                }
                else
                    break;
            }
            if(buffer_.indexOf("~OB~") != -1)
            {
                buffer_ = buffer_.substring(4, buffer_.length()-5);
                Label* bull = new Label(10, 40 + pixel_counter, 180, 40);
                bull->setText(buffer_);
                bull->setTextColor(0xFFFF);
                int sizeOfBull = bull->getHeightOfText();
                pixel_counter-=sizeOfBull;
                bull->setY(pixel_counter + 2);
                if(pixel_counter > 40)
                {
                    tft.fillRoundRect(5, pixel_counter, 180, sizeOfBull, 7, 0x1AD7);
                    bull->setBackgroundColor(0x6CDE);
                    bull->draw();
                    pixel_counter -= 5;
                    buffer_="";
                    delete bull;
                }
                else
                    break;
            }
        }

        Keyboard keyboard;
        keyboard.draw();
        tft.drawRoundRect(5, 270, 310, 35, 15, 0xA514);
        tft.fillCircle(297, 287, 15, 0x3D81);
        Label toSend(10, 275, 260, 35);

        while (1)
        {
            if(keyboard.isTouch())
            {
                toSend.setText(keyboard.getString());
                toSend.clearZone();
                toSend.draw();
                tft.drawRoundRect(5, 270, 310, 35, 15, 0xA514);
            }
            if(isScreenTouched())
            {
                TFT_getTouch();
                if(282<tx && tx<312 && 272<ty && ty<302) // send the message
                {
                    phoneNumber = "+33" + phoneNumber.substring(1, phoneNumber.length());
                    
                    SIM.println("AT+CMGF=1");
                    delay(100);
                    SIM.println("AT+CMGS=\"" + phoneNumber + "\"\r");
                    delay(100);
                    SIM.print(toSend.getText());
                    SIM.print('\r');
                    delay(100);
                    SIM.write(char(26));
                    SIM.println('\r');
                    delay(100);
                    Serial.println("Send!");
                    appendFile(file.name(), "~MB~"+toSend.getText()+"~ME~\n");
                    break;
                }
            }
            if(getNotificationNewMessage())
            {
                clearNotificationNewMessage();
                break;
            }
        }
    }
}

String AppMessage::getContact(String number)
{
    String str = readFile("/paxo/apps/messages/contacts.txt");
    int index = str.indexOf(number);
    if(index == -1) 
        return "-1";
    String contact = "";
    for(; str[index-1] != ':'; index++);
    for(; str[index] != '\n'; index++)
        contact+=str[index];
    return contact;
}

#endif