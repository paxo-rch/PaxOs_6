#ifndef APPS_HPP
#define APPS_HPP

#include "app_manager/apps_manager.hpp"
#include "apps/home/home.hpp"


void runAppSystem()
{
    HomeApp home;
    home.run();
}

#endif