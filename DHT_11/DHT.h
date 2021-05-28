#ifndef DHT_H
#define DHT_H

#include "Arduino.h"

#define DHT11 11 

class DHT {
public:
  DHT(uint8_t pin);
  void begin(uint8_t usec = 55);
  int readTemperature();
  int readHumidity();
  bool read();

private:
  uint8_t data[5]; 
  uint8_t _pin;
  uint32_t _lastreadtime, _maxcycles;
  bool _lastresult;
  uint8_t pullTime;

  uint32_t expectPulse(bool level);
};

#endif
