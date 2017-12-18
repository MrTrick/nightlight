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
#ifndef _GAME_H__
#define _GAME_H__

#define GAME_TICK_MS (20)     // Run a frame each 'tick'
#define GAME_INITIAL_U (0.1)  // Initial upward velocity of the pixel

class Game {
  public:
  float u,d,v,a;  // Initial velocity, current displacement, velocity, acceleration
  bool gameover;  // Is the game finished?
  bool hit;       // Did the player hit the pixel successfully?
  uint8_t score;  // How many times was it bounced?
  float hue,sat;  // Current colour
  
  float fmod(float x, float y) { return x - (round(x/y)*y); }

  /**
   * Start a new game
   */
  void begin() {
    u = GAME_INITIAL_U;
    d = 0;
    v = u;
    a = -(u*u) / (2*(PIXEL_ROWS-1)); //Physics; what acceleration stops at the top? v^2 = u^2 + 2*a*s
    gameover = false;
    hit = false;
    score = 0;
    mode = Mode::Game;
  }

  /**
   * Run the game loop
   */
  void update() {
    //Limit the update rate to the given framerate - return early if called too soon.
    static uint32_t prev;
    if (millis()-prev > GAME_TICK_MS) prev=millis(); else return;

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
    if (d<0 && hit) {
      Serial.println("BOUNCE");
      hit = false;
      d*=-1; 
      v*=-1;
      score++;
    }
  }

  /**
   * Swing at the ball.
   * If the button was pressed in the right location, register that it 'hit'
   */
   void swing(ButtonEvent evt) {
    if (evt==ButtonEvent::Pressed) {
      Serial.print("PRESSED "); Serial.println(d, 2);
      if (d<1.2) {
        Serial.println("HIT");
        hit = true;
      }
    }
   }
   
} game;
  
#endif
