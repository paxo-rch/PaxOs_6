#ifndef HOME_CPP
#define HOME_CPP

#include "home.hpp"
#include "../../../system/tasks/system.hpp"


#define nb_app 5

#define BACKGROUND_COLOR 0x05DC

void HomeApp::run()
{
    loop();
}

void HomeApp::draw_gui()
{
    clearAllScreen(BACKGROUND_COLOR);

    byte apps_drawed = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tft.fillRoundRect(20 + j * 100, 50 + i * 120, 80, 80, 15, 0xFFFF);
            bmpDrawSD(applications[j + i * 3]->getLogo(), 25 + j * 100, 55 + i * 120);
            tft.setFreeFont(&FreeMono12pt7b);
            tft.setTextColor(0x0000);
            tft.drawCentreString(String(applications[j + i * 3]->getName()), 60 + j * 100, 130 + i * 120, 4);
            apps_drawed++;

            if (apps_drawed == nb_app)
                break;
        }
        if (apps_drawed == nb_app)
            break;
    }
    if(already_launched) return;
}

void HomeApp::loop()
{
    draw_gui();
    for(;1;)
    {
        if(forceReload)
        {
            draw_gui();
            forceReload=0;
        }
        while(1)
        {
            if(forceReload)
            {
                draw_gui();
                forceReload=0;
            }
            TFT_getTouch();
            byte apps_checked = 0;

            if (isScreenTouched())
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (20 + j * 100 < tx && tx < 100 + j * 100 && 50 + i * 120 < ty && ty < 130 + i * 120 && apps_checked < nb_app)
                        {
                            tft.fillRoundRect(20 + j * 100, 50 + i * 120, 80, 80, 20, 0x0000);
                            while (isScreenTouched())
                                ;
                            tft.fillRoundRect(20 + j * 100, 50 + i * 120, 80, 80, 20, 0xFFFF);
                            if (apps_checked < nb_app && applications[apps_checked] != nullptr)
                            {
                                disableScreenBar();
                                applications[apps_checked]->run();
                                enableScreenBar();
                                draw_gui();
                            }
                        }
                        apps_checked++;
                    }
                }
            }
        }
    } 
}
/*
String hexa = "0043006F00750063006F0075002000E70061002000760061003F";
Coucou 

char convertHexaToChar(String data)
{
  if(data.length()!=4)
    return 0;

  if(data.indexOf("00")!=-1)
  {
    data=data.substring(2,4);
    switch(data)
    {
        case "20":
            return ' ';
        break;
        case "21":
            return '!';
        break;
        case "22":
            return '"';
        break;
        case "23":
            return '#';
        break;
        case "24":
            return '$';
        break;
        case "25":
            return '%';
        break;
        case "26":
            return '&';
        break;
        case "27":
            return '\'';
        break;
        case "28" :
            return '(';
        break;
        case "29" :
            return ')';
        break;
        case "2A" :
            return '*';
        break;
        case "2B" :
            return '+';
        break;
        case "2C" :
            return ',';
        break;
        case "2D" :
            return '-';
        break;
        case "2E" :
            return '.';
        break;
        case "2F" :
            return '\/';
        break;
        case "30" :
            return '0';
        break;
        case "31" :
            return '1';
        break;
        case "32" :
            return '2';
        break;
        case "33" :
            return '3';
        break;
        case "34" :
            return '4';
        break;
        case "35" :
            return '5';
        break;
        case "36" :
            return '6';
        break;
        case "37" :
            return '7';
        break;
        case "38" :
            return '8';
        break;
        case "39" :
            return '9';
        break;
        case "3A":
            return ':';
        break;
        case "3B" :
            return ';';
        break;
        case "3C" :
            return '<';
        break;
        case "3D" :
            return '=';
        break;
        case "3E" :
            return '>';
        break;
        case "3F" :
            return '?';
        break;
        case "40":
            return '@'
        break;
        case "20":
            return ' ';
        break;
        case "21":
            return '!';
        break;
        case "41" :
            return 'A';
        break;
        case "42" :
            return 'B';
        break;
        case "43" :
            return 'C';
        break;
        case "44" :
            return 'D';
        break;
        case "45" :
            return 'E';
        break;
        case "46" :
            return 'F';
        break;
        case "47" :
            return 'G';
        break;
        case "48" :
            return 'H';
        break;
        case "49" :
            return 'I';
        break;
        case "4A" :
            return 'J';
        break;
        case "4B" :
            return 'K';
        break;
        case "4C" :
            return 'L';
        break;
        case "4D" :
            return 'M';
        break;
        case "4E" :
            return 'N';
        break;
        case "4F" :
            return 'O';
        break;
        case "50" :
            return 'P';
        break;
        case "51" :
            return 'Q';
        break;
        case "52" :
            return 'R';
        break;
        case "53" :
            return 'S';
        break;
        case "54" :
            return 'T';
        break;
        case "55" :
            return 'U';
        break;
        case "56" :
            return 'V';
        break;
        case "57" :
            return 'W';
        break;
        case "58" :
            return 'X';
        break;
        case "59" :
            return 'Y';
        break;
        case "5A" :
            return 'Z';
        break;
        case "5B" :
            return '['
        break;
        case "5C" :
            return '\\'
        break;
        case "5D" :
            return ']'
        break;
        case "5E" :
            return '^'
        break;
        case "5F" :
            return '_'
        break;
        case "60" :
            return '`'
        break;
        case "61":
            return 'a';
        break;
        case "62":
            return 'b';
        break;
        case "63":
            return 'c';
        break;
        case "64":
            return 'd';
        break;
        case "65":
            return 'e';
        break;
        case "66":
            return 'f';
        break;
        case "67":
            return 'g';
        break;
        case "68":
            return 'h';
        break;
        case "69":
            return 'i';
        break;
        case "6A":
            return 'j';
        break;
        case "6B":
            return 'k';
        break;
        case "6C":
            return 'l';
        break;
        case "6D":
            return 'm';
        break;
        case "6E":
            return 'n';
        break;
        case "6F":
            return 'o';
        break;
        case "70":
            return 'p';
        break;
        case "71":
            return 'q';
        break;
        case "72":
            return 'r';
        break;
        case "73":
            return 's';
        break;
        case "74":
            return 't';
        break;
        case "75":
            return 'u';
        break;
        case "76":
            return 'v';
        break;
        case "77":
            return 'w';
        break;
        case "78":
            return 'x';
        break;
        case "79":
            return 'y';
        break;
        case "7A":
            return 'z';
        break;
    }
}*/

#endif /* HOME_CPP */