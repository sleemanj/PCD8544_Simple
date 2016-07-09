#include <SPI.h>
#include "PCD8544_Simple.h"

PCD8544_Simple lcd;

void setup(void)
{
	Serial.begin(9600);
	lcd.begin();
	lcd.print(F("Preparing benchmark"));
	lcd.update();
	delay(1000);
}

uint8_t bmp[] = {
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
};

void loop(void) 
{
  
  
  while(1)
  {
    for(uint8_t x = 1; x < 50; x++)
  {
    lcd.clear();
    lcd.drawFilledCircle(PCD8544_X_PIXELS/2,PCD8544_Y_PIXELS/2, x);
    lcd.update();
    delay(100);
  }
  for(uint8_t x = 50; x > 0; x--)
  {
    lcd.clear();
    lcd.drawFilledCircle(PCD8544_X_PIXELS/2,PCD8544_Y_PIXELS/2, x);
    lcd.update();
    delay(100);
  }
  
  lcd.clear();
  lcd.drawCircle(PCD8544_X_PIXELS/2,PCD8544_Y_PIXELS/2, 20);
  lcd.update();
  delay(1000);

  lcd.clear();
  lcd.drawFilledCircle(PCD8544_X_PIXELS/2,PCD8544_Y_PIXELS/2, 20);
  lcd.update();
  delay(1000);
  }
  
	size_t len;

	lcd.clear();
	unsigned long time = micros();
	len = lcd.print(F("012345678901234567890123456789012345678901234567890123456789012345678901234567890123"));
	lcd.update();
	time = micros() - time;
	delay(3000);

	lcd.clear();
	lcd.print(F("The time it took to print 84 chars is:    "));
	lcd.print(time);
	lcd.update();
	delay(3000);

	lcd.clear();
	lcd.gotoXY(5,3);
	lcd.print(F("Test gotoXY"));
	lcd.update();
	delay(3000);

	lcd.clear();
	time = micros();
	lcd.writeBitmap(bmp, 10, 2, 25, 3);
	lcd.update();
	time = micros() - time;
	delay(3000);

	lcd.clear();
	lcd.print(F("The time it took to draw a 25x3 (25x18) bitmap is: "));
	lcd.print(time);
	lcd.update();
	delay(3000);
	
	lcd.clear();
	time = micros();
	lcd.drawRectangle(5, 5, 50, 40);
	lcd.drawLine(75, 3, 75, 35);
	lcd.drawLine(60, 10, 60, 40);
	lcd.drawLine(10, 47, 60, 47);
	lcd.update();
	time = micros() - time;
	delay(3000);

	lcd.clear();
	len = lcd.print(F("The time it took draw a rect and 3 lines: "));
	len += lcd.print(time);
	lcd.update();
	delay(3000);

	lcd.clear();
	time = micros();
	for (uint8_t row = 0; row < PCD8544_Y_PIXELS; row++)
	{
		for (uint8_t col = 0; col < PCD8544_X_PIXELS; col++)
		{
			uint8_t pixel = (col + row) % 2;
			lcd.setPixel(col, row, pixel);
		}
	}
	lcd.update();
	time = micros() - time;
	delay(5000);

	lcd.clear();
	lcd.print(F("The time it took to run setPixel on all 4032 pixels and render it:    "));
	lcd.print(time);
	lcd.update();
	delay(5000);
}