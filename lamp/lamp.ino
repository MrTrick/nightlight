#include <NeoPixelBus.h> //From https://github.com/Makuna/NeoPixelBus/wiki
//#include <NeoPixelBrightnessBus.h> //From https://github.com/Makuna/NeoPixelBus/wiki

//====================================================
// Shared LED stuff

#define PIXEL_ROWS (7) //Seven levels of LEDs,
#define PIXEL_COLS (3) //and three sides/columns
#define PIXEL_COUNT (PIXEL_ROWS*PIXEL_COLS)

//NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> leds(PIXEL_COUNT); 
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> leds(PIXEL_COUNT); 
NeoTopology<RowMajorAlternatingLayout> layout(PIXEL_ROWS,PIXEL_COLS);

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
  buttons.setup();

  //Start with the nightlight
  //nightlight_begin();
  game.begin();
  
  Serial.println("ready");
}

//====================================================
// Main program loop

void loop() {
  static ButtonEvent last;
  ButtonEvent evt = buttons.check();
  if (evt != ButtonEvent::None) last = evt;

  switch(mode) {
    case Mode::Nightlight:
      nightlight.update();
      if (evt==ButtonEvent::Pressed) {
        game.begin();
      }
      break;
    
    case Mode::Game:*/
      game.update();
      game.swing(evt);
      if (game.gameover) {
        nightlight.begin();
      }
      //break;
    leds.Show();
}
