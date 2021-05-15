#include <Wire.h>
#include <My_LiquidCrystal_I2C.h>

My_LiquidCrystal_I2C lcd;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.print("Ticker");
  delay(1000);
}

void loop() {
  //lcd.scrollDisplayLeft();
  //delay(1000);
}
