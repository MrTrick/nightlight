//====================================================
// Bounce Mode
//====================================================
// A pixel travels to the top of the columns of LEDs 
// and back down. 
// The hue, saturation and speed changes each time
// the pixel bounces.
//
//====================================================
#ifndef _BOUNCE_H__
#define _BOUNCE_H__

#define BOUNCE_TICK_MS (20)     // Run a frame each 'tick'
#define BOUNCE_INITIAL_U (0.1)  // Initial upward velocity of the pixel

class Bounce: public Mode {
  protected:
  float u,d,v,a;  // Initial velocity, current displacement, velocity, acceleration
  uint8_t score;  // How many times was it bounced?
  float hue,sat;  // Current colour

  public:
  /**
   * Start a new bounce
   */
  void begin() {
    u = BOUNCE_INITIAL_U;
    d = 0;
    v = u;
    a = -(u*u) / (2*(PIXEL_ROWS-1)); //Physics; what acceleration stops at the top? v^2 = u^2 + 2*a*s
    score = 0;
  }

  /**
   * Run the bounce loop
   */
  void update() {
    //Limit the update rate to the given framerate - return early if called too soon.
    static uint32_t prev;
    if (millis()-prev > BOUNCE_TICK_MS) prev=millis(); else return;

    //Move the pixel
    d+=v+=a;

    //Update LEDs to show its location 
    //(d is a float so it's approximated, pixels to either side are lit to smooth it)
    for(uint8_t r=0;r<PIXEL_ROWS;r++) {      
      HsbColor color = HsbColor(
        fmod(0.13*score,1.0),
        constrain(0.5+0.03*score,0.0,1.0),
        constrain(1.0-abs(d-r),0.0,1.0)
      );
      for(uint8_t c=0;c<PIXEL_COLS;c++) leds.SetPixelColor(layout.Map(r,c), color);      
    }    

    //Bounce?
    if (d<0) {
      d*=-1; 
      v*=-1;
      score++;
    }
  }
  
} mode_bounce;
  
#endif
