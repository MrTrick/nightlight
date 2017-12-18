//====================================================
// Nightlight Mode - Fade slowly between colours
//====================================================
#ifndef __NIGHTLIGHT_H__
#define __NIGHTLIGHT_H__

#define NIGHT_SPEED (PI/5000.0)  //How fast does it progress between colours?
#define NIGHT_SPREAD (0.05/NIGHT_SPEED) //How far apart are the LEDs, temporally?
#define NIGHT_BRIGHTNESS (0.2)   //How bright does it get?

class Nightlight {
  public:
  /**
   * Start nightlight mode
   */
  void begin() {
    mode = Mode::Nightlight;
  }

  /**
   * Animate the LEDs for a nightlight effect
   */
  void nightlight_update() {
    uint32_t t = millis();  
    for (uint8_t i=0;i<PIXEL_COUNT;i++) {
      float h,s,l;
      h=0.5-0.5*sin(t*NIGHT_SPEED*0.9);
      s=0.5-0.5*sin(t*NIGHT_SPEED);
      l=NIGHT_BRIGHTNESS;
      leds.SetPixelColor(i,HslColor(h,s,l));
      t+=NIGHT_SPREAD;
    }
  }
} nightlight;

#endif
