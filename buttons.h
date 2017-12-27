//====================================================
// Buttons
//====================================================
// Simple class to detect button presses and 
// return events
//
//====================================================
#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#define BTN_TICK_MS (100)  //How often should we check the pin state?
#define BTN_HOLD_MS (2000) //How long is a button held down before triggering 'held'?

#define BTN_PIN_COM D1     //Common ground line (because splicing pins was a pain)
//#define BTN_PIN_A D2       //Where are the buttons connected?
//#define BTN_PIN_B D3       //
#define BTN_PIN_C D4       //

//What kind of button events occur?
enum class ButtonEvent { None, Pressed, Released, Held };

class Buttons {
protected:
  //Track timestamps when the button is last checked, and when it was pressed
  uint32_t timer_pressed;

public:
  /**
   * Initialise button concerns
   */
  void setup() {
    //Make this pin a 'ground' (not usually a good idea, but needs less wiring)
    pinMode(BTN_PIN_COM, OUTPUT);
    digitalWrite(BTN_PIN_COM, LOW);
    
    //pinMode(BTN_PIN_A, INPUT_PULLUP);
    //pinMode(BTN_PIN_B, INPUT_PULLUP);
    pinMode(BTN_PIN_C, INPUT_PULLUP);
  
    timer_pressed = 0; //Use zero to indicate button not pressed.

    Serial.print("BUTTONS...");
  }

  /**
   * Call in the loop()
   * Returns the latest button event, will mostly return none.
   */
  ButtonEvent check() {
    static uint32_t prev;
    uint32_t now = millis();
    //Limit the function to run only once each BTN_TICK_MS interval (for debouncing reasons)
    if (now - prev > BTN_TICK_MS) prev=now; else return ButtonEvent::None;
    
    //Is 'the' button pushed down? Take at least two out of three
    //bool a = digitalRead(BTN_PIN_A)==LOW;
    //bool b = digitalRead(BTN_PIN_B)==LOW;
    //bool c = digitalRead(BTN_PIN_C)==LOW;
    //if(a+b+c) { 
    if(digitalRead(BTN_PIN_C)==LOW) {
      //First pressed?
      if (!timer_pressed) {
        Serial.print(now); Serial.print(" "); Serial.println("Button pressed");
        timer_pressed = now;
        return ButtonEvent::Pressed;
      }
      //Held on? (
      else if (now > timer_pressed + BTN_HOLD_MS) {
        Serial.print(now); Serial.print(" "); Serial.println("Button held");
        timer_pressed = -1 - BTN_HOLD_MS; //Set to a high value so 'held' only occurs once
        return ButtonEvent::Held;
      }
    }
    //Or is the button up?
    else if (timer_pressed) {
      Serial.print(now); Serial.print(" "); Serial.println("Button released");
      timer_pressed = 0;
      return ButtonEvent::Released;
    }
    //If no other event occurred,
    return ButtonEvent::None;
  }
} buttons;

#endif

