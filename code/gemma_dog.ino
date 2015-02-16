//Created by building on top of Adafruit example.
#include <Adafruit_NeoPixel.h>

#define PIN            1
#define NUMPIXELS      5
#define INPUT1         0
#define INPUT2         2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.show();
  pinMode(INPUT1, INPUT);
  pinMode(INPUT2, INPUT);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void setAll(uint32_t c){
  int i;
  for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
  }
  pixels.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(wait);
  }
}

//-----------------------Setup stuff above---------------

//To set a single pixel to a colour, use pixels.setPixelColor(3, pixels.Color(0,10,0));
//The 3 is the pixel number (don't forget they start at 0!!)
//To then display the pixel change, add this below pixels.show();

//To wait for a period of time, use delay(1000);    The 1000 is miliseconds (1000 is 1 second)


//2 other functions you may want to use is setAll() and colourWipe()
//setAll does just that, sets all the pixels to a single colour in 1 go. To use 
//setAll(pixels.Color(255, 0, 0));    where the 3 numbers are the colours

//colorWipe is used to turn each pixel to that colour one after each other. 
//colorWipe(pixels.Color(255, 0, 0), 50);     The 50 is the delay between the colours in miliseconds


//pixels.setPixelColor(3, pixels.Color(0,10,0));  pixels.show();
//setAll(pixels.Color(255, 0, 0));
//colorWipe(pixels.Color(255, 0, 0), 50);
//delay(1000);


//To use any of the code above, remember to remove the // in front of each command!

void loop() {
  
  if (digitalRead(INPUT1) == HIGH && digitalRead(INPUT2) == LOW) { 
    colorWipe(pixels.Color(0, 0, 255), 50);
    delay(500);
    colorWipe(pixels.Color(0, 0, 300), 50);
    delay(500);
  }
  
  if (digitalRead(INPUT1) == LOW && digitalRead(INPUT2) == HIGH) { 
  
  setAll(pixels.Color(255, 50, 0));
  delay(1000);
  setAll(pixels.Color(0, 0, 0));
  delay(500);
  }
  
  if (digitalRead(INPUT1) == HIGH && digitalRead(INPUT2) == HIGH) { 
    rainbowCycle(10);
  }
  
  if (digitalRead(INPUT1) == LOW && digitalRead(INPUT2) == LOW) { 
    setAll(pixels.Color(0, 0, 0));
  }
  
 
}
