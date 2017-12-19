
class Mode {
  public: 
  //Mode() {};
  
  /**
   * Keep a reference to the next mode
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
  float fmod(float x, float y) { return x - (round(x/y)*y); }
};
