//====================================================
// Technicolor Mode - Fade slowly between colours
//====================================================
#ifndef __TECHNICOLOR_H__
#define __TECHNICOLOR_H__

#define TECH_SPEED (PI/5000.0)  //How fast does it progress between colours?
#define TECH_SPREAD (0.05/TECH_SPEED) //How far apart are the LEDs, temporally?
#define TECH_BRIGHTNESS (0.2)   //How bright does it get?

class Technicolor: public Mode {
  public:
  /**
   * Start technicolor mode
   */
  void begin() {}

  /**
   * Animate the LEDs for a technicolor effect
   */
  void technicolor_update() {
    uint32_t t = millis();  
    for (uint8_t i=0;i<PIXEL_COUNT;i++) {
      float h,s,l;
      h=0.5-0.5*sin(t*TECH_SPEED*0.9);
      s=0.5-0.5*sin(t*TECH_SPEED);
      l=TECH_BRIGHTNESS;
      leds.SetPixelColor(i,HslColor(h,s,l));
      t+=TECH_SPREAD;
    }
  }
} mode_technicolor;

#endif
