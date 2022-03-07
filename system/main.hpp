#include "tasks/system.hpp"
#include "hardware/hardware.hpp"
#include "files/files_manager.hpp"
#include "../apps/apps.hpp"
//#include "tasks/task.hpp"

#include <WiFi.h>
#include <BluetoothSerial.h>
#include "driver/adc.h"
#include <esp_bt.h>

void disableWiFi()
{
    adc_power_off();
    WiFi.disconnect(true); // Disconnect from the network
    WiFi.mode(WIFI_OFF);   // Switch WiFi off
}

void disableBluetooth()
{
    btStop();
}

byte updateTouch()
{
    isScreenTouched();
}

#define SCREEN_LED   25
#define PWM1_Ch    0
#define PWM1_Res   8
#define PWM1_Freq  1000

void setup()
{
    disableWiFi();
    disableBluetooth();

    Serial.begin(115200);
    SIM.begin(9600);
    //RTC.begin(9600);

    pinMode(19, INPUT_PULLDOWN);
    pinMode(22, OUTPUT);    // declare TFT power
    digitalWrite(22, HIGH); // TFT power on
    pinMode(25, OUTPUT);    // declare screen's light
    pinMode(32, INPUT_PULLUP);  //declare home button

    TFT_init();
    SD_init();

    Task *autoHourUpdate = new Task(5000, update_hour, TASKS_LOOP); // auto hour update
    SystemTasks.addTask(autoHourUpdate);
    Task *autoSim800lreader = new Task(1000, PHONE::check_news, TASKS_LOOP); // auto hour update
    SystemTasks.addTask(autoSim800lreader);
    Task *touchUpdate = new Task(100, updateTouch, TASKS_LOOP); // auto hour update
    SystemTasks.addTask(touchUpdate);
    /* initialize page */

    ledcAttachPin(SCREEN_LED, PWM1_Ch);
    ledcSetup(PWM1_Ch, PWM1_Freq, PWM1_Res);
    tft.fillScreen(0xFFFF);
    bmpDrawSD("/logo.bmp", 3, 100);
    SCREEN_LIGHT::ON();
    delay(5000);
    tft.fillScreen(0x0000);
}

void loop()
{
    runAppSystem();
}