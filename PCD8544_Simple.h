/**
 * Nokia 5110 Type Display Arduino Library
 * 
 * This is a "Fast PCD8544 Library". It is designed to be used with
 * Nokia 5110 type of display, driven by the PCD8544 controller.
 * This library uses hardware SPI of your Arduino microcontroller,
 * and does not supprt 'software SPI' mode.
 *
 * Originally written by Arthur Liberman (aka 'The Coolest').
 *    http://www.alcpu.com
 * Special thanks goes out to 'robtillaart' for his help with debugging
 * and optimization.
 *
 * Reworked by James Sleeman (aka, 'James Sleeman') in 2016
 *    http://sparks.gogo.co.nz
 * to simplify and further Arduinoify, document, and enhance with
 * improved drawing ability (circles, arbitrary lines, non-aligned
 * bitmaps). 
 * 
 * BSD license, check license.txt for more information.
 * All text above must be included in any redistribution.
 * 
*/

#pragma once
#include "Arduino.h"

// When DC is '1' the LCD expects data, when it is '0' it expects a command.
#define PCD8544_COMMAND		0 
#define PCD8544_DATA      1

// You may find a different size screen, but this one is 84 by 48 pixels
#define PCD8544_X_PIXELS	84
#define PCD8544_Y_PIXELS	48
#define PCD8544_ROWS		( PCD8544_Y_PIXELS / 8 )

#define BUF_LEN				(( PCD8544_X_PIXELS * PCD8544_Y_PIXELS) / 8)

#define PCD8544_SUCCESS		1
#define PCD8544_ERROR		0

class PCD8544_Simple : public Print
{
public:
	PCD8544_Simple();	

  /** Initialize
   * 
   * @param Arduino digital pin connected to 5110 RST
   * @param Arduino digital pin connected to 5110 DC 
   * @param Arduino digital pin connected to 5110 CE
   *   If CE toggling is not required, connect CE to ground and chipEnablePin as 255 to disable it.
   */
  
  void begin(uint8_t resetPin = 9, uint8_t dataCommandPin = 8, uint8_t chipEnablePin = 255);
  
  /** Set the Contrast
   * 
   * In general, just change the vOP value, leave bias and tempCoef as defaults.
   * (experimentally determined defaults).
   * 
   * @param The contrast to use, range of 0..127, values around 45 seem to be best (default).
   * @param The bias, range of 0..7, 2 seems to work fine
   * @param The temperature co-efficient, range 0..3, 0 seems to work fine.
   */
  
  void setContrast(uint8_t vOP = 45, uint8_t bias = 2, uint8_t tempCoef = 0);
  
  /** Set the display to inverted (or not inverted) mode.
   * 
   *  @param Pass true to invert the entire display, false to go back to normal mode.
   */
  
  void invertDisplay(uint8_t inverse = true);
  
	/** Update (refresh, render) the display.
   * 
   *  When using the draw_____() methods, you must call update() to actually cause what
   *  it was you drew to display (calling .print() type methods does this automatically)
   * 
   */
	void update();
  
  /** Update (refresh, render) a part of the display.
   * 
   *  As for update() but only re-renders part of the display between the two y pixel
   *  coordinates.  Due to addressing being in 8 pixel vertical blocks, the portion 
   *  of the display updated is expanded to at least 8 vertical pixels.
   * 
   */
  
  void update(uint8_t y0, uint8_t y1);
  
  /** print(), println() support.
   * 
   *  write() is a method used by the Print class to print stuff.
   * 
   *  For simplicity, when using print(), println(), you do not need to
   *  update().
   *    
   * 
   */
  virtual size_t write(uint8_t data);
  
  /** print(), println() support.
   * 
   *  write() is a method used by the Print class to print stuff.
   * 
   *  For simplicity, when using print(), println(), you do not need to
   *  update().
   * 
   */
  
  virtual size_t write(const uint8_t *buffer, size_t size);
  
  /** Invert (or stop inverting) future strings passd to print/println/drawText
   * 
   *  Example, for highlighting a menu option you might invert the selected option
   *   (white text on black background)
   * 
   *  @param True to invert future strings, False to stop inverting future strings.
   */
  
  void invertText(uint8_t inversionStatus = true);  
  
