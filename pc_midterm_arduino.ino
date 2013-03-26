/* Turns the Arduino into a signal processor for several capacitive sensors.
   Maintains a state for each sensor and writes changed states to Serial port. */
#include <CapacitiveSensor.h>

const int NUM_SENSORS = 5;
int recPins[NUM_SENSORS] = {4,13,8,0,6};
int sensePins[NUM_SENSORS] = {2,12,9,1,7};
int SAMPLES = 30;
const int AUTOCAL = 0xFFFFFFFF;
const int DEFAULT_THRESH = 200;
int THRESHOLDS[NUM_SENSORS];// = {200,200,200,200,200};
CapacitiveSensor *sensors[NUM_SENSORS];
int states[NUM_SENSORS]; // keeps track of the state of each sensor as an int code: 0=off, 1=on

void setup() {
  
  /* Instantiate a cap. sensor for each of the sensors and set its autocal value.
      Also sets the threshold to default value. */
  for(int i=0; i<NUM_SENSORS; i++){
    sensors[i] = new CapacitiveSensor(recPins[i],sensePins[i]);
    sensors[i]->set_CS_AutocaL_Millis(AUTOCAL);
    THRESHOLDS[i] = DEFAULT_THRESH;
  }
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
    delay(25);
}
