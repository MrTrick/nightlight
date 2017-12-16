#include <NeoPixelBus.h> //From https://github.com/Makuna/NeoPixelBus/wiki
#include <NeoPixelBrightnessBus.h> //From https://github.com/Makuna/NeoPixelBus/wiki

//====================================================
// Shared LED stuff

#define PIXEL_ROWS (7) //Seven levels of LEDs,
#define PIXEL_COLS (3) //and three sides/columns
#define PIXEL_COUNT (PIXEL_ROWS*PIXEL_COLS)

NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> leds(PIXEL_COUNT); 
NeoTopology<RowMajorAlternatingLayout> topo(PIXEL_COLS, PIXEL_ROWS);

//====================================================
// Program components

enum class Mode { Game, Nightlight };
Mode mode;

#include "buttons.h"
#include "nightlight.h"
#include "game.h"

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
  button_setup();

  //Start with the nightlight
  nightlight_begin();
  
  Serial.println("ready");
}

//====================================================
// Main program loop

void loop() {
  ButtonEvent evt = button_check();

  switch(mode) {
    case Mode::Nightlight:
      nightlight_update();
      if (evt==ButtonEvent::Pressed) {
        game_begin();
      }
      break;
    
    case Mode::Game:
      game_update();
      if (game_over) {
        nightlight_begin();
      }
      break;
  }
}
