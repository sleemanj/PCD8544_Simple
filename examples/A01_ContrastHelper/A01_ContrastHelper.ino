/** Contrast Helper
 *  
 *  Loops through a range of contrast values and prints each one.
 * 
 *  To set the contrast in your sketch, simply put lcd.setContrast(xx); 
 *  after your lcd.begin().
 *   
 *  Experimentally determined, contrast values around 65-70 tend to 
 *  work reasonably well on most displays.  The best contrast value
 *  for each display is specific to that particular display due to
 *  manufacturing tolerances and so forth.
 *  
 */
 
#include <SPI.h>
#include "PCD8544_Simple.h"

PCD8544_Simple lcd;
const uint8_t contrastMin = 40;
const uint8_t contrastMax = 80;
static uint8_t contrastDirection = 1;
static uint8_t contrast = (contrastMax-contrastMin)/2+contrastMin;

void setup()
{
  lcd.begin();  
}

void loop()
{  
  if(contrastDirection)
  {
    if(contrast++ > contrastMax)
    {
      contrastDirection = 0;
    }
  }  
  else
  {
    if(contrast-- < contrastMin)
    {
      contrastDirection = 1;
    }  
  }
  
  lcd.setContrast(contrast);      
  lcd.print("lcd.setContrast(");
  lcd.print(contrast);
  lcd.println(");");
  
  delay(500);  
}