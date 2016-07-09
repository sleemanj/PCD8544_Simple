#include "PCD8544_Simple.h"
#include <SPI.h>

PCD8544_Simple::PCD8544_Simple()
{
}

void PCD8544_Simple::begin(bool invert)
{
  this->begin(invert, 0xB0, 0x04, 0x12);
}

void PCD8544_Simple::begin(bool invert, uint8_t vop, uint8_t tempCoef, uint8_t bias)
{
  PCD8544_PORT |= (PIN_DC | PIN_RESET | PIN_CE);
  PCD8544_DDR |= (PIN_DC | PIN_RESET | PIN_CE);
  SPI.begin();
  
  // LCD init section:
  
  uint8_t invertSetting = invert ? 0x0D : 0x0C;
  // Must reset LCD first!
  PCD8544_PORT &= ~PIN_RESET;
  PCD8544_PORT |= PIN_RESET;

  this->writeLcd(PCD8544_COMMAND, 0x21); //Tell LCD that extended commands follow
  this->writeLcd(PCD8544_COMMAND, vop); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
  this->writeLcd(PCD8544_COMMAND, tempCoef); //Set Temp coefficent
  this->writeLcd(PCD8544_COMMAND, bias); //LCD bias mode 1:48: Try 0x13 or 0x14. Mine works best with 1:65/1:65

  this->writeLcd(PCD8544_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
  this->writeLcd(PCD8544_COMMAND, invertSetting); //Set display control, normal mode. 0x0D for inverse

  this->clear();
}

size_t PCD8544_Simple::write(uint8_t data)
{  
  if(data == '\n')  // Newline means go to the next line
  {        
    this->m_Position = ((this->m_Position / PCD8544_X_PIXELS) + 1) * PCD8544_X_PIXELS;
  }
  
  // If we are out of room in the buffer for the entire character
  // (including if we have just walked across the buffer end due to the 
  // newline on the last line)
  if(this->m_Position + 5 >= BUF_LEN)
  {
    // shift Rows:1..n up to 0..n-1 
    for(uint8_t y = 1; y < PCD8544_ROWS; y++)
    {
      memcpy(this->m_Buffer+((y-1)*PCD8544_X_PIXELS), this->m_Buffer+(y * PCD8544_X_PIXELS ), PCD8544_X_PIXELS);             
    }       
    
    // Clear and seek to th last line.
    memset(this->m_Buffer+((PCD8544_ROWS-1)*PCD8544_X_PIXELS), 0, PCD8544_X_PIXELS);
    this->gotoXY(0,PCD8544_ROWS-1);
  }
  
  // Non-ASCII characters are not supported.
  // We pretend they are though otherwise all the rest of the 
  // string is dropped (by Print::write(const uint8_t *buffer, size_t size))
  if (data < 0x20 || data > 0x7F) return 1;
  
  if(this->textInversion)
  {
    for(uint8_t x = 0; x < 5; x++)
    {
      this->m_Buffer[this->m_Position + x] = ~pgm_read_byte(ASCII[data - 0x20]+x);      
    }
  }
  else
  {
    memcpy_P(this->m_Buffer + this->m_Position, ASCII[data - 0x20], 5);
  }
  
  this->m_Position += 5;
  
  if(this->m_Position < BUF_LEN-1)
  {
    // Set the next pixel row to blank for spaces between characters
    this->m_Buffer[this->m_Position] = this->textInversion ? 0xFF : 0x00;
    this->m_Position++;
  }
  
  return 1;
}

void PCD8544_Simple::invertText(uint8_t inversionStatus)
{
  textInversion = inversionStatus;
}

void PCD8544_Simple::clear(bool render)
{
  memset(this->m_Buffer, 0x00, sizeof(this->m_Buffer));
  if (render)
    this->update();
  this->gotoXY(0, 0);
}

uint8_t PCD8544_Simple::gotoXY(uint8_t x, uint8_t y) 
{ 
  if (x >= PCD8544_X_PIXELS || y >= PCD8544_ROWS) return PCD8544_ERROR;
 // this->writeLcd(PCD8544_COMMAND, 0x80 | x);  // Column (Pixel).
 // this->writeLcd(PCD8544_COMMAND, 0x40 | y);  // Bank (Rows).
  this->m_Position = (PCD8544_X_PIXELS * y) + x;
  return PCD8544_SUCCESS;
}

uint8_t PCD8544_Simple::writeBitmap(const uint8_t *bitmap, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
  //if (x >= PCD8544_X_PIXELS || y >= PCD8544_Y_PIXELS) return;
  //this->gotoXY(x, y);
  //uint16_t pos = this->m_Position;
  //for (uint8_t y = 0; y < height; y++)
  //{
  //  memcpy(this->m_Buffer + pos, bitmap + (y*width), width);
  //  pos += PCD8544_X_PIXELS;
  //}
  
  if (this->gotoXY(x, y) == PCD8544_ERROR) return PCD8544_ERROR;

  uint8_t *pos = this->m_Buffer + this->m_Position;
    const uint8_t *maxY = bitmap + height * width;  

  for (const uint8_t *y = (uint8_t*) bitmap; y < maxY; y += width)
  {
    memcpy(pos, y, width);
    pos += PCD8544_X_PIXELS;
  }
  return PCD8544_SUCCESS;
}

void PCD8544_Simple::update()
{ 
 // this->gotoXY(0, 0);
  this->writeLcd(PCD8544_DATA, this->m_Buffer, BUF_LEN);
}

uint8_t PCD8544_Simple::renderString(uint8_t x, uint8_t y, uint16_t length)
{
  if (this->gotoXY(x, y) == PCD8544_ERROR) return PCD8544_ERROR;
  length *= 6;
  this->writeLcd(PCD8544_DATA, this->m_Buffer + this->m_Position, length);
  this->m_Position += length;
  return PCD8544_SUCCESS;
}

void PCD8544_Simple::setPixel(uint8_t x, uint8_t y, uint8_t value)
{
  if (x >= PCD8544_X_PIXELS || y >= PCD8544_Y_PIXELS) return;
  uint8_t bank = y / 8;
  uint8_t bitMask = 1 << (y % 8);
  uint8_t &byte = this->m_Buffer[(PCD8544_X_PIXELS * bank) + x];
  if (value)
    byte |= bitMask;
  else
    byte &= ~bitMask;
}

// Bresenham's Line Algorithm
// https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
void PCD8544_Simple::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) 
{ 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    setPixel(x0,y0,1);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

// Rectangles using Bresenham
// x & y are top left corner
void PCD8544_Simple::drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
  drawLine(x, y, x + width, y);                       // Top Line
  drawLine(x, y, x , y + height);                     // Left Line
  drawLine(x+width, y, x+width , y + height);         // Right Line
  drawLine(x, y+height, x + width , y + height);      // Bottom Line    
}

