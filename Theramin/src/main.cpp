#include <Arduino.h>
#include <lib/NewTone/NewTone.h>

// put function declarations here:
#define TONE_PIN 11 // Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor).

// Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

int potpin=5;
int buzzerpin=11;
int val;

void setup() {
  Serial.begin(115200);
  pinMode(buzzerpin, OUTPUT);
  // put your setup code here, to run once:
  //setup analog pot input
  //setup analog sensor input
  //setup setup a way to read antenna input
}

void loop() {
  // put your main code here, to run repeatedly
  // Need to loop through inputs and display a tone
  //Input1: potentionmeter
  //Input2: light
  //Input3: antenna field
  //output1: led intensity
  //output2: led color - maybe based on pitch
  //output3: sound pitch/volume
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 1000);
  newtone(buzzerpin, val);
  tone(buzzerpin, val);
  Serial.println(val);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}