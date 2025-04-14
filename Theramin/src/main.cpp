#include <Arduino.h>
//#include <../lib/NewTone/NewTone.h>
#include <../lib/toneAC2/toneAC2.h>
#include <../lib/NewPing/src/NewPing.h>

// put function declarations here:
#define TONE_PIN 10
#define TONE_PIN2 11 // Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor).
#define TIMER_ENABLED false
#define TRIGGER_PIN  3
#define ECHO_PIN 4 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MIN_DISTANCE   35 
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // the first and the second number are the pins   of the sensor of volume, the third is the maximum distance
// Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

int potpin=A5;
int prpin=A0;
int buzzerpin=1;
int val;
int prval; 
int uval;

int echo = 4;                            
int trigger = 3;

int distance;
int PotValue;

unsigned long TimeResponse;
float   distance2;
float tone1;
long duration, cm, inches;

void setup() {
  Serial.begin(115200);
  pinMode(buzzerpin, OUTPUT);
  pinMode(prpin, INPUT);
  //setup analog pot input
  //setup analog sensor input
  //setup setup a way to read antenna input
  pinMode(trigger, OUTPUT); // tone sensor                    
  pinMode(echo,   INPUT); // tone sensor    
}

void loop() {
  /*for (unsigned long freq = 125; freq <= 15000; freq += 10) {  
    toneAC2(TONE_PIN, TONE_PIN2, freq, 100); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
    //toneAC2(0, 1, freq, 1); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps) for 1ms.
  }

  delay(10); // Wait a second.

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    toneAC2(TONE_PIN, TONE_PIN2, melody[thisNote], noteDuration); // Play thisNote for noteDuration.
    //toneAC2(0, 1, melody[thisNote], noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
*/
  //while(1); // Stop (so it doesn't repeat forever driving you crazy--you're welcome).


  // Need to loop through inputs and display a tone
  //Input1: potentionmeter
  //Input2: light
  //Input3: antenna field
  //output1: led intensity
  //output2: led color - maybe based on pitch
  //output3: sound pitch/volume
  
  //  for (unsigned long freq = 125; freq <= 15000; freq += 10) {  
  //    NewTone(TONE_PIN, freq); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
 //     delay(1); // Wait 1 ms so you can hear it.
 //   }
 //   noNewTone(TONE_PIN); // Turn off the tone.
  
 //   delay(1000); // Wait a second.
  
 //   for (int thisNote = 0; thisNote < 8; thisNote++) { // Loop through the notes in the array.
 //     int noteDuration = 1000/noteDurations[thisNote];
 //     NewTone(TONE_PIN, melody[thisNote], noteDuration); // Play thisNote for noteDuration.
 //     delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
 //   }
  
  //  while(1); // Stop (so it doesn't repeat forever driving you crazy--you're welcome).
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);
 distance2 = duration / 58.2; // Convert the time into a distance

  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  /*Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  */
  uval = 50.0*pow(2,(distance2/12.0));
  //uval = map(cm, 0, 100, 80,1000);
  
  prval = analogRead(prpin);
  prval = map(prval, 0, 100, 100, 1100);
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 1000);
  toneAC2(TONE_PIN, TONE_PIN2, uval);
  delay(10);
  Serial.println(uval);
//  delayMicroseconds(10);

}
/*
int digitalPotWrite(int value) {
  digitalWrite(CS, LOW); // this uses SPI protocol   to communicate with the potentiometer and sets the resistance
  SPI.transfer(address);
   SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
*/

//Notepad


/*
  This projects is a theremin created with one ultrasonic sensor and a optical potentionmeter,   one controls the frequency (tone) and the other controls the amplitude (volume).
  Resource   on controlling similar potentiometer using SPI protocol, provides example code and   electrical setup: http://www.learningaboutelectronics.com/Articles/MCP4131-digital-potentiometer-circuit.php
  It is also using some libraries to enhance the suound quality over the auduino sdk tone()
  */

/*                                                                                                                                                                                                                                                
   Potentiometer conecctions:
 1 - Arduino pin ~9
 2 - Speaker +
 3 - GND
   4 - 5V
 5 - Arduino pin ~10
 6 - Arduino pin 13
 7 - Arduino pin ~11
   8 - GND
 More info https://app.ultralibrarian.com/details/23D04BE7-10A0-11E9-AB3A-0A3560A4CCCC/Microchip/MCP4161-103E-P
*/