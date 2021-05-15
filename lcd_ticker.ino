#include <Wire.h>
#include <My_LiquidCrystal_I2C.h>

My_LiquidCrystal_I2C lcd;
char str[] = {'H', 'e', 'l', 'l', 'o'};

void setup() {
  Serial.begin(9600);
  lcd.init();
  delay(1000);
}

void loop() {
  lcd.tickerInRow(str, 1); //пример использования бегущей строки
}
