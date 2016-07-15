/** Absolutely Positioned (Drawn) Text
 *  
 *  Sometimes you need to position text better than at a cursor position
 *  so we can use drawText() to draw some text at a particular pixel
 *  location.
 * 
 *  Note that this method can ONLY draw text, it can't print numbers
 *  etc natively like print() can.
 * 
 *  The pixel location is the TOP LEFT of the first character drawn.
 * 
 *  When you use a draw_____() function you must call "update()" to
 *  refresh the display and actually show what you drew.   
 *  
 */
 
#include <SPI.h>
#include "PCD8544_Simple.h"

PCD8544_Simple lcd;

void setup()
{
  lcd.begin();  
}

void loop()
{  
  for(uint8_t x = 0; x < PCD8544_X_PIXELS; x+=2)
  {
    uint8_t y = ((float)x/PCD8544_X_PIXELS) * PCD8544_Y_PIXELS;
  
    lcd.clear();
    lcd.drawText("Hello\nWorld", x, y);
    lcd.update();
    delay(100);          
  }
  
  // We can of course also combine our text with some shape for fancy effects, 
  // I quite like this expanding circle, the not-quite-filled-sort-of-shadowy
  // circle is just a happy accident from a not-very-good filled circle
  // algorithm.
    
  lcd.invertText();
  // We draw some filled circles out to 50 radius (larger than the screen)
  for(uint8_t x = 1; x < 50; x++)
  {
    lcd.clear();
    lcd.drawFilledCircle(PCD8544_X_PIXELS/2,PCD8544_Y_PIXELS/2, x);
    
    // We want a rectangle that will border our text, which is 
    // going to be 2 lines of 5 characters each
    // Our font is 6x8 (including spacings) 
    uint8_t textX = (84-(5*6))/2; // lcd is 84px wide, 5 characters, 6px per character
    uint8_t textY = (48-(2*8))/2; // lcd is 48px high, 2 lines, 8px per line    
    lcd.drawRectangle(textX-1, textY-1, 5*6+1, 2*8+1);
    
    // And in the middle of the circles we put our inverted text
    lcd.drawText("Hello\nWorld", textX, textY);    
    lcd.update();
    delay(100);
  }
  
  lcd.invertText(false);
}