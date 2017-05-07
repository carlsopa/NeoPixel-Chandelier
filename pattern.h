#ifndef pattern_h
#define pattern_h
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
enum pattern {NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, FADE, SOLID, ON, OFF};
enum direction {FORWARD, REVERSE };

class ChanLevels : public Adafruit_NeoPixel
{
    public:
    pattern ActivePattern;
    direction Direction;
    
    unsigned long Interval;
    unsigned long lastUpdate;
    
    uint32_t Color1, Color2, Color3;
    uint16_t TotalSteps;
    uint16_t Index;
    uint16_t pixels;
    uint8_t pin;
    uint8_t type;
    String name;
    String status;
    bool begun;
    
    void (*OnComplete)();
    
    ChanLevels(uint16_t pixels, uint8_t pin, uint8_t type):Adafruit_NeoPixel(pixels, pin, type)
    {
        SetPin(pin);
        SetPixels(pixels);
        SetType(type);
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);

    }
    String GetName() {
        return name;
    }
    uint16_t GetPixels(){
        return pixels;
    }
    uint8_t GetPin(){
        return pin;
    }
    uint8_t GetType(){
        return type;
    }
    void SetName(String x){
        name = x;
    }
    void SetPixels(uint16_t x){
        pixels = x;
    }
    void SetPin(uint8_t x){
        pin = x;
    }
    void SetType(uint8_t x){
        type = x;
    }
    void Update()
  {
    if((millis() - lastUpdate) > Interval)
    {
      lastUpdate = millis();
      switch(ActivePattern)
      {
        case RAINBOW_CYCLE:
          RainbowCycleUpdate();
          break;
        case THEATER_CHASE:
          TheaterChaseUpdate();
          break;
        case COLOR_WIPE:
          ColorWipeUpdate();
          break;
        case FADE:
          FadeUpdate();
          break;
        case ON:
          OnUpdate();
          break;
        case OFF:
          OffUpdate();
          break;
        case SOLID:
          SetUpdate();
          break;
        default:
          break;
      }
    }
  }
  void Increment()
  {
    if (Direction == FORWARD)
    {
      Index++;
      if (Index >= TotalSteps)
      {
        Index = 0;
        if (OnComplete != NULL)
        {
          OnComplete();
        }
      }
    }
    else
    {
      --Index;
      if(Index <= 0)
      {
        Index = TotalSteps-1;
        if (OnComplete != NULL)
        {
          OnComplete();
        }
      }
    }
  }
  void Reverse()
  {
    if (Direction == FORWARD)
    {
      Direction = REVERSE;
      Index = TotalSteps-1;
    }
    else
    {
      Direction = FORWARD;
      Index = 0;
    }
  }
  void RainbowCycle(uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = RAINBOW_CYCLE;
        Interval = interval;
        TotalSteps = 255;
        Index = 0;
        Direction = dir;
    }
    
    // Update the Rainbow Cycle Pattern
    void RainbowCycleUpdate()
    {
        for(int i=0; i< numPixels(); i++)
        {
            setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
        }
        show();
        Increment();
    }
 
    // Initialize for a Theater Chase
    void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = THEATER_CHASE;
        Interval = interval;
        TotalSteps = numPixels();
        Color1 = color1;
        Color2 = color2;
        Index = 0;
        Direction = dir;
   }
    
    // Update the Theater Chase Pattern
    void TheaterChaseUpdate()
    {
        for(int i=0; i< numPixels(); i++)
        {
            if ((i + Index) % 3 == 0)
            {
                setPixelColor(i, Color1);
            }
            else
            {
                setPixelColor(i, Color2);
            }
        }
        show();
        Increment();
    }
 
    // Initialize for a ColorWipe
    void CWipe(uint8_t r,uint8_t g,uint8_t b,uint8_t i){
        ColorWipe(Color(r,g,b),i);
        ColorWipeUpdate();
    }
    void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = COLOR_WIPE;
        Interval = interval;
        TotalSteps = numPixels();
        Color1 = color;
        Index = 0;
        Direction = dir;
    }
    
    // Update the Color Wipe Pattern
    void ColorWipeUpdate()
    {
        setPixelColor(Index, Color1);
        show();
        Increment();
    }
    // Initialize for a Fade
    void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = FADE;
        Interval = interval;
        TotalSteps = steps;
        Color1 = color1;
        Color2 = color2;
        Index = 0;
        Direction = dir;
    }
    
    // Update the Fade Pattern
    void FadeUpdate()
    {
        // Calculate linear interpolation between Color1 and Color2
        // Optimise order of operations to minimize truncation error
        uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
        uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
        uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
        
        ColorSet(Color(red, green, blue));
        show();
        Increment();
    }
   
    // Calculate 50% dimmed version of a color (used by ScannerUpdate)
    uint32_t DimColor(uint32_t color)
    {
        // Shift R, G and B components one bit to the right
        uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
        return dimColor;
    }
 
    // Set all pixels to a color (synchronously)
    void ColorSet(uint32_t color)
    {
        for (int i = 0; i < numPixels(); i++)
        {
            setPixelColor(i, color);
        }
        show();
    }
    uint8_t Red(uint32_t color)
    {
        return (color >> 16) & 0xFF;
    }
 
    // Returns the Green component of a 32-bit color
    uint8_t Green(uint32_t color)
    {
        return (color >> 8) & 0xFF;
    }
 
    // Returns the Blue component of a 32-bit color
    uint8_t Blue(uint32_t color)
    {
        return color & 0xFF;
    }
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos)
    {
        WheelPos = 255 - WheelPos;
        if(WheelPos < 85)
        {
            return Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        else if(WheelPos < 170)
        {
            WheelPos -= 85;
            return Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        else
        {
            WheelPos -= 170;
            return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
    } 
    void SetColor(uint8_t r,uint8_t g, uint8_t b){
        Color1 = Color(r,g,b);
        ActivePattern = SOLID;
    }
    void SetUpdate(){
        ColorSet(Color1);
        show();
        Increment();
    }
    void TurnOn(){
        Interval = 20;
        ActivePattern = ON;
        //ColorSet(Color(255,255,255));
    }
    void OnUpdate(){
        ColorSet(Color(255,255,255));
        //setPixelColor(0, Color(255,255,255));
        show();
        Increment();
    }
    void TurnOff(){
        Interval = 20;
        ActivePattern = OFF;
        //ColorSet(Color(0,0,0));
    }
    void OffUpdate(){
        ColorSet(Color(0,0,0));
        //setPixelColor(0, Color(0,0,0));
        show();
        Increment();
    }
    void SHOW(){
        show();
    }
    static uint32_t AColor(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
    static uint32_t AColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
        return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
};
#endif
