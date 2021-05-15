#ifndef My_LiquidCrystal_I2C_h
#define My_LiquidCrystal_I2C_h

#include <Wire.h>

class My_LiquidCrystal_I2C {
private:
	void send4byte(uint8_t, uint8_t);
	void send(uint8_t);
	void pulse(uint8_t);
public:
	My_LiquidCrystal_I2C() { };
	void init();
	void print(const char*);
	void print(char);
	void clearDisplay();
	void setCursor(uint8_t, uint8_t);
	void showCursor();
	void scrollDisplay();
};

#endif