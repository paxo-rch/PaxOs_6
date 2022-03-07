#ifndef PHONE_HPP
#define PHONE_HPP

#include "Sim800L.h"
#include <SoftwareSerial.h>
#include "../../graphics/graphics.hpp"
#include "../../system/tasks/system.hpp"
#include "button.hpp"
//#include "messages.hpp"

#define RX 26
#define TX 27

Sim800L SIM(RX, TX);

namespace PHONE
{
    String buffer_sim = "";
    byte check_news();
    void receive_call();
}

byte numberNotificationNewMessage = 0;

void newNotificationNewMessage()
{
    numberNotificationNewMessage++;
}

void clearNotificationNewMessage()
{
    numberNotificationNewMessage=0;
}

byte getNotificationNewMessage()
{
    return numberNotificationNewMessage;
}

void saveNewMessage(String number, String message)
{
    Serial.println("number: " + number);
    File root = SD.open("/paxo/apps/messages/chat");
    File file = root.openNextFile();
    int number_file = 0;
    for (int i = 0;file;i++)
    {
        if (!file.isDirectory())
        {
            number_file++;
            String str = readFile(file.name());
            String name = "";
            for(int j = 0;; j++)
            {
                if(str[j] != ':')
                    name += str[j];
                else
                {
                    if(name.indexOf(number.substring(3, number.length()))!=-1)
                    {
                        Serial.println("name=" + name + "\nnumber=" + number);
                        appendFile(file.name(), "\n~OB~" + message + "  ~OE~");
                        Serial.println("write in the "+String(number_file) +" file");
                        newNotificationNewMessage();
                        return;
                    }
                    break;
                }
            }
        }
        file = root.openNextFile();
    }
    Serial.println("write a new file: "+String(number_file)+" file");
    writeFile("/paxo/apps/messages/chat/" + String(number_file+1) + ".txt", "0"+number.substring(3, number.length())+ ":" + "\n~OB~" + message + "~OE~\n");
    newNotificationNewMessage();
}

byte PHONE::check_news()
{
    if (!SIM.available())
        return 0;
    for (; SIM.available();)
    {
        buffer_sim += char(SIM.read());
    }

    if (buffer_sim.indexOf("RING") != -1) // new call
    {
        buffer_sim = "";
        SIM.print("AT+CLCC\r\n");
        delay(100);
        for (; SIM.available();)
            buffer_sim += char(SIM.read());
        Serial.println(buffer_sim);
        String number = buffer_sim.substring(28, 40); // get the phone number
        clearAllScreen(0x0000);
        tft.setTextColor(0xFFFF);
        tft.drawCentreString(number, 160, 40, 4);
        tft.fillRoundRect(170, 400, 140, 70, 15, 0xB9A6);
        tft.fillRoundRect(10, 400, 140, 70, 15, 0x45E6);

        if (System::isStandbyON())
            System::standbyOFF();

        while (1)
        {
            if (isScreenTouched())
            {
                if (170 < tx && tx < 310 && 400 < ty && ty < 470)
                {
                    SIM.print("ATH\r\n");
                    forceReload = 1;
                    return 0;
                }
                if (10 < tx && tx < 150 && 400 < ty && ty < 470)
                {
                    SIM.print("ATA\r\n");
                    buffer_sim = "";
                    break;
                }
            }
        }
        for (int i = 0; i < 165; i += 5)
            tft.fillRoundRect(170 - i, 400, 140, 70, 15, 0xB9A6);
        while (1)
        {
            if (isButtonPressed() || (isScreenTouched() && 10 < tx && tx < 310 && 400 < ty && ty < 470))
            {
                SIM.print("ATH\r\n");
                forceReload = 1;
                return 0;
            }
        }
        buffer_sim = "";
    }

    if (buffer_sim.indexOf("+CMTI:") != -1) // new message
    {
        Serial.println("Nouveau message");
        buffer_sim = "";
        /*while (SIM.read() != '\n') // wait endline
            ;*/
        SIM.print("AT+CMGF=1\r\n"); // enable SMS mode
        /*while (SIM.read() != 'K') // wait SIM800 SMS mode enable
            ;*/
        delay(100);
        while(SIM.available()) 
            SIM.read();
        buffer_sim = "";
        SIM.print("AT+CMGL=\"REC UNREAD\"\r\n"); //  ask new messages

        while(buffer_sim.indexOf("OK")==-1) // wait Sim800 send all new messages
        {
            if(SIM.available())
            {
                buffer_sim+=(char)SIM.read();
            }
        }

        

        while(buffer_sim.indexOf("+CMGL:") != -1) // repeat for all messages
        {
            //Serial.println(buffer_sim);
            buffer_sim=buffer_sim.substring(buffer_sim.indexOf("+CMGL:") + 10,buffer_sim.length()); // cursor on phone number
            while(1)
            {
                if(buffer_sim[0] == '+')
                    break;
                buffer_sim = buffer_sim.substring(1, buffer_sim.length());
            }
            String number = "";
            while(buffer_sim[0] != '"')
            {
                number+=char(buffer_sim[0]);
                buffer_sim = buffer_sim.substring(1, buffer_sim.length());
            }
            while (buffer_sim[0] != '\n')
            {
                buffer_sim = buffer_sim.substring(1, buffer_sim.length());
            }
            buffer_sim = buffer_sim.substring(1, buffer_sim.length());
            String message = "";
            while(message.indexOf("OK")==-1)
            {
                message+=char(buffer_sim[0]);
                buffer_sim = buffer_sim.substring(1, buffer_sim.length());
            }
            message = message.substring(0, message.length()-6);
            saveNewMessage(number, message);
        }
        buffer_sim = "";
        SIM.print("AT+CMGD=1,4\r\n");
    }
}

#endif /* PHONE_HPP */