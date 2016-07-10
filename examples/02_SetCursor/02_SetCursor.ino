/** Simple Text Positioning (Cursor)
 *  
 *  This example demonstrates printing text to the LCD starting at a 
 *  certain text position.
 * 
 *  The LCD is divided into a grid of 14 columns (0-13) and 6 rows (0-5)
 *  you can start printing characters at any position identified by the
 *  X and Y cursor location. 
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
  // Print the word HELLO on row 2
  lcd.setCursor(4,2);  
  lcd.print("HELLO");
  
  // Print the word WORLD on row 3
  lcd.setCursor(4,3);  
  lcd.print("WORLD");  
  delay(100);  
}