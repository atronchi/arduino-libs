#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 0); // Red
  //colorWipe(strip.Color(0, 0, 255), 0); // Blue

  
  //colorWipe(strip.Color(0, 32, 0), 10); // Green
  //colorWipe(strip.Color(255, 255, 255), 10); // White
  //Clear();


  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(200);
  //theaterChaseRainbow(50);
  
  //Strobe(500, 1, 3);
  //RWFlash(500, 255);
  uint16_t t = 100;
  uint8_t k = 255;
  
  colorBounce(k,0,0, t, 6);  //colorBounce(0,k,0, t, 128);  colorBounce(0,0,k, t, 128);
  //Span(0, strip.numPixels(), 128,128,128); strip.show();

  /*
  colorRun(k,0,0, t);
  colorRun(k,k,0, t);
  colorRun(0,k,0, t);
  colorRun(0,k,k, t);
  colorRun(0,0,k, t);
  colorRun(k,0,k, t);
  colorRun(k,k,k, t);
  */
}


void colorBounceT(uint8_t r, uint8_t g, uint8_t b, uint8_t wait, uint8_t width) {
  
  for(uint16_t x=0; x<strip.numPixels(); x++) {
    for(uint16_t t=0; t<10000; j++) {
      //uint16_t d = abs(i-j) * width + 1 ;
      //strip.setPixelColor(j, strip.Color(r/d, g/d, b/d));

      double e = exp( -pow(x-t, 2) / (2*pow(width, 2)) );
      strip.setPixelColor(j, strip.Color(
        (uint16_t) r*e,
        (uint16_t) g*e,
        (uint16_t) b*e
        ));
    }
    strip.show();
    delay(wait);
  }
  
  for(uint16_t i=strip.numPixels()-1; i>0; i--) {
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      int16_t imj = i - j;

      //uint16_t d = abs(imj) * width + 1 ;
      //strip.setPixelColor(j, strip.Color(r/d, g/d, b/d));
      
      double e =  exp( -pow(imj, 2) / pow(width, 2) );
      strip.setPixelColor(j, strip.Color(
        (uint16_t) r*e,
        (uint16_t) g*e,
        (uint16_t) b*e
        ));
    }
    strip.show();
    delay(wait);
  }
}


void colorBounce(uint8_t r, uint8_t g, uint8_t b, uint8_t wait, uint8_t width) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      int16_t imj = i - j;
      
      //uint16_t d = abs(imj) * width + 1 ;
      //strip.setPixelColor(j, strip.Color(r/d, g/d, b/d));

      double e = exp( -pow(imj, 2) / (2*pow(width, 2)) );
      strip.setPixelColor(j, strip.Color(
        (uint16_t) r*e,
        (uint16_t) g*e,
        (uint16_t) b*e
        ));
    }
    strip.show();
    delay(wait);
  }
  
  for(uint16_t i=strip.numPixels()-1; i>0; i--) {
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      int16_t imj = i - j;

      //uint16_t d = abs(imj) * width + 1 ;
      //strip.setPixelColor(j, strip.Color(r/d, g/d, b/d));
      
      double e =  exp( -pow(imj, 2) / pow(width, 2) );
      strip.setPixelColor(j, strip.Color(
        (uint16_t) r*e,
        (uint16_t) g*e,
        (uint16_t) b*e
        ));
    }
    strip.show();
    delay(wait);
  }
}


void Span(uint16_t sta, uint16_t stp, uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i=sta; i<stp; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b)); // red
  }
}

void Clear() {
  Span(0, strip.numPixels(), 0,0,0);
  strip.show();
}

void RWFlash(uint16_t wait, uint8_t br) {
  Span(0, strip.numPixels()/2, br,0,0);
  Span(strip.numPixels()/2, strip.numPixels(), br,br,br);
  strip.show(); delay(wait);

  Span(0, strip.numPixels()/2, br,br,br);
  Span(strip.numPixels()/2, strip.numPixels(), br,0,0);
  strip.show(); delay(wait);
}

void StrobeN(uint16_t sta, uint16_t stp, uint16_t wait, uint8_t br, uint8_t n) {
  for (uint16_t i=0; i<n; i++) {
    Span(sta, stp, br,br,br); strip.show(); delay(wait/n/2);
    Span(sta, stp, 0, 0, 0 ); strip.show(); delay(wait/n/2);
  }
}


// Flash n times per wait interval at brightness br
void Strobe(uint16_t wait, uint8_t br, uint8_t n) {
  StrobeN(strip.numPixels()/2, strip.numPixels(), wait,br,n);
  StrobeN(0, strip.numPixels()/2, wait,br,n);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


void colorRun(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      int16_t imj = i - j;
      uint16_t d = abs(imj) * 48 + 1 ;
      strip.setPixelColor(j, strip.Color(r/d, g/d, b/d));
    }
    strip.show();
    delay(wait);
  }
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
