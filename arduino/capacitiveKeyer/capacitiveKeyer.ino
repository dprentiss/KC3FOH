#include <CapacitiveSensor.h>

/*
 * Arudino-based CW keyer for capacitive touch sensor paddles
 * David Prentiss KC3FOH 2015
 *
 * Thanks to Paul Badger for the Capacitive Sensing Librabry
 * <http://http://playground.arduino.cc/Main/CapacitiveSensor>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);

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