  /** Set a pixel of the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after setting the pixel
   * if you want to see it (or of course, set a bunch of pixels then call update())
   * 
   * @param X coordinate - 0 is left
   * @param Y coordinate - 0 is top
   * @param 0 clears the pixel, 1 sets the pixel.
   * 
   */
  
	void setPixel(uint8_t x, uint8_t y, uint8_t value);
		
  /** Draw a line on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   * 
   * @param X coordinate of first point - 0 is left
   * @param Y coordinate of first point - 0 is top
   * @param X coordinate of second point - 0 is left
   * @param Y coordinate of second point - 0 is top   
   * 
   */
  
	void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  
  /** Draw a rectangle (outline) on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   * 
   * @param X coordinate of top left corner point - 0 is left
   * @param Y coordinate of top left corner point - 0 is top
   * @param Width of rectangle
   * @param Height of rectangle
   * 
   */
	
  void drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
  
  /** Draw a filled rectangle on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   * 
   * @param X coordinate of top left corner point - 0 is left
   * @param Y coordinate of top left corner point - 0 is top
   * @param Width of rectangle
   * @param Height of rectangle
   * 
   */
  
	void drawFilledRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
  
  /** Draw a circle (outline) on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   * 
   * @param X coordinate of center point of circle - 0 is left
   * @param Y coordinate of center point of circle - 0 is top
   * @param Radius of circle
   * 
   */
    
  void drawCircle(uint8_t x0, uint8_t y0, uint8_t radius);
  
  /** Draw a filled circle on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   * 
   * @param X coordinate of center point of circle - 0 is left
   * @param Y coordinate of center point of circle - 0 is top
   * @param Radius of circle
   * 
   */
  
  void drawFilledCircle(uint8_t x0, uint8_t y0, uint8_t radius);
  
  /** Draw text at a pixel location on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   *
   * print() etc only work on "character locations" (setCursor) while this 
   * method can put the text at any pixel location.
   * 
   * @param The string to draw.
   * @param X coordinate of top left point of first character
   * @param Y coordinate of top left point of first character
   * 
   */
  
  void drawText(const char *text, uint8_t x, uint8_t y);
  
  /** Draw bitmap at a pixel location on the display.
   * 
   * Top left pixel is 0, 0.  You must call update() after drawing
   * if you want to see it (or of course, draw a bunch of stuff then call update())
   *
   * To generate a suitable bitmap, you can use my tool here:
   *   http://sparks.gogo.co.nz/pcd8554-bmp.html
   * 
   * @param The bitmap data to draw
   * @param X coordinate of top left point of bitmap
   * @param Y coordinate of top left point of bitmap
   * @param Width of the bitmap
   * @param Height of the bitmap
   * @param True if the bitmap is in PROGMEM, False if it is already in SRAM
   * 
   */
  void drawBitmap(const uint8_t *bitmap, uint8_t x, uint8_t y, uint8_t widthPX, uint8_t heightPX, uint8_t fromProgmem = true);
    
	/** Clear the display.
   * 
   * @param True to clear immediately (update), false if you just want to clear the buffer.
   */
  
	void clear(bool render = true);
  
  /** Set the "cursor" to a position.
   * 
   * The cursor is used for print/println operations, the display is divided into 6 rows (0..5) and 14 columns (0..13)
   * in accordance with out 6x8 font (5x8 plus an extra blank column per character for spacing).
   * This sets the cursor position for the next character printed.
   * 
   * @param Column 0..13
   * @param Row 0..5
   */
  
	uint8_t setCursor(uint8_t x, uint8_t y);	

private:
  
	void writeLcd(uint8_t dataOrCommand, uint8_t data);
	void writeLcd(uint8_t dataOrCommand, const uint8_t *data, uint16_t count);
	
	uint16_t m_Position;
	uint8_t m_Buffer[BUF_LEN];
  
  uint8_t textInversion = false;  
  uint8_t resetPin, dataCommandPin, chipEnablePin;
  
};

