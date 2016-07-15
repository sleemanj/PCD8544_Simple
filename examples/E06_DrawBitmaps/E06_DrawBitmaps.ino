/** Draw (display) bitmaps
 *  
 *  We can display a bitmap image, placing it's top-left
 *  at any position we so choose.
 * 
 *  The bitmap is stored in a specially formatted array, to 
 *  create this array, first create your 84x48 pixel image 
 *  (or smaller, preferably not larger) then upload it to
 *     http://sparks.gogo.co.nz/pcd8554-bmp.html
 *  the code will be generated for you and you can copy-paste.
 * 
 *  When you use a draw_____() function you must call "update()" to
 *  refresh the display and actually show what you drew.   
 *  
 */
 
#include <SPI.h>
#include "PCD8544_Simple.h"

// This is a (vertical) picture of a mad scientist
const uint8_t madscientist_Width    = 79;
const uint8_t madscientist_Height   = 48;
const uint8_t PROGMEM madscientist_Bitmap[] = { 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1e, 0xbf, 0xfd, 0xf8, 0xf0, 0xe1, 0xc7,
  0xcf, 0x8f, 0x1f, 0x3f, 0x7f, 0xfd, 0xf7, 0xfb, 0x77, 0x35, 0x17, 0x05, 0x07, 0x05, 0x07, 0x0d, 0x07, 0x05, 0x07, 0x09, 0x1f, 0x18,
  0x08, 0x18, 0x08, 0x18, 0x0d, 0x1b, 0x06, 0x00, 0x40, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x20, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00,
  0x00, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1e, 0x03, 0x01, 0x00, 0xf9, 0x1f, 0x07,
  0xc7, 0xff, 0x7f, 0x3e, 0x1e, 0x1b, 0x39, 0x18, 0x3e, 0x0e, 0xc6, 0x1c, 0x18, 0x30, 0xb8, 0x38, 0x0c, 0x8e, 0x0e, 0x9c, 0x30, 0x30,
  0x70, 0x70, 0x30, 0x30, 0x18, 0x18, 0x18, 0x18, 0x30, 0x31, 0xff, 0x78, 0x21, 0x61, 0xc3, 0x83, 0x07, 0x0f, 0x18, 0x01, 0x03, 0x07,
  0x1e, 0x7f, 0x1f, 0x00, 0x03, 0x07, 0x3e, 0xf8, 0x7f, 0x1e, 0xfc, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x9f, 0xf0, 0xc0, 0x00, 0x00, 0x0f, 0x3c, 0xe0,
  0x80, 0x07, 0x0f, 0x7c, 0xf0, 0x00, 0x00, 0x00, 0x20, 0xcd, 0x00, 0x00, 0x00, 0x25, 0x52, 0x00, 0x00, 0x03, 0x04, 0x30, 0xc1, 0x02,
  0x00, 0x27, 0x08, 0x90, 0x20, 0x80, 0xc0, 0xa0, 0x21, 0x24, 0x40, 0x20, 0x10, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0xd0, 0xbc,
  0x74, 0xdc, 0x8c, 0xfc, 0xf8, 0x40, 0x00, 0x03, 0xc0, 0xf0, 0x3f, 0x0f, 0x00, 
  0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x03, 0x00, 0x06, 0x00, 0x00,
  0x07, 0x07, 0x42, 0x9f, 0x87, 0x81, 0x40, 0x80, 0x00, 0x01, 0x04, 0x48, 0x84, 0x00, 0x40, 0x22, 0x05, 0x10, 0x10, 0x00, 0x60, 0x41,
  0x02, 0xc6, 0x01, 0x01, 0x00, 0x00, 0xc1, 0xc3, 0x8e, 0x24, 0x00, 0x08, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe1,
  0xa3, 0xff, 0xfe, 0x8b, 0x01, 0x00, 0x00, 0x18, 0xf1, 0xf7, 0x7e, 0xf8, 0x60, 
  0x90, 0x80, 0x80, 0x8c, 0xa8, 0x00, 0xa0, 0x00, 0x20, 0x00, 0x3c, 0x08, 0x00, 0x00, 0x40, 0x00, 0x08, 0x58, 0x00, 0x04, 0x20, 0x10,
  0x00, 0x00, 0xc2, 0xfc, 0x0c, 0x06, 0x07, 0x03, 0x07, 0x0e, 0x0c, 0x1c, 0x19, 0x1a, 0x30, 0x34, 0xfc, 0xf0, 0xa1, 0x88, 0x90, 0x90,
  0x34, 0x2a, 0xa9, 0x42, 0x10, 0x74, 0x80, 0x04, 0x00, 0x00, 0x17, 0x30, 0x20, 0x60, 0x38, 0x0d, 0x00, 0x00, 0x20, 0x33, 0x1e, 0x1f,
  0x0c, 0x0f, 0x06, 0x03, 0x00, 0x00, 0xfc, 0xf8, 0x7f, 0x3f, 0x00, 0x00, 0x00, 
  0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x7e, 0xfe, 0x00, 0x00,
  0x00, 0x0c, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03,
  0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x03, 0x03, 0x0f, 0xde, 0xfa, 0xf8, 0xc8, 0x40, 0x40, 0xe0, 0xe0, 0x30, 0x00, 0x80, 0x80, 0xc0,
  0xf0, 0xf8, 0x80, 0xc0, 0x70, 0x3e, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

// This is a (horizontal) picture of a chemical flask
const uint8_t chemical24px_Width    = 20;
const uint8_t chemical24px_Height   = 24;
const uint8_t PROGMEM chemical24px_Bitmap[] = { 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0xfe, 0x0e, 0x0e, 0xfe, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x30, 0x98, 0x0f, 0x00, 0x10, 0x47, 0x0c, 0x18, 0x70, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x30, 0x7c, 0x47, 0x41, 0x50, 0x50, 0x41, 0x47, 0x46, 0x42, 0x40, 0x58, 0x58, 0x50, 0x41, 0x47, 0x7c, 0x30, 0x00
};


PCD8544_Simple lcd;

void setup()
{
  lcd.begin();  
  // lcd.setContrast(70);
}

void loop()
{  
  // To display a bitmap defined above we simply pass it to drawBitmap with
  // x and y for the top left (in this case 0,0) and the width and height
  lcd.clear();  
  lcd.drawBitmap(madscientist_Bitmap, 0, 0, madscientist_Width, madscientist_Height);
  lcd.update();
  delay(1000);

  // As you can see we can display a bitmap at any x/y pixel location
  for(uint8_t x = 0; x < 84-chemical24px_Width; x++)
  {
    uint8_t y = ((float)x/(84-chemical24px_Width)) * (48-chemical24px_Height);
    
    lcd.clear();  
    lcd.drawBitmap(chemical24px_Bitmap, x, y, chemical24px_Width, chemical24px_Height);
    lcd.update();
    delay(200);  
  }

  // We can display bitmaps multiple times, note that the entire bitmap (including "white" pixels) is overlaid
  // in graphic design terms there is no alpha layer.
  lcd.clear();  
  for(uint8_t numlines = 0; numlines < 100; numlines++)
  {
    uint8_t x, y;
    x = random(0,84);
    y = random(0,48);
    lcd.drawBitmap(chemical24px_Bitmap, x, y, chemical24px_Width, chemical24px_Height);
    lcd.update();
    delay(100);  
  }
}