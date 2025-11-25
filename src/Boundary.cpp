#include "Boundary.h"
#include <Adafruit_NeoPixel.h>

IR_sensor::IR_sensor(int pir_pin) : pin(pir_pin), presence(false) {}

bool IR_sensor::IR_init() {
    pinMode(pin, INPUT); // Vælger pins og sætter den til input, da IR sensoren skal aflæse.
    return true;
}

bool IR_sensor::getPresence() {
    presence = (digitalRead(pin) == HIGH); // Hvis IR-sensoren er høj, er der tilstedeværelse.
    return presence;
}

Lyssensor::Lyssensor() 
    : lux_level(0) {}

bool Lyssensor::lyssensor_init() {
    Wire.begin(); 
    return Lysmaaler.begin();
}

int Lyssensor::getluxlevel() {
    lux_level = Lysmaaler.readLightLevel();
    return lux_level;
}

LED::LED(int led_pin) : pin(led_pin) {}

void LED::setup() {
    pinMode(pin, OUTPUT); // Sætter LED_PIN som output
    TCCR3A = (1 << COM3C1) | (1 << WGM30); 
    TCCR3B = (1 << WGM32) | (1 << CS31);
}

void LED::setPWM_value(int pwm_value) {
    OCR3C = pwm_value;
}

LEDDriver::LEDDriver() :
      ring1Pin_(5),
      ledsRing1_(12),
      currentIntensity_(0),
      ring1_(ledsRing1_, ring1Pin_, NEO_GRB + NEO_KHZ800)
{   
}

void LEDDriver::initLED()
{
    ring1_.begin();
    setIntensity(0);
}

void LEDDriver::setIntensity(int intensity)
{
    if (intensity < 0) intensity = 0;
    if (intensity > 100) intensity = 100; // Frygter den sluger for meget strøm ellers.

    currentIntensity_ = intensity;

    uint8_t level = (currentIntensity_ * 200) / 100;
    uint32_t color1 = ring1_.Color(level, level, level);
    for (uint16_t i = 0; i < ledsRing1_; i++)
        ring1_.setPixelColor(i, color1);
        
    ring1_.show();
}

void LEDDriver::runSimplePartySequence()
{

    const uint16_t numRounds = 4;        
    const int startDelayMs = 150;        
    const int endDelayMs = 5;           
    const int maxIntensity = 30;
    
    uint8_t introLevel = (15 * 255) / 100;
    uint32_t introColor = ring1_.Color(introLevel, introLevel, introColor);
    
    const uint16_t totalSteps = ledsRing1_ * numRounds;
    
    for (uint16_t step = 0; step < totalSteps; step++)
    {
        int currentDelay = map(step, 
                               0, totalSteps, 
                               startDelayMs, endDelayMs);

        uint16_t pixelIndex = step % ledsRing1_;

        // TÆNDER KUN DENNE ENE PIXEL
        ring1_.clear(); // Slukker ALT før den tænder den nye
        ring1_.setPixelColor(pixelIndex, introColor);
        ring1_.show();
        
        delay(currentDelay); 
    }

    // --- 2. PARTY MODE (2 sekunder med blinkende tilfældige farver) ---
    
    const unsigned long partyDurationMs = 2000;
    const unsigned long flashDelayMs = 75;
    uint8_t maxLevel = (maxIntensity * 255) / 100;
    
    unsigned long startTime = millis();
    
    while (millis() - startTime < partyDurationMs)
    {
        uint8_t r = random(0, maxLevel);
        uint8_t g = random(0, maxLevel);
        uint8_t b = random(0, maxLevel);

        uint32_t color = ring1_.Color(r, g, b);

        for (uint16_t i = 0; i < ledsRing1_; i++)
        {
            ring1_.setPixelColor(i, color);
        }
        ring1_.show();
        
        delay(flashDelayMs); 
    }
    
    ring1_.clear();
    ring1_.show();
}

void Lyssenor2::init_lightsensor()
{
    Wire.begin();

    Wire.beginTransmission(0x23);
    Wire.write(BH1750_POWER_ON);
    Wire.endTransmission();

    Wire.beginTransmission(0x23);
    Wire.write(BH1750_RESET);
    Wire.endTransmission();

    lux_ = 0;

}

int Lyssenor2::getLuxValue()
{
    Wire.beginTransmission(0x23);
    Wire.write(ONE_HIGH_RES_MODE);
    Wire.endTransmission();

    Wire.requestFrom(0x23, 2);
    if (Wire.available() == 2)
    {
        uint16_t lumen = (Wire.read() << 8 | Wire.read());
        lux_ = lumen / 1.2;
    }
    else
    {
        lux_ = -1;
    }

    return lux_;
}
