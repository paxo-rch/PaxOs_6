bool BackgroundProcess();

//#include "../../system/tasks/system.hpp"

#ifndef APPS_MANAGER_HPP
#define APPS_MANAGER_HPP

//#include <vector>

#define while(condition) while(BackgroundProcess() && condition)

void wait(long timeout)
{
    long mm_ = millis();
    while(timeout + mm_ > millis());
}

class App
{
public:
    virtual String getName();
    virtual String getLogo();
    virtual void run();
    virtual void restore();
    virtual void quit();
};

#endif