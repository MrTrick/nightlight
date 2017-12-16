//====================================================
// Nightlight Mode - Fade slowly between colours
//====================================================
#ifndef __NIGHTLIGHT_H__
#define __NIGHTLIGHT_H__

#define NIGHT_SPEED (PI/5000)   //How fast does it progress between colours?
#define NIGHT_BRIGHTNESS (32.0) //How bright does it get? Float, max is 102.0

void nightlight_begin() {
  mode = Mode::Nightlight;
}

/**
 * Animate the LEDs for a nightlight effect
 */
void nightlight_update() {
  float t = millis()*NIGHT_SPEED;  
  for(uint8_t i=0;i<PIXEL_COUNT;i++) {
    t+=0.1;
    leds.SetPixelColor(i, RgbColor(
      (exp(sin(t)) - 0.36787944)*NIGHT_BRIGHTNESS,
      (exp(sin(t+PI/3)) - 0.36787944)*NIGHT_BRIGHTNESS,
      (exp(sin(t+2*PI/3)) - 0.36787944)*NIGHT_BRIGHTNESS
    ));
  }
  leds.Show();
}

#endif
