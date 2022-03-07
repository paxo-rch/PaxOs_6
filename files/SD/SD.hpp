#ifndef SD_HPP
#define SD_HPP

#include <SD.h>

bool SD_init()
{
    if (!SD.begin(4))
    {
        return 1;
    }
    return 0;
}

bool SD_isConnected()
{
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

#endif