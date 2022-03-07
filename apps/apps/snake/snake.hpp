#ifndef AppSnake_HPP
#define AppSnake_HPP

#include "../../app_manager/apps_manager.hpp"

#include "../../../graphics/graphics.hpp"

#define SNAKE_X snake[0][1] * 10
#define SNAKE_Y snake[0][0] * 10

class AppSnake : public App
{
public:
    String getName() { return "snake"; }
    String getLogo() { return "/paxo/apps/snake/logo.bmp"; }
    void run();
    void restore(){}
    void quit(){}

private:
    short difference(short a, short b);
};

short AppSnake::difference(short a, short b)
{
    if (b > a)
        return b - a;
    else
        return a - b;
}

void AppSnake::run()
{
    while(1)
    {
        uint16_t snake_color = 0xFFFF;
        uint16_t background_color = 0x0000;

        clearAllScreen(background_color);
        tft.drawRect(9, 39, 302, 402, 0xFFFF);
        byte snake[200][2] = {254};   // create snake board of 200 cubes (254 is out of screen)
        snake[0][1] = 24;           // init position of snake
        snake[0][0] = 16;
        int level = 7;              // init level to 4
        int speed = 300;           // init speed in milliseconds | ex: 100 = 1 cube / second ; 200 = 2 cube / second
        byte pointxy[2];       // init the point at randoms points
        pointxy[0] = random(1, 31);
        pointxy[1] = random(4, 40);
        uint16_t pointColor = tft.color565(random(100, 255), random(100, 255), random(100, 255));
        tft.fillRoundRect(pointxy[0]*10, pointxy[1]*10, 10, 10, 3, pointColor);
        long snakeTimer = millis();   // init the timer
        byte direction = 1;         // 1=right 2=under 3=left 4=up
        byte direction_ = 1;
        bool gameover = 0;
        byte interprete = false;

        while(!gameover)
        {
            if (millis() > snakeTimer + 100000/speed)
            {
                for (byte i = level; i != 0; i--)
                {
                    snake[i][1] = snake[i - 1][1];
                    snake[i][0] = snake[i - 1][0];
                }

                if(direction != direction_ && interprete == 1)
                {
                    direction = direction_;
                    interprete = 2;
                }
                    

                if (direction == 1)
                    snake[0][0]++;
                if (direction == 3)
                    snake[0][0]--;
                if (direction == 2)
                    snake[0][1]++;
                if (direction == 4)
                    snake[0][1]--;

                tft.fillRect(snake[0][0] * 10, snake[0][1] * 10, 10, 10, snake_color);
                tft.fillRect(snake[level - 1][0] * 10, snake[level - 1][1] * 10, 10, 10, background_color);

                // detect collision

                for (int i = 1; i < level; i++)
                {
                    if (snake[i][0] == snake[0][0]  && snake[i][1] == snake[0][1] && snake) // gameover
                    {
                        gameover = true;
                        tft.fillRect(snake[0][0] * 10, snake[0][1] * 10, 10, 10, 0xD820);

                        while(isScreenTouched());
                        while(!isScreenTouched());
                    }
                }

                if(snake[0][0] == pointxy[0] && snake[0][1] == pointxy[1]) // get point
                {
                    pointxy[0] = random(1, 31);
                    pointxy[1] = random(4, 40);
                    
                    level++;
                    speed+=10;
                    snake_color = pointColor;

                    tft.setTextColor(0x0000);
                    tft.drawCentreString("score = " + String(level-8), 160, 460, 4);
                    tft.setTextColor(0xFFFF);
                    tft.drawCentreString("score = " + String(level-7), 160, 460, 4);
                    
                    pointColor = tft.color565(random(100, 255), random(100, 255), random(100, 255));
                }
                
                tft.fillRoundRect(pointxy[0]*10, pointxy[1]*10, 10, 10, 3, pointColor);


                if (1 > snake[0][0] || snake[0][0] > 30 || 4 > snake[0][1] || snake[0][1] > 43)
                {
                    gameover = true;
                    tft.fillRect(snake[0][0] * 10, snake[0][1] * 10, 10, 10, 0xD820);
                    while(isScreenTouched());
                    while(!isScreenTouched());
                }

                snakeTimer = millis();
            }

            if (isScreenTouched())
            {
                TFT_getTouch(); // get new pos

                if(interprete == 0 || interprete == 1)
                {
                    if(direction == 1 || direction == 3)
                    {
                        if(snake[0][1] < ty/10)
                            direction_ = 2;
                        else
                            direction_ = 4;
                    }

                    if(direction == 2 || direction == 4)
                    {
                        if(snake[0][0] < tx/10)
                            direction_ = 1;
                        else
                            direction_ = 3;
                    }
                    interprete = 1;
                }
                
            }
            else if(interprete == 2)
                interprete = 0;
        }
    }
}


