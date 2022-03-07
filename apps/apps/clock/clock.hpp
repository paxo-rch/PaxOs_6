#ifndef CLOCK_APP_HPP
#define CLOCK_APP_HPP

class ClockApp : public App
{
    public:
    String getName() { return "clock"; }
    String getLogo() { return "/paxo/apps/time/logo.bmp"; }
    void run();
    void restore(){};
    void quit(){};

    void menu();
    void simpleClock();
    void simpleTimer();
    void alarmClock();

    private:
    bool reloadGui = 0;
    long timer = 0;
    long timerBegin = 0;
};

#include "clock.cpp"

#endif