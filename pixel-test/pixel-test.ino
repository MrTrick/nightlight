
#include <NeoPixelBus.h>
#define PIXEL_COUNT 21
#define NIGHT_SPEED (PI/5000)   //How fast does it switch between colours?
#define NIGHT_BRIGHTNESS (32.0) //How bright does it get? Float, max is 102.0

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PIXEL_COUNT);

void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for serial attach
    Serial.println();
    Serial.print("Initializing...");
    Serial.flush();

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();

    Serial.println("done");
}

float _fmod(float x, float y) { return x - (round(x/y)*y); }


void loop()
{
  float t = millis()*NIGHT_SPEED;
    
  for(uint8_t i=0;i<PIXEL_COUNT;i++) {
    t+=0.1;
    int r = (exp(sin(t)) - 0.36787944)*NIGHT_BRIGHTNESS;
    int g = (exp(sin(t+PI/3)) - 0.36787944)*NIGHT_BRIGHTNESS;
    int b = (exp(sin(t+2*PI/3)) - 0.36787944)*NIGHT_BRIGHTNESS;
    RgbColor c = RgbColor(r,g,b);
    strip.SetPixelColor(i,c);
  }
  strip.Show();
  delay(20);
}

