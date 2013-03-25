#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

const int NUM_SENSORS = 5;
int SAMPLES = 30;
const int AUTOCAL = 0xFFFFFFFF;
int THRESHOLDS[NUM_SENSORS] = {200,200,200,200,200};
CapacitiveSensor *sensors[NUM_SENSORS];
int states[NUM_SENSORS]; // keeps track of the state of each sensor as an int code: 0=off, 1=on

//CapacitiveSensor   cs1 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs2 = CapacitiveSensor(13,12);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
void setup() {
  sensors[0] = new CapacitiveSensor(4,2);
  sensors[0]->set_CS_AutocaL_Millis(AUTOCAL);
  sensors[1] = new CapacitiveSensor(13,12);
  sensors[1]->set_CS_AutocaL_Millis(AUTOCAL);
  sensors[2] = new CapacitiveSensor(8,9);
  sensors[2]->set_CS_AutocaL_Millis(AUTOCAL);
  sensors[3] = new CapacitiveSensor(0,1);
  sensors[3]->set_CS_AutocaL_Millis(AUTOCAL);
  sensor[4] = new CapacitiveSensor(6,7);
  sensors[4]->set_CS_AutocaL_Millis(AUTOCAL);
  Serial.begin(9600); 
}

void loop() {
    //long start = millis();
 
    /* Loop through the sensors and get new data.
       Process data into code values and check against current sensor state codes.
       If the new code is different, update the current state code and write a control message to the serial port. */
    for(int i=0; i<NUM_SENSORS; i++){
      int datum = sensors[i]->capacitiveSensor(SAMPLES);
      //Serial.print((String)datum + ","); //DEBUG
      int ncode = 0;
      
      if(datum<THRESHOLDS[i]){
        ncode = 0;
      }
      else{
        ncode = 1;
      }
      if(ncode^states[i]){ // this is like a not equals check
        states[i] = ncode;
        Serial.println((String)(10*(i+1) + ncode));
      }
    }
    //Serial.println(); //DEBUG
    
    /*
    long total1 =  cs1.capacitiveSensor(30); //TODO (david) wtf is the 30 for?
    long total2 =  cs2.capacitiveSensor(30);

    Serial.print(total1);
    Serial.print(",");
    Serial.print(total2);
    Serial.print("\n");
    */
    delay(25);
}
