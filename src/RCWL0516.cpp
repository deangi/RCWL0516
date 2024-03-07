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
// V1.0 - initial release
//
// V1.0 March 1, 2024, Dean Gienger
//
//------------------------------------------------

#include <Arduino.h>
#include "RCWL0516.h"
#include <FunctionalInterrupt.h>

//------------------------------------------------
// Constructor
RCWL0516::RCWL0516(int gpiopin)
{
    gpioPin = gpiopin;
    triggerCount = 0;
    lastReadTriggerCount = 0;
    trigTime = 0;
    pinMode(gpioPin,INPUT_PULLUP);
}

//------------------------------------------------
// activate a sensor on a particular pin
int RCWL0516::activate()
{
  triggerCount = 0;
  lastReadTriggerCount = 0;
  trigTime = 0;
  pinMode(gpioPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), std::bind(&RCWL0516::isr,this), RISING);
  return true; // success
}

//------------------------------------------------
// detach a sensor - make it inactive
int RCWL0516::deactivate()
{
  detachInterrupt(gpioPin);
  gpioPin = -1; // not active
  return true; // success
}

//------------------------------------------------
// true if there was a trigger in last xms
int RCWL0516::triggeredWithin(unsigned long xms)
{
  unsigned long x = millis() - trigTime;
  return x <= xms;
}

//------------------------------------------------
// see how many triggers since last time
// this routine was called
unsigned long RCWL0516::currentTriggers() 
{ 
  unsigned long n = triggerCount - lastReadTriggerCount; 
  lastReadTriggerCount = triggerCount; 
  return n;
}
