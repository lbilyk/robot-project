#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H



/// A generic graphics superclass that can handle all sorts of drawing. At a minimum you can subclass and provide drawPixel(). At a maximum you can do a ton of overriding to optimize. Used for any/all Adafruit displays!
#include "gfxfont.h"
#include "stm32f30x.h"
#include "Arduino.h"
/// A simple drawn button UI element


/// A GFX 1-bit canvas context for graphics
class GFXcanvas1 : public Adafruit_GFX {
 public:
  GFXcanvas1(uint16_t w, uint16_t h);
  ~GFXcanvas1(void);
  void     drawPixel(int16_t x, int16_t y, uint16_t color),
           fillScreen(uint16_t color);
  uint8_t *getBuffer(void);
 private:
  uint8_t *buffer;
};


/// A GFX 8-bit canvas context for graphics
class GFXcanvas8 : public Adafruit_GFX {
 public:
  GFXcanvas8(uint16_t w, uint16_t h);
  ~GFXcanvas8(void);
  void     drawPixel(int16_t x, int16_t y, uint16_t color),
           fillScreen(uint16_t color),
           writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

  uint8_t *getBuffer(void);
 private:
  uint8_t *buffer;
};


///  A GFX 16-bit canvas context for graphics
class GFXcanvas16 : public Adafruit_GFX {
 public:
  GFXcanvas16(uint16_t w, uint16_t h);
  ~GFXcanvas16(void);
  void      drawPixel(int16_t x, int16_t y, uint16_t color),
            fillScreen(uint16_t color);
  uint16_t *getBuffer(void);
 private:
  uint16_t *buffer;
};

#endif // _ADAFRUIT_GFX_H
