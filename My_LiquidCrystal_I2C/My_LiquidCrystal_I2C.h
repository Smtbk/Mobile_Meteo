#ifndef My_LiquidCrystal_I2C_h
#define My_LiquidCrystal_I2C_h

#include <Wire.h>
#include <Print.h>

class My_LiquidCrystal_I2C : public Print {
private:
	void send4byte(uint8_t, uint8_t);
	void send(uint8_t);
	void pulse(uint8_t);
	size_t write(uint8_t);
public:
	My_LiquidCrystal_I2C() { };
	void init();
	void clearDisplay();
	void setCursor(uint8_t, uint8_t);
	void home();
};

#endif