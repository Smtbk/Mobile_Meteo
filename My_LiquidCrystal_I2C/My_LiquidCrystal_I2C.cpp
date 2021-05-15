#include "My_LiquidCrystal_I2C.h"
#include <inttypes.h>
#include <Arduino.h>
#include <Wire.h>

#define address 0x27 // адрес устройства
#define backlight 0x08 // включение подсветки



/**********public**********/



/// <summary>
/// Инициализация дисплея 
/// (приведение его к нормальному режиму работы)
/// </summary>
void My_LiquidCrystal_I2C::init() {
	delay(50);

	Wire.begin();

	send(backlight);
	delay(1000);

	send(B00110000); // 1
	pulse(B00110000);
	delayMicroseconds(4500);

	send(B00110000); // 2
	pulse(B00110000);
	delayMicroseconds(4500);

	send(B00110000); // 3
	pulse(B00110000);
	delayMicroseconds(150);

	send(B00100000); // 4
	pulse(B00100000);
	delayMicroseconds(50);

	send4byte(B00101000, 0); // установка 4 битного режима, использование 2х строк и установка шрифта
	delayMicroseconds(50);

	send4byte(B00001100, 0); // включение дисплея, отключение курсора и мигания
	delayMicroseconds(50);

	send4byte(B00000001, 0); // очистка дисплея
	delayMicroseconds(2000);

	send4byte(B00000110, 0); // вывод символов слева-направо, запрет на сдвиг экрана
	delayMicroseconds(50);

	send4byte(B00000010, 0); // установка курсора в начало
	delayMicroseconds(2000);
}

/// <summary>
/// Вывод строки на дисплей
/// </summary>
/// <param name="str">Строка</param>
void My_LiquidCrystal_I2C::print(const char* str) {
	while (*str) {
		send4byte((uint8_t)(*str), 1);
		str++;
	}
}

/// <summary>
/// Вывод символа на дисплей
/// </summary>
/// <param name="byte">Символ</param>
void My_LiquidCrystal_I2C::print(char c) {
	send4byte((uint8_t)c, 1);
}

/// <summary>
/// Очистить дисплей
/// </summary>
void My_LiquidCrystal_I2C::clearDisplay() {
	send4byte(B00000001, 0);
	delayMicroseconds(2000);
}

/// <summary>
/// Установить курсор в выбранную позицию
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
void My_LiquidCrystal_I2C::setCursor(uint8_t row, uint8_t col) {
	uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > 4) {
		row = 4 - 1;
	}
	send4byte(0x80 | (col + row_offsets[row]), 0);
}

/// <summary>
/// Показать курсрор
/// </summary>
void My_LiquidCrystal_I2C::showCursor() {
	send4byte(B00001110, 0);
	delayMicroseconds(50);
}

/// <summary>
/// Сдвиг дисплея вправо
/// </summary>
void My_LiquidCrystal_I2C::scrollDisplay() {
	send4byte(B00011100, 0);
	delayMicroseconds(50);
}



/**********private**********/



/// <summary>
/// Отправка данных на дисплей 
/// (1 байт данных отправляется 4мя байтами)
/// </summary>
/// <param name="data">Байт данных</param>
/// <param name="flags">Байт флагов</param>
void My_LiquidCrystal_I2C::send4byte(uint8_t data, uint8_t flags) {
	uint8_t up = data & 0xF0;
	uint8_t lo = (data << 4) & 0xF0;
	send(up | flags);
	pulse(up | flags);
	send(lo | flags);
	pulse(lo | flags);
}

/// <summary>
/// Отправка одного байта на дисплей
/// </summary>
/// <param name="data">Байт данных</param>
void My_LiquidCrystal_I2C::send(uint8_t data) {
	Wire.beginTransmission(address);
	Wire.write(data | backlight);
	Wire.endTransmission();
}

/// <summary>
/// Отправка управляющего импульса
/// </summary>
/// <param name="data">Байт данных</param>
void My_LiquidCrystal_I2C::pulse(uint8_t data) {
	send(data | 0x04);
	delayMicroseconds(1);
	send(data & ~(0x04));
	delayMicroseconds(50);
}