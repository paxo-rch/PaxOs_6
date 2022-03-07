#ifndef SCREEN_LIGHT_HPP
#define SCREEN_LIGHT_HPP

int STATE_LIGHT = 0;

#define SCREEN_LED   25
#define PWM1_Ch    0
#define PWM1_Res   8
#define PWM1_Freq  1000

namespace SCREEN_LIGHT
{
    void analog(int state)
    {
        if (state < STATE_LIGHT)
        {
            while (STATE_LIGHT > state)
            {
                ledcWrite(PWM1_Ch, STATE_LIGHT--);
                delay(1);
            }
            return;
        }
        if (state > STATE_LIGHT)
        {
            while (STATE_LIGHT < state)
            {
                ledcWrite(PWM1_Ch, STATE_LIGHT++);
                delay(1);
            }
            return;
        }
    }
    void ON() { analog(255); }
    void OFF() { analog(-1); }
}

#endif
