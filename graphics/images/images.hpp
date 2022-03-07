#ifndef IMAGE_PROGREM_HPP
#define IMAGE_PROGREM_HPP

#include "maj.c"
#include <SD.h>
#include "../../files/files_manager.hpp"

uint16_t read16(fs::File &f)
{
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t read32(fs::File &f)
{
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}

#define BUFFPIXEL 20

void bmpDrawSD(String filename, uint16_t x, uint16_t y)
{
    if(!SD_isConnected()) return;

    File bmpFile;
    int bmpWidth, bmpHeight;            // W+H in pixels
    uint8_t bmpDepth;                   // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;            // Start of image data in file
    uint32_t rowSize;                   // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel buffer (R+G+B per pixel)
    uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    boolean goodBmp = false;            // Set to true on valid header parse
    boolean flip = true;                // BMP is stored bottom-to-top
    int w, h, row, col;
    uint8_t r, g, b;
    uint32_t pos = 0, startTime = millis();

    if ((x >= tft.width()) || (y >= tft.height()))
        return;

    Serial.println();
    Serial.print(F("Loading image '"));
    Serial.print(filename);
    Serial.println('\'');

    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) == NULL)
    {
        Serial.print(F("File not found"));
        return;
    }

    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        Serial.print(F("File size: "));
        Serial.println(read32(bmpFile));
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        Serial.print(F("Image Offset: "));
        Serial.println(bmpImageoffset, DEC);
        // Read DIB header
        Serial.print(F("Header size: "));
        Serial.println(read32(bmpFile));
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);

        int SIZEBUFFER = 100; //bmpHeight;
        if (480 < SIZEBUFFER)
            SIZEBUFFER = bmpHeight;

        if (SIZEBUFFER > bmpHeight)
            SIZEBUFFER = bmpHeight;

        uint16_t *image = new uint16_t[bmpWidth * SIZEBUFFER];
        //uint16_t *image = (uint16_t *)ps_malloc(bmpWidth * SIZEBUFFER * sizeof(uint16_t));

        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            {

                goodBmp = true;

                rowSize = (bmpWidth * 3 + 3) & ~3;
                if (bmpHeight < 0)
                {
                    bmpHeight = -bmpHeight;
                    flip = false;
                }

                w = bmpWidth;
                h = bmpHeight;
                if ((x + w - 1) >= tft.width())
                    w = tft.width() - x;
                if ((y + h - 1) >= tft.height())
                    h = tft.height() - y;

                int counter = 0;

                for (row = 0; row < h; row++)
                {
                    if (flip)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    else
                        pos = bmpImageoffset + row * rowSize;
                    if (bmpFile.position() != pos)
                    {
                        bmpFile.seek(pos);
                        buffidx = sizeof(sdbuffer);
                    }

                    for (col = 0; col < w; col++)
                    {
                        if (buffidx >= sizeof(sdbuffer))
                        {
                            bmpFile.read(sdbuffer, sizeof(sdbuffer));
                            buffidx = 0;
                        }

                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];

                        image[(row - counter) * bmpWidth + col] = tft.color565(r, g, b);
                    }

                    if (row - SIZEBUFFER  + 1 == counter)
                    {
                        tft.setSwapBytes(true);
                        tft.pushImage(x, y + counter, bmpWidth, SIZEBUFFER, image);
                        counter = row + 1;
                    }
                    if (bmpHeight - row < SIZEBUFFER && row + 1 == bmpHeight)
                      tft.pushImage(x, y + counter, bmpWidth, bmpHeight - counter, image);
                }
            }
        }

        //delete[] image;
        free(image);
    }

    bmpFile.close();
    if (!goodBmp)
        Serial.println(F("BMP format not recognized."));
}

#endif