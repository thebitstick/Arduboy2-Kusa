/*
   Kusa.ino
   @TheBitStick
   Pocket Watch for Arduboy
   Uses Arduboy2, Keyboard, 8x8DotJPFont libraries
*/

#include <Arduboy2.h>
#include "Keyboard.h"
#include <misaki_font.h>

Arduboy2 arduboy;

#define FRAME_RATE 15

PROGMEM const byte kusa[] = { 0xf0, 0x51,0x57, }; // くさ

// from emutyworks/8x8DotJPFont @ Github, file: 8x8DotJPFont/JPLang8x8Text/JPLang8x8Text.ino
// takes array of unsigned 8-bit integers that represent characters in special format
// to draw katakana and hiragana glyphs in Japanese
// edited to the bare essentials and edited with understandable variables
void drawText(byte x0, byte y0, byte *bitmap, byte size) {
  byte currentByte;
  byte byteType;

  for (byte i = 0; i < size; i++) {
    currentByte = pgm_read_byte_near(bitmap + i);

    switch (currentByte) {
      case MISAKI_FONT_F0_PAGE:
        byteType = MISAKI_FONT_F0_PAGE;
        continue;
      case MISAKI_FONT_F1_PAGE:
        byteType = MISAKI_FONT_F1_PAGE;
        continue;
    }

    switch (byteType) {
      case MISAKI_FONT_F0_PAGE:
        arduboy.drawBitmap(x0, y0,  misaki_font_f0[currentByte], MISAKI_FONT_F0_W, 8);
        x0 = x0 + 8;
        break;
      case MISAKI_FONT_F1_PAGE:
        arduboy.drawBitmap(x0, y0,  misaki_font_f1[currentByte], MISAKI_FONT_F1_W, 8);
        x0 = x0 + 4;
        break;
    }
  }
}

// begins standard Arduboy cycle and sets framerate
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);

  Serial.begin(9600);
  Keyboard.begin();
}

// the main loop where everything happens
// event catching!
void loop() {
  if (!(arduboy.nextFrame())) return;

  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
    Keyboard.write('k');
    Keyboard.write('u');
    Keyboard.write('s');
    Keyboard.write('a');
  }

  arduboy.clear();
  
  drawText(5, 5, kusa, sizeof(kusa));

  arduboy.display(); // display everything in the current loop
}
