//====================================================
// Game Mode
//====================================================
// A simple reaction game, where a pixel travels to 
// the top of the columns of LEDs and back down. 
// Press the button when the pixel is at the bottom,
// and it 'bounces', getting brighter and changing 
// colours each time.
//
// Miss and the game is over.
//====================================================
#ifndef __GAME_H__
#define __GAME_H__

float game_d, game_v, game_a; //Current displacement, velocity, acceleration
float game_u;                 //Initial velocity, dynamically set after each 'bounce'
bool game_over; //Becomes set when the game is over


//uint32_t =


void game_begin() {
  game_d = 0;
  game_u = 0.2;
  game_v = game_u;
  game_a = (game_u*game_u) / (2*(PIXEL_COLS-1)); //Choose acceleration that gets it to the top

  mode = Mode::Game;
}

void game_update() {
  //float t = millis();
  float r = (millis()/1000)%6;
  
 /* for(uint8_t c=0;
  
  for(uint8_t i=0;i<PIXEL_COUNT;i++) {
    t+=0.1;
    leds.SetPixelColor(i, RgbColor(
      (exp(sin(t)) - 0.36787944)*NIGHT_BRIGHTNESS,
      (exp(sin(t+PI/3)) - 0.36787944)*NIGHT_BRIGHTNESS,
      (exp(sin(t+2*PI/3)) - 0.36787944)*NIGHT_BRIGHTNESS
    ));
  }
  leds.Show();*/
  
};


float fmod(float x, float y) { return x - (round(x/y)*y); }


void game_bounce() {
  fmod(1.0,2.0);
}

#endif