/*void AppSnake::run()
{
    while (1)
    {
        uint16_t tx, ty;
        clearAllScreen(0xFFFF);
        tft.drawRect(9, 39, 302, 432, 0x0000);
        byte snake[100][2] = {0};
        byte head = 0;
        byte deriere = 0;
        bool point = true;
        byte pointxy[2] = {0, 0};
        short speed;
        bool gameover = false;
        long chrono_snake = millis();
        snake[0][1] = 16;
        snake[0][0] = 24;
        byte direc = 2;
        int score = 5;
        pointxy[0] = random(2, 30);
        pointxy[1] = random(5, 46);
        tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
        
        while (gameover == false)
        {
            tft.getTouch(&tx, &ty);
            if (score < 20)
            {
                speed = score/2;
            }
            if (millis() - 300 > chrono_snake - speed * 10)
            {
                for (byte i = score; i != 0; i--)
                {
                    snake[i][1] = snake[i - 1][1];
                    snake[i][0] = snake[i - 1][0];
                }

                tft.getTouch(&tx, &ty);
                if (isScreenTouched())
                {
                    tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
                    byte mem = direc;
                    if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X < tx)
                        direc = 1;

                    else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y < ty)
                        direc = 2;

                    else if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X > tx)
                        direc = 3;

                    else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y > ty)
                        direc = 4;
                    if (mem == 1 && direc == 3)
                        direc = 1;
                    if (mem == 2 && direc == 4)
                        direc = 2;
                    if (mem == 3 && direc == 1)
                        direc = 3;
                    if (mem == 4 && direc == 2)
                        direc = 4;
                }
                if (direc == 1)
                    snake[0][1]++;
                if (direc == 3)
                    snake[0][1]--;
                if (direc == 2)
                    snake[0][0]++;
                if (direc == 4)
                    snake[0][0]--;

                tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 10, 10, 0x0000);
                tft.fillRect(snake[score - 1][1] * 10, snake[score - 1][0] * 10, 10, 10, 0xFFFF);
                chrono_snake = millis();
            }
            tft.getTouch(&tx, &ty);
            if (isScreenTouched())
            {
                tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
                byte mem = direc;
                if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X < tx)
                    direc = 1;

                else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y < ty)
                    direc = 2;

                else if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X > tx)
                    direc = 3;

                else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y > ty)
                    direc = 4;

                if (mem == 1 && direc == 3)
                    direc = 1;
                if (mem == 2 && direc == 4)
                    direc = 2;
                if (mem == 3 && direc == 1)
                    direc = 3;
                if (mem == 4 && direc == 2)
                    direc = 4;
            }
            head = 1;
            while (head != score)
            {
                if ((snake[0][1] == snake[head][1] && snake[0][0] == snake[head][0]) || snake[0][0] > 46 || snake[0][0] == 3 || snake[0][1] == 0 || snake[0][1] > 30)
                {
                    tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 10, 10, tft.color565(200, 10, 10));
                    tft.setTextColor(0x0000);
                    tft.setFreeFont(&FreeMono24pt7b);
                    tft.drawCentreString(String(score), 160, 100, 4);

                    while (!isScreenTouched())
                        ;
                    gameover=1;
                }
                head++;
            }
            if (snake[0][0] == pointxy[1] && snake[0][1] == pointxy[0])
            {
                pointxy[0] = random(2, 30);
                pointxy[1] = random(5, 46);
                tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
                score+=2;
            }
        }
    }
}*/

#endif