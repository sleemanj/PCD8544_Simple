/** Simple Text Printing Example
 *  
 *  This example demonstrates printing text to the LCD by printing an ever increasing
 *  counter to the lcd.
 *  
 *  You can see that we can use print() and println() just like we would
 *  with Serial.
 *   
 */
 
#include <SPI.h>
#include "PCD8544_Simple.h"

PCD8544_Simple lcd;

int counter = 0;

void setup()
{
  lcd.begin();  
}

void loop()
{  
  lcd.print("Count: ");
  lcd.println(counter++);
  lcd.update();
  delay(100);  
}