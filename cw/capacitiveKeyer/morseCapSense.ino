#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
 long threshold = 300;
 float WPM = 12;
 long dot = 1200 / WPM;
 long dah = 3 * dot;
 long shortGap = dah;
 long longGap = 7 * dot;

void setup()                    
{
   pinMode(13, OUTPUT);
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop()   
{
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_4_6.capacitiveSensor(30);
    //WPM = 100*analogRead(A0)/1024;
    WPM = 1 + int(100 * float(analogRead(A0))/1024);
    dot = 1200 / WPM;
    dah = 3 * dot;
   
    while(total1 > threshold) {
      while (total2 > threshold && total1 > threshold) {
        digitalWrite(13, HIGH);
        delay(dah);
        digitalWrite(13, LOW);
        delay(dot);
        total2 = cs_4_6.capacitiveSensor(30);
        total1 = cs_4_2.capacitiveSensor(30);
      }
      if(total1 > threshold) {
        digitalWrite(13, HIGH);
        delay(dot);
        digitalWrite(13, LOW);
        delay(dot);
      }
      total1 = cs_4_2.capacitiveSensor(30);
      total2 = cs_4_6.capacitiveSensor(30);
    }
    digitalWrite(13, LOW);

    while(total2 > threshold) {
      while (total2 > threshold && total1 > threshold) {
        digitalWrite(13, HIGH);
        delay(dot);
        digitalWrite(13, LOW);
        delay(dot);
        total2 = cs_4_6.capacitiveSensor(30);
        total1 = cs_4_2.capacitiveSensor(30);
      }
      if (total2 > threshold) {
        digitalWrite(13, HIGH);
        delay(dah);
        digitalWrite(13, LOW);
        delay(dot);
      }
      total2 = cs_4_6.capacitiveSensor(30);
      total1 = cs_4_2.capacitiveSensor(30);
    }
    digitalWrite(13, LOW);
}
