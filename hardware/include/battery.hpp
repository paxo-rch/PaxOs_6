#ifndef BATTERY_HPP
#define BATTERY_HPP

#include <Wire.h>
#include "battery_utils.hpp"

#define I2C_SDA 21
#define I2C_SCL 22

#define ADC_BAT 35 // TCALL 35

int bat_mv = 0;

void getBatteryFromADC()
{
  bat_mv = 0;
  uint32_t oversample = 0;
  for (size_t i = 0; i < 100; i++)
  {
    oversample += (uint32_t)analogRead(ADC_BAT);
  }
  bat_mv = (int)oversample / 100;
  bat_mv = ((float)bat_mv / 4096) * 3600 * 2;

  Serial.print("Battery from ADC: ");
  Serial.print(bat_mv);
  Serial.println("mV");
}

void PowerManagment()
{

  Wire.begin(I2C_SDA, I2C_SCL);
  delay(100);

  Serial.println(String("IP5306 Battery level:") + getBatteryLevel());
  getBatteryFromADC();
}

namespace battery
{
    int getVolatge(){return (analogRead(35)*2) * 1000 / 1135;}
    int getLevel();
};

int battery::getLevel()
{
  int v = getVolatge();
  if(v>4200)
    return 100;
  if(v>4100)
    return 90;
  if(v>3970)
    return 80;
  if(v>3920)
    return 70;
  if(v>3870)
    return 60;
  if(v>3830)
    return 50;
  if(v>3790)
    return 40;
  if(v>3750)
    return 30;
  if(v>3700)
    return 20;
  if(v>3600)
    return 10;
  if(v>3300)
    return 5;
  return 0;
}


#endif /* BATTERY_HPP */