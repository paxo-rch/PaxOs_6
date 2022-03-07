#ifndef HOME_APP_HPP
#define HOME_APP_HPP

#include "../../../graphics/graphics.hpp"
#include "../../app_manager/apps_manager.hpp"

int idOfLaunchedApplication = -1;

class HomeApp
{
public:
    HomeApp() {run();}
    ~HomeApp() {}
    void run();
    void draw_gui();
    void loop();

    byte page = 0;
};

bool already_launched=false;

/*------------------------------------------------------*/
/*            INCLUDE SYSTEM APPS                       */
/*------------------------------------------------------*/
#include "../../system_apps/lockedScreen.hpp"
/*------------------------------------------------------*/
/*            INCLUDE APPS HERE                         */
/*------------------------------------------------------*/
#include "../calculator/calculator.hpp"
#include "../snake/snake.hpp"
#include "../phone/phone.hpp"
#include "../message/message.hpp"
#include "../clock/clock.hpp"
/*------------------------------------------------------*/

App *applications[] =
    {
        new CalculatorApp,
        new AppSnake,
        new AppPhone,
        new AppMessage,
        new ClockApp};

/*------------------------------------------------------*/

#include "home.cpp"

#endif /* HOME_APP_HPP */