// A filled rectangle is a series of lines
// again x & y are top left corner
void PCD8544_Simple::drawFilledRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
  while(width)
  {
    drawLine(x+width,y,x+width,y+height);
    width--;
  }
}

/*
uint8_t PCD8544_Simple::drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool fill)
{
  
  
  if (x >= PCD8544_X_PIXELS || y >= PCD8544_Y_PIXELS || width == 0 || height == 0) return PCD8544_ERROR;

  // Calculate the bitmasks for the pixels.
  uint8_t bottom = y + height - 1;
  uint8_t bankTop = y / 8;
  uint8_t bankBottom = bottom / 8;
  uint8_t bitMaskTop = 0x01;
  uint8_t bitMaskBottom = 0x80;
  uint8_t bitMaskTopFill = 0xFF;
  uint8_t bitMaskBottomFill = 0xFF;
  bitMaskTop <<= (y % 8);
  bitMaskBottom >>= 7 - (bottom % 8);
  bitMaskTopFill <<= (y % 8);
  bitMaskBottomFill >>= 7 - (bottom % 8);

  // When fill is selected, we'll use the FillMask.
  if (fill)
  {
    bitMaskTop = bitMaskTopFill;
    bitMaskBottom = bitMaskBottomFill;
  }

  // When the rectangle fits in a single bank, we AND the top and bottom masks
  // So that we only fill the required area on the LCD.
  if (bankTop == bankBottom)
  {
    bitMaskTop = fill ? bitMaskTop & bitMaskBottom : bitMaskTop | bitMaskBottom;
    bitMaskTopFill &= bitMaskBottomFill;
  }
  this->gotoXY(x, bankTop);

  // Write the left 'side' of the rectangle on the top bank.
  this->m_Buffer[this->m_Position++] |= bitMaskTopFill;
  // Write a line or a fill.
  for (uint8_t i = 1; i < width-1; i++)
    this->m_Buffer[this->m_Position++] |= bitMaskTop;
  // Write the right 'side' of the rectangle on the top bank.
  if (width > 1)
    this->m_Buffer[this->m_Position++] |= bitMaskTopFill;

  this->m_Position += (PCD8544_X_PIXELS - width);

  // Write a fill across the middle banks or two sides of the rectangle.
  if (bankBottom - bankTop > 1)
  {
      for (uint8_t i = bankTop + 1; i < bankBottom; i++)
      {
        if (fill)
          memset(this->m_Buffer + this->m_Position, 0xFF, width);
        else
        {
          this->m_Buffer[this->m_Position] = 0xFF;
          this->m_Buffer[this->m_Position+width-1] = 0xFF;
        }
        this->m_Position += PCD8544_X_PIXELS;
      }
  }
  // If the rectangle spans across more than one bank,
  // apply the same logic for the bottom as the top.
  if (bankBottom > bankTop)
  {
    this->m_Buffer[this->m_Position++] |= bitMaskBottomFill;
    for (uint8_t i = 1; i < width-1; i++)
      this->m_Buffer[this->m_Position++] |= bitMaskBottom;
    if (width > 1)
      this->m_Buffer[this->m_Position++] |= bitMaskBottomFill;
  }
  return PCD8544_SUCCESS;
}
*/


