#include <Wire.h>
#include <My_LiquidCrystal_I2C.h>

My_LiquidCrystal_I2C lcd;
uint8_t charmap[8] = {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.createChar(1, charmap);
  lcd.home();
  lcd.print(1, 0); // так выводить кастомные символы
  delay(1000);
}

void loop() {
  
}
