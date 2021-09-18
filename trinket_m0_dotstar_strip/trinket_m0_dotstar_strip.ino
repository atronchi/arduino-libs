/* 
 *  https://github.com/FastLED/FastLED/wiki/SPI-Hardware-or-Bit-banging
 *  https://core-electronics.com.au/tutorials/what-are-dotstar-leds.html
 * 
 * Project: https://www.instructables.com/id/Animated-LED-Scarf/ 
 * Debug upload: https://www.amazon.com/ask/questions/Tx22O6W041Q8PVM/ref=ask_dp_dpmw_al_hza
 * Drivers for KOOKYE : http://www.wch.cn/download/CH341SER_MAC_ZIP.html
 */

//This is inspired by the code with Adafruit's Animated
//Neopixel Glow Fur Scarf & the color palettes included within 
//the FastLED library. I've included one additional palette to play with

#include <FastLED.h>
#include "colorutils.h"
#include "colorpalettes.h"

#define NUM_LEDS    144  // adjust this to the number of LEDs you have: 16 or 50
#define LED_TYPE    APA102 // adjust this to the type of LEDS. This is for Neopixels
#define DATA_PIN    4 // MOSI -> green wire -> DI
#define CLOCK_PIN   3 // SCK -> yellow wire -> CI

#define BRIGHTNESS  64 // 255 is full brightness, 128 is half
#define SATURATION  255 // 0-255, 0 is pure white, 255 is fully saturated color
#define COLOR_ORDER BRG  // Try mixing up the letters (RGB, GBR, BRG, etc) for a whole new world of color combinations

//#define UPDATES_PER_SECOND 100
uint16_t gHue = 0;
uint8_t  gHueDelta = 1;

/*
void loop() {
  gHue += gHueDelta; // compute new hue
  gHue = gHue % 360; // bring hue back in range
*/

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette( PartyColors_p );
TBlendType    currentBlending;
uint8_t       colorLoop = 1;

uint16_t STEPS = 0;
uint16_t SPEED = 0;
uint16_t WAIT = 0;

void setup() {
  delay( 2000 ); // power-up safety delay
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,CLOCK_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  /*
   * https://github.com/FastLED/FastLED/wiki/SPI-Hardware-or-Bit-banging
   * 
   * FastLED.addLeds<APA102,DATA_PIN,CLOCK_PIN,RGB,DATA_RATE_MHZ(10)>(leds,NUM_LEDS);
   * FastLED.addLeds<APA102,DATA_PIN,CLOCK_PIN>(leds,NUM_LEDS);
   */
   
  FastLED.setBrightness(  BRIGHTNESS );
  currentBlending;

//FastLED has a bunch of built-in "palettes" to choose from:
//RainbowColors_p     is all the colors of the rainbow
//PartyColors_p     is all the colors of the rainbow minus greens
//RainbowStripeColors_p is all the colors of the rainbow divided into stripes
//HeatColors_p      is reds and yellows, white, and black
//LavaColors_p      is more reds and orangey colors
//ForestColors_p    is greens and yellows
//OceanColors_p     is lots of blues and aqua colors
//CloudColors_p     is blues and white

//The group of colors in a palette are sent through a strip of LEDS in speed and step increments youve chosen
//You can change the SPEED and STEPS to make things look exactly how you want
//SPEED refers to how fast the colors move.  Higher numbers = faster motion
//STEPS refers to how wide the bands of color are.  1 = more like a gradient, 10 = more like stripes

//{currentPalette = RainbowColors_p;  SPEED = 100; STEPS = 10;}
//{currentPalette = ForestColors_p;     SPEED = 40; STEPS = 8;}
//{currentPalette = PartyColors_p;    SPEED = 30; STEPS = 7;}
//{currentPalette = OceanColors_p;    SPEED = 20; STEPS = 6;}
//{currentPalette = LavaColors_p;   SPEED = 10; STEPS = 5;}

//{currentPalette = RainbowColors_p;    SPEED = 5; STEPS = 1;}
{currentPalette = RainbowColors_p;    WAIT = 0; STEPS = 1;}
}

void loop() {
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  //FastLED.delay(1000 / SPEED);  
  FastLED.delay(WAIT);  
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += STEPS;              
  }
}
