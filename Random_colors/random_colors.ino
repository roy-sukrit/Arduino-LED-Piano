#include <FastLED.h>
#define NUM_LEDS 174 // how many leds do you want to control
#define DATA_PIN 5 // your LED strip data pin

int redVal = 255;
int greenVal = 255;
int blueVal = 255;
bool setColors = false;
bool receiveNotes = false;
int colorSetCounter = 0;

CRGB leds[NUM_LEDS];

void setup() 
{
    Serial.begin(9600);   
    Serial.setTimeout(10);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
    // FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUM_LEDS);
   
}

void loop() 
{
    // serial communication    
    while(Serial.available() > 0 )
    {
        int inByte = Serial.read();        
        if (inByte > 0) 
        {
            // if byte is 255, then the next 3 bytes will be new rgb value
            if (inByte == 255) 
            {
                setColors = true;
                colorSetCounter = 0;
            } 
            else if (setColors) 
            {
                switch (colorSetCounter) 
                {
                    case 0:
                        redVal = inByte;
                        //interval.loop();
                        break;
                    case 1:
                        greenVal = inByte;
                        //interval.loop();
                        break;
                    case 2:
                        blueVal = inByte;
                        setColors = false;
                        receiveNotes = true;
                        fill_solid(leds, NUM_LEDS, CRGB::Black);
                        FastLED.show();
                        break;
                }
                colorSetCounter++;
            } 
            else if (receiveNotes) 
            {               
                controlLeds(inByte);
                
            }
        }
    }
}

void controlLeds (int note) 
{
    note -= 1;
    if (!leds[note]) 
    {
        
        redVal = random(10,250);
        greenVal = random(10,250);
        blueVal = random(10,250);
        
        
        leds[note].red = redVal;
        leds[note].green = greenVal;
        leds[note].blue = blueVal;
          
    } 
    else 
    {
        leds[note] = CRGB::Black;
    }
    FastLED.show();
}