//This table contains the hex values that represent pixels
//for a font that is 5 pixels wide and 8 pixels high
static const PROGMEM uint8_t ASCII[][5] = {
	 { 0x00, 0x00, 0x00, 0x00, 0x00 } // 20   (space)
	,{ 0x00, 0x00, 0x5f, 0x00, 0x00 } // 21 !
	,{ 0x00, 0x07, 0x00, 0x07, 0x00 } // 22 "
	,{ 0x14, 0x7f, 0x14, 0x7f, 0x14 } // 23 #
	,{ 0x24, 0x2a, 0x7f, 0x2a, 0x12 } // 24 $
	,{ 0x23, 0x13, 0x08, 0x64, 0x62 } // 25 %
	,{ 0x36, 0x49, 0x55, 0x22, 0x50 } // 26 &
	,{ 0x00, 0x05, 0x03, 0x00, 0x00 } // 27 '
	,{ 0x00, 0x1c, 0x22, 0x41, 0x00 } // 28 (
	,{ 0x00, 0x41, 0x22, 0x1c, 0x00 } // 29 )
	,{ 0x14, 0x08, 0x3e, 0x08, 0x14 } // 2a *
	,{ 0x08, 0x08, 0x3e, 0x08, 0x08 } // 2b +
	,{ 0x00, 0x50, 0x30, 0x00, 0x00 } // 2c ,
	,{ 0x08, 0x08, 0x08, 0x08, 0x08 } // 2d -
	,{ 0x00, 0x60, 0x60, 0x00, 0x00 } // 2e .
	,{ 0x20, 0x10, 0x08, 0x04, 0x02 } // 2f /
	,{ 0x3e, 0x51, 0x49, 0x45, 0x3e } // 30 0
	,{ 0x00, 0x42, 0x7f, 0x40, 0x00 } // 31 1
	,{ 0x42, 0x61, 0x51, 0x49, 0x46 } // 32 2
	,{ 0x21, 0x41, 0x45, 0x4b, 0x31 } // 33 3
	,{ 0x18, 0x14, 0x12, 0x7f, 0x10 } // 34 4
	,{ 0x27, 0x45, 0x45, 0x45, 0x39 } // 35 5
	,{ 0x3c, 0x4a, 0x49, 0x49, 0x30 } // 36 6
	,{ 0x01, 0x71, 0x09, 0x05, 0x03 } // 37 7
	,{ 0x36, 0x49, 0x49, 0x49, 0x36 } // 38 8
	,{ 0x06, 0x49, 0x49, 0x29, 0x1e } // 39 9
	,{ 0x00, 0x36, 0x36, 0x00, 0x00 } // 3a :
	,{ 0x00, 0x56, 0x36, 0x00, 0x00 } // 3b ;
	,{ 0x08, 0x14, 0x22, 0x41, 0x00 } // 3c <
	,{ 0x14, 0x14, 0x14, 0x14, 0x14 } // 3d =
	,{ 0x00, 0x41, 0x22, 0x14, 0x08 } // 3e >
	,{ 0x02, 0x01, 0x51, 0x09, 0x06 } // 3f ?
	,{ 0x32, 0x49, 0x79, 0x41, 0x3e } // 40 @
	,{ 0x7e, 0x11, 0x11, 0x11, 0x7e } // 41 A
	,{ 0x7f, 0x49, 0x49, 0x49, 0x36 } // 42 B
	,{ 0x3e, 0x41, 0x41, 0x41, 0x22 } // 43 C
	,{ 0x7f, 0x41, 0x41, 0x22, 0x1c } // 44 D
	,{ 0x7f, 0x49, 0x49, 0x49, 0x41 } // 45 E
	,{ 0x7f, 0x09, 0x09, 0x09, 0x01 } // 46 F
	,{ 0x3e, 0x41, 0x49, 0x49, 0x7a } // 47 G
	,{ 0x7f, 0x08, 0x08, 0x08, 0x7f } // 48 H
	,{ 0x00, 0x41, 0x7f, 0x41, 0x00 } // 49 I
	,{ 0x20, 0x40, 0x41, 0x3f, 0x01 } // 4a J
	,{ 0x7f, 0x08, 0x14, 0x22, 0x41 } // 4b K
	,{ 0x7f, 0x40, 0x40, 0x40, 0x40 } // 4c L
	,{ 0x7f, 0x02, 0x0c, 0x02, 0x7f } // 4d M
	,{ 0x7f, 0x04, 0x08, 0x10, 0x7f } // 4e N
	,{ 0x3e, 0x41, 0x41, 0x41, 0x3e } // 4f O
	,{ 0x7f, 0x09, 0x09, 0x09, 0x06 } // 50 P
	,{ 0x3e, 0x41, 0x51, 0x21, 0x5e } // 51 Q
	,{ 0x7f, 0x09, 0x19, 0x29, 0x46 } // 52 R
	,{ 0x46, 0x49, 0x49, 0x49, 0x31 } // 53 S
	,{ 0x01, 0x01, 0x7f, 0x01, 0x01 } // 54 T
	,{ 0x3f, 0x40, 0x40, 0x40, 0x3f } // 55 U
	,{ 0x1f, 0x20, 0x40, 0x20, 0x1f } // 56 V
	,{ 0x3f, 0x40, 0x38, 0x40, 0x3f } // 57 W
	,{ 0x63, 0x14, 0x08, 0x14, 0x63 } // 58 X
	,{ 0x07, 0x08, 0x70, 0x08, 0x07 } // 59 Y
	,{ 0x61, 0x51, 0x49, 0x45, 0x43 } // 5a Z
	,{ 0x00, 0x7f, 0x41, 0x41, 0x00 } // 5b [
	,{ 0x02, 0x04, 0x08, 0x10, 0x20 } // 5c backslash
	,{ 0x00, 0x41, 0x41, 0x7f, 0x00 } // 5d ]
	,{ 0x04, 0x02, 0x01, 0x02, 0x04 } // 5e ^
	,{ 0x40, 0x40, 0x40, 0x40, 0x40 } // 5f _
	,{ 0x00, 0x01, 0x02, 0x04, 0x00 } // 60 `
	,{ 0x20, 0x54, 0x54, 0x54, 0x78 } // 61 a
	,{ 0x7f, 0x48, 0x44, 0x44, 0x38 } // 62 b
	,{ 0x38, 0x44, 0x44, 0x44, 0x20 } // 63 c
	,{ 0x38, 0x44, 0x44, 0x48, 0x7f } // 64 d
	,{ 0x38, 0x54, 0x54, 0x54, 0x18 } // 65 e
	,{ 0x08, 0x7e, 0x09, 0x01, 0x02 } // 66 f
	,{ 0x0c, 0x52, 0x52, 0x52, 0x3e } // 67 g
	,{ 0x7f, 0x08, 0x04, 0x04, 0x78 } // 68 h
	,{ 0x00, 0x44, 0x7d, 0x40, 0x00 } // 69 i
	,{ 0x20, 0x40, 0x44, 0x3d, 0x00 } // 6a j 
	,{ 0x7f, 0x10, 0x28, 0x44, 0x00 } // 6b k
	,{ 0x00, 0x41, 0x7f, 0x40, 0x00 } // 6c l
	,{ 0x7c, 0x04, 0x18, 0x04, 0x78 } // 6d m
	,{ 0x7c, 0x08, 0x04, 0x04, 0x78 } // 6e n
	,{ 0x38, 0x44, 0x44, 0x44, 0x38 } // 6f o
	,{ 0x7c, 0x14, 0x14, 0x14, 0x08 } // 70 p
	,{ 0x08, 0x14, 0x14, 0x18, 0x7c } // 71 q
	,{ 0x7c, 0x08, 0x04, 0x04, 0x08 } // 72 r
	,{ 0x48, 0x54, 0x54, 0x54, 0x20 } // 73 s
	,{ 0x04, 0x3f, 0x44, 0x40, 0x20 } // 74 t
	,{ 0x3c, 0x40, 0x40, 0x20, 0x7c } // 75 u
	,{ 0x1c, 0x20, 0x40, 0x20, 0x1c } // 76 v
	,{ 0x3c, 0x40, 0x30, 0x40, 0x3c } // 77 w
	,{ 0x44, 0x28, 0x10, 0x28, 0x44 } // 78 x
	,{ 0x0c, 0x50, 0x50, 0x50, 0x3c } // 79 y
	,{ 0x44, 0x64, 0x54, 0x4c, 0x44 } // 7a z
	,{ 0x00, 0x08, 0x36, 0x41, 0x00 } // 7b {
	,{ 0x00, 0x00, 0x7f, 0x00, 0x00 } // 7c |
	,{ 0x00, 0x41, 0x36, 0x08, 0x00 } // 7d }
	,{ 0x10, 0x08, 0x08, 0x10, 0x08 } // 7e ~
	,{ 0x78, 0x46, 0x41, 0x46, 0x78 } // 7f DEL
};