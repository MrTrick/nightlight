//====================================================
// Ants Mode
//====================================================
// Alternating pixels crawl slowly around the strip
//
//====================================================
#ifndef __ANTS_H__
#define __ANTS_H__

#define ANTS_SPEED (1/400.0)
#define ANTS_BRIGHTNESS (0.2)
#define ANTS_SPACING (3.0)

class ModeAnts: public Mode {
  public:

  /**
   * Start ants mode
   */
  void begin() {
    Serial.println("Mode: Ants");
  }

  /**
   * Crawl - animate an insect population
   */
  void update() {
    float t = millis()*ANTS_SPEED;
    for(uint8_t i=0;i<PIXEL_COUNT;i++) {
      float h=0,s=0,b=constrain(ANTS_BRIGHTNESS*sin(t),0,1);
      leds.SetPixelColor(i,HsbColor(h,s,b));
      t+=ANTS_SPACING*(PI/2);
    }
  }
    
} mode_ants;

#endif
