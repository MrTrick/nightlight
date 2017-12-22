#include <NeoPixelBrightnessBus.h> //From https://github.com/Makuna/NeoPixelBus/wiki

//====================================================
// Shared LED stuff

#define PIXEL_ROWS (7) //Seven levels of LEDs,
#define PIXEL_COLS (3) //and three sides/columns
#define PIXEL_COUNT (PIXEL_ROWS*PIXEL_COLS)

NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> leds(PIXEL_COUNT); 
NeoTopology<RowMajorAlternatingLayout> layout(PIXEL_ROWS,PIXEL_COLS);

//====================================================
// Program components

#include "buttons.h"
#include "mode.h"
#include "mode_ants.h"
#include "mode_bounce.h"
#include "mode_technicolor.h"
#include "mode_off.h"

Mode *mode;

//====================================================
// Initialisation

void setup()
{
  //Configure the serial port
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  Serial.println();
  Serial.print("Initializing...");
  Serial.flush();

  //LEDs
  leds.Begin();   // Reset all the pins to an 'off' state
  leds.Show();    

  //Button
  buttons.setup();

  //Set initial mode and link modes together in order
  mode_ants.next = &mode_bounce;
  mode_bounce.next = &mode_technicolor;
  mode_technicolor.next = &mode_ants;
  mode_off.next = &mode_ants;
  mode = &mode_ants;
  mode->begin();
    
  Serial.println("Nightlight ready");
}

//====================================================
// Main program loop

void loop() {
  //Change mode?
  ButtonEvent evt = buttons.check();
  if (evt == ButtonEvent::Released) {
    Serial.println("Change mode");
    mode = mode->next;
    mode->begin();
  } else if (evt == ButtonEvent::Held) {
    Serial.print("Switching off...");
    mode = &mode_off;
    mode->begin();
    //Wait for the button to be released before continuing.
    do yield(); while(buttons.check() != ButtonEvent::Released);
    Serial.println("done.");
  }

  //Animate
  mode->update();
  leds.Show();
}
