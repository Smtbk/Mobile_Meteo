#include <My_LiquidCrystal_I2C.h>
#include <DHT.h>
#define K 0.9

My_LiquidCrystal_I2C lcd;
DHT dht(2);

unsigned long time = millis();
float temp = 0;
float hum = 0;

unsigned long filter(unsigned long n, unsigned long old) {
  return old * K + n * (1 - K);
}

void printMeteo() {
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(1, 0);
  lcd.print(temp);
  lcd.setCursor(2, 0);
  lcd.print("Humidity");
  lcd.setCursor(3, 0);
  lcd.print(hum);
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  dht.begin();
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  printMeteo();
  time = millis();
}

void loop() {
  if (millis() - time > 2000)
  {
    time = millis();
    float temp_t = dht.readTemperature();
    float temp_h = dht.readHumidity();
    lcd.setCursor(1, 10);
    lcd.print(temp_t);
    lcd.setCursor(3, 10);
    lcd.print(temp_h);
    temp = filter(temp_t, temp);
    hum = filter(temp_h, hum);
    printMeteo();
  }
}
