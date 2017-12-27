//====================================================
// Technicolor Mode
//====================================================
// Fade slowly between colours, animate the LEDs with 
// a technicolor effect - the hue and saturation changes, 
// running around the length of the LED strip
//
//====================================================
#ifndef __TECHNICOLOR_H__
#define __TECHNICOLOR_H__

#define TECH_SPEED (PI/5000.0)  //How fast does it progress between colours?
#define TECH_SPREAD (0.05/TECH_SPEED) //How far apart are the LEDs, temporally?
#define TECH_BRIGHTNESS (0.2)   //How bright does it get?

class ModeTechnicolor: public Mode {
  public:
 
  /**
   * Start technicolor mode
   */
  void begin() {
    Serial.println("Mode: Technicolor");    
  }

  /**
   * Animate the LEDs with a technicolor effect - 
   * The hue and saturation changes, running around
   * the length of the LED strip
   */
  void update() {
    uint32_t t = millis();  
    for (uint8_t i=0;i<PIXEL_COUNT;i++) {
      leds.SetPixelColor(i,HslColor(
        0.5-0.5*sin(t*TECH_SPEED*0.9),  //Hue travels slowly from 0-1
        0.5-0.5*sin(t*TECH_SPEED),      //Saturation is slightly out of sync
        TECH_BRIGHTNESS                 //Luminance is constant
      ));
      t+=TECH_SPREAD;                   //The next LED is a bit further along in the cycle
    }
  }
  
} mode_technicolor;

#endif
