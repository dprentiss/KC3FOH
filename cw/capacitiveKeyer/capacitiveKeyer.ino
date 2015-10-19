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
int WPM = 20;

long dit = 1200 / WPM;
long dah = 3 * dit;
long pitch = 800;

void sendDit() {
  digitalWrite(13, HIGH);
  tone(9, pitch, dit);
  delay(dit);
  digitalWrite(13, LOW);
  delay(dit); 
}

void sendDah() {
  digitalWrite(13, HIGH);
  tone(9, pitch, dah);
  delay(dah);
  digitalWrite(13, LOW);
  delay(dit); 
}
 
void setup()                    
{
   pinMode(13, OUTPUT);
   pinMode(9, OUTPUT);
   Serial.begin(9600);
   sendDah();
   sendDit();
   sendDah();
}

void loop()   
{
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_4_6.capacitiveSensor(30);
    WPM = 5 + int(25 * float(analogRead(A0))/1024);
    dit = 1200 / WPM;
    dah = 3 * dit;
   
   
    while(total1 > threshold) {
      while (total2 > threshold && total1 > threshold) {
        sendDah();
        total2 = cs_4_6.capacitiveSensor(30);
        total1 = cs_4_2.capacitiveSensor(30);
      }
      if(total1 > threshold) {
        sendDit();
      }
      total1 = cs_4_2.capacitiveSensor(30);
      total2 = cs_4_6.capacitiveSensor(30);
    }
    //digitalWrite(13, LOW);

    while(total2 > threshold) {
      while (total2 > threshold && total1 > threshold) {
        sendDit();
        total2 = cs_4_6.capacitiveSensor(30);
        total1 = cs_4_2.capacitiveSensor(30);
      }
      if (total2 > threshold) {
        sendDah();
      }
      total2 = cs_4_6.capacitiveSensor(30);
      total1 = cs_4_2.capacitiveSensor(30);
    }
    //digitalWrite(13, LOW);
}
