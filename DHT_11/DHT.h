#ifndef DHT_H
#define DHT_H

#include "Arduino.h"

#define DHT11 11 

class DHT {
public:
  DHT(uint8_t pin);
  void begin(uint8_t usec = 55);
  float readTemperature();
  float readHumidity();
  float convertCtoF(float);
  float convertFtoC(float);
  bool read();

private:
  uint8_t data[5]; 
  uint8_t _pin;
  uint32_t _lastreadtime, _maxcycles;
  bool _lastresult;
  uint8_t pullTime;

  uint32_t expectPulse(bool level);
};

class InterruptLock {
public:
  InterruptLock() {
#if !defined(ARDUINO_ARCH_NRF52)
    noInterrupts();
#endif
  }
  ~InterruptLock() {
#if !defined(ARDUINO_ARCH_NRF52)
    interrupts();
#endif
  }
};

#endif
