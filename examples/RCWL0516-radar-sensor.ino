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

#include "RCWL0516.h"

// OUT connected to GPIO12
#define RCWPIN 12  

RCWL0516 radar(RCWPIN);

void setup() 
{
  Serial.begin(115200);
  Serial.println("\nRCW-0516 radar sensor test\n");
  radar.activate();
}

void loop() 
{
  delay(500);
  Serial.print("trigTime "); Serial.print(radar.lastTriggerTime());
  Serial.print(", trigCount "); Serial.println(radar.trigCount());
}
