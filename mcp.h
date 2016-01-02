#ifndef MCP_h
#define MCP_h

#include <Arduino.h>
#include "Wire.h"

#define POWER_MODE_ONDEMAND  0
#define POWER_MODE_PASSTRU   1
#define POWER_MODE_ALWAYS_ON 2

#define POWER_SUPPLY_AVR_MIN 1.8

class MCP {
 public:
  MCP(Stream& s):serial(s) {};
  
  void setMinVoltage(float voltage);
  void checkMode(float voltage);
  uint8_t getMode(void);
  
  void init(uint8_t enable_pin);
  void sleep(void);
  void disablePowerBoost(void);
  void enablePowerBoost(void);
  
 protected:
  uint8_t enable_pin;
  uint8_t mode;
  float min_voltage;


  
  private:
    Stream& serial;
};

#endif
