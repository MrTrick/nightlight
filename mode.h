//====================================================
// Mode base class
//====================================================
// Define a common interface for animation 'modes'
// and utility functions
//
//====================================================
#ifndef __MODE_H__
#define __MODE_H__

class Mode {
  public:   
  /**
   * Hold a reference to the next mode
   */
  Mode *next;

  /**
   * Called once at entry time
   */
  virtual void begin();

  /**
   * Called each frame to update the display
   */
  virtual void update();

  /**
   * Utility: Floating-point modulus function.
   * (not defined correctly by esp8266 core)
   */
  float fmod(float x, float y) { return x - (floor(x/y)*y); }

  /**
   * Utility: Return a triangle wave. 
   * Change amplitude by multiplying output, change period by multiplying input.
   */
   float tri(float i) { return 1.0 - abs(1-fmod(i,2)); }

};

#endif
