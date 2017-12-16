#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#define BTN_TICK_MS (50)   //How often should we check the pin state?
#define BTN_HOLD_MS (5000) //How long is a button held down before triggering 'held'?
#define BTN_PIN_COM D1     //Common ground line (because splicing pins was a pain)
#define BTN_PIN_A D2       //Where are the buttons connected?
#define BTN_PIN_B D3       //
#define BTN_PIN_C D4       //

//What kind of button events occur?
enum class ButtonEvent { None, Pressed, Released, Held };

//Track timestamps when the button is last checked, and when it was pressed
uint32_t btn_timer_check, btn_timer_pressed;

/**
 * Initialise button concerns
 */
void button_setup() {
  pinMode(BTN_PIN_COM, OUTPUT);
  digitalWrite(BTN_PIN_COM, LOW);
  pinMode(BTN_PIN_A, INPUT_PULLUP);
  pinMode(BTN_PIN_B, INPUT_PULLUP);
  pinMode(BTN_PIN_C, INPUT_PULLUP);
  btn_timer_check = millis();
  btn_timer_pressed = 0; //Use zero to indicate button not pressed.
}

/**
 * Call in the loop()
 * Returns the latest button event, will mostly return none.
 */
ButtonEvent button_check() {
  uint32_t now = millis();
  //Limit the function to run only once each BTN_TICK_MS interval (for debouncing reasons)
  if (now < btn_timer_check + BTN_TICK_MS) return ButtonEvent::None;
  
  //Is the button down?
  if (digitalRead(BTN_PIN_A) == LOW || digitalRead(BTN_PIN_B) == LOW || digitalRead(BTN_PIN_C) == LOW) {
    //First pressed?
    if (!btn_timer_pressed) {
      Serial.println("Button pressed");
      btn_timer_pressed = now;
      return ButtonEvent::Pressed;
    }
    //Held on? (
    else if (now > btn_timer_pressed + BTN_HOLD_MS) {
      Serial.println("Button held"); 
      btn_timer_pressed = -1 - BTN_HOLD_MS; //Set to a high value so 'held' only occurs once
      Serial.println(btn_timer_pressed);
      return ButtonEvent::Held;
    }
  }
  //Or is the button up?
  else if (btn_timer_pressed) {
    Serial.println("Button released");      
    btn_timer_pressed = 0;
    return ButtonEvent::Released;
  }
  //If no other event occurred,
  return ButtonEvent::None;
}

#endif

