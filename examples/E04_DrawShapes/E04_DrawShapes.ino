/** Draw simple shapes
 *  
 *  We can draw lines, rectangles, filled rectangles, circles and filled circles
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
  // Draw some random lines, lines have a start position (x0,y0)
  // and an end position (x1,y1)
  lcd.clear();  
  for(uint8_t numlines = 0; numlines < 100; numlines++)
  {
    uint8_t x0, x1;
    uint8_t y0, y1;
    x0 = random(0,84);
    x1 = random(0,84);
    
    y0 = random(0,48);
    y1 = random(0,48);
    
    lcd.drawLine(x0,y0,x1,y1);
    lcd.update();
    delay(100);
  }
  delay(1000);
  
  // Draw some random rectangles, a rectangle has a top left corner (x0, y0)
  // and a width and height.  
  lcd.clear();
  for(uint8_t numrects = 0; numrects < 25; numrects++)
  {
    uint8_t x0, y0;
    uint8_t  w, h;
    x0 = random(0,84);  // Left corner    
    y0 = random(0,48);  // Top  corner
    
    w  = random(1,84-x0); // Width
    h  = random(1,48-y0); // Height
    
    lcd.drawRectangle(x0,y0,w,h);
    lcd.update();
    delay(100);
  }
  delay(1000);
  
  // Draw some random filled rectangles, a rectangle has a top left corner (x0, y0)
  // and a width and height.  
  lcd.clear();
  for(uint8_t numrects = 0; numrects < 25; numrects++)
  {
    uint8_t x0, y0;
    uint8_t  w, h;
    x0 = random(0,84);  // Left corner    
    y0 = random(0,48);  // Top  corner
    
    w  = random(1,((84-x0)/2)+1); // Width
    h  = random(1,((48-y0)/2)+1); // Height
    
    lcd.drawFilledRectangle(x0,y0,w,h);
    lcd.update();
    delay(100);
    
  }
  delay(1000);
    
  // Draw some random circles, a circle has a midpoint and a radius
  lcd.clear();
  for(uint8_t numrects = 0; numrects < 25; numrects++)
  {
    uint8_t x0, y0;
    uint8_t  r;
    x0 = random(0,84);  // Center, x
    y0 = random(0,48);  // Center, y
    
    r  = random(1,25);  // Radius
        
    lcd.drawCircle(x0,y0,r);
    lcd.update();
    delay(100);
  }
  delay(1000);
  
  // Draw some random filled circles, a circle has a midpoint and a radius
  // NB: The filling of circles isn't complete, could do with work.
  lcd.clear();
  for(uint8_t numrects = 0; numrects < 25; numrects++)
  {
    uint8_t x0, y0;
    uint8_t  r;
    x0 = random(0,84);  // Center, x
    y0 = random(0,48);  // Center, y
    
    r  = random(1,25);  // Radius
        
    lcd.drawFilledCircle(x0,y0,r);
    lcd.update();
    delay(100);
  }
  delay(1000);
}