// https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C
// This seems to be the same algo that Adafruit uses in their GFX library
// it produces a better result than the (Bresenham?) algorithm presented 
// on https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

void PCD8544_Simple::drawCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{  
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    setPixel(x0, y0 + radius, 1);
    setPixel(x0, y0 - radius, 1);
    setPixel(x0 + radius, y0, 1);
    setPixel(x0 - radius, y0, 1);
 
    while(x < y) 
    {
        if(f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;    
        setPixel(x0 + x, y0 + y, 1);
        setPixel(x0 - x, y0 + y, 1);
        setPixel(x0 + x, y0 - y, 1);
        setPixel(x0 - x, y0 - y, 1);
        setPixel(x0 + y, y0 + x, 1);
        setPixel(x0 - y, y0 + x, 1);
        setPixel(x0 + y, y0 - x, 1);
        setPixel(x0 - y, y0 - x, 1);
    }
}


// This needs work, due the aliasing it doesn't result in a completely
// filled circle, although the result I quite like....
void PCD8544_Simple::drawFilledCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  while(radius > 0)
  {
    drawCircle(x0, y0, radius--);
  }
  setPixel(x0, y0, 1);
}



void PCD8544_Simple::writeLcd(uint8_t dataOrCommand, const uint8_t *data, uint16_t count)
{
  PCD8544_PORT = (PCD8544_PORT & ~PINS_CE_DC) | dataOrCommand;
  //for (uint16_t i = 0; i < count; i++)
  //  SPI.transfer(data[i]);
    for (uint16_t i = count; i > 0; i--)
    SPI.transfer(data[count-i]);
  PCD8544_PORT |= PIN_CE;
}

void PCD8544_Simple::writeLcd(uint8_t dataOrCommand, uint8_t data)
{
  PCD8544_PORT = (PCD8544_PORT & ~PINS_CE_DC) | dataOrCommand;
  SPI.transfer(data);
  PCD8544_PORT |= PIN_CE;
}

