#ifndef My_Sensor
#define My_Sensor

#include<Arduino.h>

inline void sensorBegin(int pin_in, int pin_out) {
	pinMode(pin_in, INPUT);
	pinMode(pin_out, OUTPUT);
}

inline int sensorRead(int pin_in, int pin_out) {
	digitalWrite(pin_out, HIGH);
	int i = digitalRead(pin_in);
	if (i != 0)
		return i;
	digitalWrite(pin_out, LOW);
	return 0;
}

#endif



