#include <FastLED.h>

#include <Adafruit_NeoPixel.h>

// the data pin for the NeoPixels
#define PIN 6

// How many NeoPixels we will be using, charge accordingly
#define NB_PIXELS 60

// Instatiate the NeoPixel from the ibrary
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NB_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define MIN_RED 255
#define MAX_RED 255

#define MIN_GREEN 0
#define MAX_GREEN 40

#define MIN_BLUE 0
#define MAX_BLUE 0

//Value must be between 0 & 1.
//If you never want a LED to be completly off, put 0.1 to min
#define MIN_INTENSITY 0.0
#define MAX_INTENSITY 1.0

//Speed for variations, higher is slower
#define NOISE_SPEED_COLOR 5
#define NOISE_SPEED_INTENSITY 3

double n;
double ni;

void setup() {
  strip.begin();  // initialize the strip
  strip.show();   // make sure it is visible
  strip.clear();  // Initialize all pixels to 'off'
  //strip.setBrightness(60);
  Serial.begin(9600);

}

void loop() {
  renderLEDs();
}

unsigned int lastTime = 0;
void renderLEDs() {

  unsigned int time = millis();

  Serial.println(1000/(time - lastTime));
  lastTime = time;

  for (int i = 0; i < NB_PIXELS; i++) {
    //adjust the mult and divide to change the global effect
    n = inoise8(i*250 , (time+i)/NOISE_SPEED_COLOR);

    ni = inoise8(i*500 , (time+i)/NOISE_SPEED_INTENSITY);

    //You can change the easing function here
    float v = QuadraticEaseInOut(n/255);
    float vi = QuadraticEaseInOut(ni/255);
    
    vi = (MAX_INTENSITY - MIN_INTENSITY) * v + MIN_INTENSITY;
    float r = vi *((MAX_RED - MIN_RED)*v + MIN_RED);
    float g = vi *((MAX_GREEN - MIN_GREEN)*v + MIN_GREEN);
    float b = vi * ((MAX_BLUE - MIN_BLUE)*v + MIN_BLUE);

    strip.setPixelColor(i, r , g , b);
  }
  strip.show();

}

float CubicEaseInOut(float p)
{
  if (p < 0.5)
  {
    return 4 * p * p * p;
  }
  else
  {
    float f = ((2 * p) - 2);
    return 0.5 * f * f * f + 1;
  }
}

float QuadraticEaseInOut(float p)
{
  if (p < 0.5)
  {
    return 2 * p * p;
  }
  else
  {
    return (-2 * p * p) + (4 * p) - 1;
  }
}

float SineEaseOut(float p)
{
  return sin(p * M_PI_2);
}
