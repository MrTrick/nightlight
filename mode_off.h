//====================================================
// 'Off' Mode
//====================================================
// What is sounds like.
//
//====================================================
#ifndef __OFF_H__
#define __OFF_H__

class ModeOff: public Mode {
  public:

  /**
   * Switch off
   */
  void begin() {
    Serial.println("Switching off");
    leds.ClearTo(RgbColor(0));
    leds.Show();
  }
  /**
   * And stay off
   */
  void update() {}
  
} mode_off;

#endif
