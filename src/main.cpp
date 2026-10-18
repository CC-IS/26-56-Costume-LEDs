// Note: for the purposes of this example code, blanking means turning off a given amount of LEDs by making them be the Colour black

// Import dependencies, because we are using Platformio we need to include the Arduino library as well as FastLED
#include <Arduino.h>
#include <FastLED.h>

// Define the amount of leds in our LED strip
#define numLeds 4

// Define which pin our LED strip's DIN pad is connected to
#define ledPin 2

// Define the leds array (our LED strip is considered an array in code, with each individual LED being an index in the array)
CRGB leds[numLeds];

// Helper function for demonstration purposes which blanks our LED strip 
void blankLeds(CRGB arr[], int num){
  // Makes all the leds up to num a given colour (in this case black, to turn them off)
  fill_solid(arr, num, CRGB::Black);
  // Show our changes on the physical leds
  FastLED.show();
  // A 2 second delay so that we can see that we are doing a different example
  delay(2000);
}

// Set up our leds
void setup() {
  // Attach our physical LEDs to our code so that we can interact with them
  /*
    Explanation of parameters:
      WS2812B: is the chipset used in our specific LED strip, that might be different depending on the LED strip.
      ledPin: which pin we are connecting to (we defined this earlier in code)
      GRB: the order in which the R[ed]G[reen]B[lue] pixels are handled in our chipset, in this case its GRB. Other chipsets might have different orders
      leds: our led array
      numLeds: the amount of leds that we are actually using
  */
  FastLED.addLeds<WS2812B, ledPin, GRB>(leds, numLeds);

  // Set the brightness of our LEDS to our desired value, possible values are 0-255, this can be changed in loop()
  FastLED.setBrightness(10);

  // Call our function to blank our leds
  blankLeds(leds, numLeds);
}

// The way that arduino code works, this 
void loop() {
  // The following are a set of examples of different functions that can be used with FastLED for some fun effects!

  // 1. Incrementally turn on the LEDS
  for (int i = 0; i < numLeds; i ++){
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
  delay(1000);

  // Call our function to blank our leds
  blankLeds(leds, numLeds);

  // 2. Make one of our leds move from one side of the strip to the other 2 times
  for (int i = 0; i < 3; i ++){
    int j = 0;
    // Make our current led green, show it and turn it blank before the next update
    while (j < numLeds){
      leds[j] = CRGB::Green;
      FastLED.show();
      leds[j] = CRGB::Black;
      j++;
      delay(250);
    }
    // Reset where j is and repeat the previous loop in the opposite direction by removing where j starts and ends
    j = numLeds-1;
    while (j >= 0){
      leds[j] = CRGB::Green;
      FastLED.show();
      leds[j] = CRGB::Black;
      j--;
      delay(250);
    }
  }

  // 3. Make all leds a given colour at the same time
  fill_solid(leds, numLeds, CRGB::Blue); 
  // You can for example make the only first 3 leds turn on the given color, by changing numLeds to 3, but note that when using fill_solid it will always turn on the leds up to the given amount starting from the 0th LED.
  FastLED.show();
  delay(2000);

  // Call our function to blank our leds
  blankLeds(leds, numLeds);

  // 4. Make a rainbow with our leds
  fill_rainbow(leds, numLeds, 0, 255/numLeds); 
  FastLED.show();
  delay(2000);
  
  // Call our function to blank our leds
  blankLeds(leds, numLeds);
}
