//----------------------------------------------------------------
// RCWL-0516 Radar Motion Sensor example
//
// Dean Gienger, March 1, 2024
//
// The RCWL-0516 is a doppler radar motion sensor with the following specs:
// Operating voltage: 4-28V, typically 5V
// Detection distance: 5-7 meters max
// Maximum Current: <3ma
// Frequency: 3.18 GHz
// Tx power: 20-30 mW
// Signal duration: about 2 seconds
// Regulated output voltage: 3.3V
//
// There are 5 pins:
// 3V3: 3.3V regulated output
// GND: ground
// OUT: 3.3V TTL logic output (LOW->HIGH for 2-3 seconds when motion detected)
// VIN: Input power to module 4-28V
// CDS: Optional pins for a CDS light dependent resistor
// V1.0 - initial release, March 1, 2024
// V1.1 - deactivate on destruct
//
// https://www.instructables.com/All-About-RCWL-0516-Microwave-Radar-Motion-Sensor/
//
// V1.0 March 1, 2024, Dean Gienger
// --------------

class RCWL0516
{
  public:
    //--- Constructor ---
    RCWL0516(int gpiopin);
    ~RCWL0516() { deactivate(); }
    
    //--- millis() time when we last triggered, 0 means none
    unsigned long lastTriggerTime() { return trigTime; }
    
    // true if we triggered with the last xms
    int triggeredWithin(unsigned long xms);
    
    // how many times it triggered since last time we checked by calling currentTriggers
    unsigned long currentTriggers();
    
    int activate();
    
    int deactivate();

    int trigCount() { return triggerCount; }
    
  private:
    void ARDUINO_ISR_ATTR isr() { triggerCount++; trigTime = millis(); }
    int gpioPin;
    unsigned long triggerCount;
    unsigned long trigTime;
    unsigned long lastReadTriggerCount; // trigger count last time we checked
};
