#include "NyLED.h"
#include "Konfiguration.h"

LEDDriver::LEDDriver() : 
    ring1Pin_(0),
    ledsRing1_(0),
    currentIntensity_(0),
    ring1_()
{ 
}

LEDDriver::LEDDriver(int taerskel_value)
    : Konfiguration(taerskel_value),
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

bool LEDDriver::isRunning()
{
    return currentIntensity_;
}

int LEDDriver::calculateIntensity(int lux) //Omsætter lux til en procentdel.
{
    if (lux >= lys_taerskel_val) {
        return 0; // Hvis lyset er over tærskel, slukker det.
    }
    int intensity = map(lux, 0, lys_taerskel_val, 100, 0);
    return constrain(intensity, 0, 100);
}

void LEDDriver::runSimplePartySequence()
{
    // --- 1. INTRO MODE (Accelererende "scanner" effekt) ---
    
    // Konstanter for timing og lysstyrke
    const uint16_t numRounds = 4;        // Antal gentagelser
    const int startDelayMs = 150;        // Langsom start
    const int endDelayMs = 5;            // Hurtig slutning
    const int maxIntensity = 30;
    
    uint8_t introLevel = (15 * 255) / 100;
    uint32_t introColor = ring1_.Color(introLevel, introLevel, introColor);
    
    const uint16_t totalSteps = ledsRing1_ * numRounds;
    
    for (uint16_t step = 0; step < totalSteps; step++)
    {
        // Beregn den accelererende forsinkelse
        int currentDelay = map(step, 
                               0, totalSteps, 
                               startDelayMs, endDelayMs);

        // Find den pixel, der skal tændes (bruger modulo til at loope)
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
    
    // --- 3. SLUK og gør klar til gentagelse ---
    ring1_.clear();
    ring1_.show();
}