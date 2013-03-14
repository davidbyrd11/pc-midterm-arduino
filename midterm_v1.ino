#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs1 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs2 = CapacitiveSensor(13,12);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
void setup() { Serial.begin(9600); }

void loop() {
    long start = millis();
    long total1 =  cs1.capacitiveSensor(30); //TODO (david) wtf is the 30 for?
    long total2 =  cs2.capacitiveSensor(30);

    Serial.print(total1);
    Serial.print(",");
    Serial.print(total2);
    Serial.print("\n");
    
    delay(10);
}
