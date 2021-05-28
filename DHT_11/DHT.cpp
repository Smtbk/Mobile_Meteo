#include "DHT.h"

#define MIN_INTERVAL 2000
#define TIMEOUT UINT32_MAX


DHT::DHT(uint8_t pin) {
  _pin = pin;
  _maxcycles = microsecondsToClockCycles(1000); 
}

void DHT::begin(uint8_t usec) {
  pinMode(_pin, INPUT_PULLUP);
  _lastreadtime = millis() - MIN_INTERVAL;
  pullTime = usec;
}


int DHT::readTemperature() {
  int f = NAN;

  if (read()) {
    f = data[2];
    if (data[3] & 0x80) {
        f = -1 - f;
    }
  }
  return f;
}

int DHT::readHumidity() {
  int f = NAN;
  if (read()) {
      f = data[0];
  }
  return f;
}

bool DHT::read() {
  uint32_t currenttime = millis();
  if ((currenttime - _lastreadtime) < MIN_INTERVAL) {
    return _lastresult;
  }
  _lastreadtime = currenttime;

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  pinMode(_pin, INPUT_PULLUP);
  delay(1);

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  
  delay(20);


  uint32_t cycles[80];
  {
    pinMode(_pin, INPUT_PULLUP);
    delayMicroseconds(pullTime);

    noInterrupts();

    if (expectPulse(LOW) == TIMEOUT) {
      _lastresult = false;
      return _lastresult;
    }
    if (expectPulse(HIGH) == TIMEOUT) {
      _lastresult = false;
      return _lastresult;
    }

    for (int i = 0; i < 80; i += 2) {
      cycles[i] = expectPulse(LOW);
      cycles[i + 1] = expectPulse(HIGH);
    }

    interrupts();
  } 

  for (int i = 0; i < 40; ++i) {
    uint32_t lowCycles = cycles[2 * i];
    uint32_t highCycles = cycles[2 * i + 1];
    if ((lowCycles == TIMEOUT) || (highCycles == TIMEOUT)) {
      _lastresult = false;
      return _lastresult;
    }
    data[i / 8] <<= 1;
    if (highCycles > lowCycles) {
      data[i / 8] |= 1;
    }
  }

  if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
    _lastresult = true;
    return _lastresult;
  } else {
    _lastresult = false;
    return _lastresult;
  }
}

uint32_t DHT::expectPulse(bool level) {
  uint32_t count = 0;

  while (digitalRead(_pin) == level) {
      if (count++ >= _maxcycles) {
          return TIMEOUT;
      }
  }

  return count;
}
