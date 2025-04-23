/*Project for Physics class - Jason Thomson Spring 2025 PHY 252
This theramin project uses the ultrasonic sensor, potentiometer, and a piezo speaker to create a theramin-like instrument.
https://github.com/schnoggy/phy252/tree/main/Theramin
*/
//include libraries
#include <Arduino.h>
#include <../lib/NewPing/src/NewPing.h> // from https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
#include <../lib/timerfreetone/TimerFreeTone.h> // from https://bitbucket.org/teckel12/arduino-timer-free-tone/wiki/Home , needed to use because of timer conflicts, but then keept it becuase it gave me a direct volume contorl

//define constants
#define TONE_PIN 9 // Arduino pin connected to piezo speaker.
#define TRIGGER_PIN  3 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 4 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MIN_DISTANCE   35 // Minimum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters).
#define PING_INTERVAL 29 // Milliseconds between pings (minimum is 29ms, but 50ms is a good number).

// initialize sonar object
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // the first and the second number are the pins   of the sensor of volume, the third is the maximum distance

//initiate variables
int potpin=A5;
int prpin=A0;
int buzzerpin=9;
int val;
int prval; 
int uval;
int echo = 4;                            
int trigger = 3;
unsigned long TimeResponse;
long duration, cm, inches;


void setup() {
  // Initialize serial communication at 115200 bps
  Serial.begin(115200);

  pinMode(buzzerpin, OUTPUT); // setup piezo speaker output
  pinMode(prpin, INPUT); // setup analog pot input
  pinMode(potpin, INPUT);  //setup analog pot input
  pinMode(trigger, OUTPUT); // setup ultrasonic tone sensor                    
  pinMode(echo,   INPUT); // setup ultrasonic tone sensor    
}

void loop() {
  // Need to loop through inputs and display a tone
  //Input1: potentionmeter
  //Input2: light
  //output3: sound pitch/volume
  
  digitalWrite(TRIGGER_PIN, LOW);
  //delayMicroseconds(5); // unneeded delay
  digitalWrite(TRIGGER_PIN, HIGH);
  //delayMicroseconds(10); //unneded delay
  digitalWrite(TRIGGER_PIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  pinMode(ECHO_PIN, INPUT);
  //An alternative, albeit slower way to read the echo:
  /*
  duration = pulseIn(ECHO_PIN, HIGH);
  distance2 = duration / 58.2; // Convert the time into a distance
  */
  cm = sonar.ping_cm(); // Convert the time into a distance

  //calibrate the frequency to start at 220, then increase by 2^(cm/12). /12 to keep it aligned with a 12 tone scale
  uval = 220+pow(2,(cm*8/12));

  uval = map(cm, 0, 100, 80,1800); // map the inputs to the frequency range of the piezo speaker

  prval = analogRead(prpin); // read the optical sensor
  prval = map(prval, 0, 20, 0, 10);

  val = analogRead(potpin); //read the potentiometer
  val = map(val, 0, 1023, 5, 300); //map the potentiometer to a range of 5ms to 300ms to controle the length of the tone


  TimerFreeTone(TONE_PIN, uval, val, prval);// make the sound!

  // print serial output for monitoring values
  Serial.print("cm: ");
  Serial.print(cm);
  Serial.print("  vol: ");
  Serial.print(prval);
  Serial.print("  tone: ");
  Serial.print(uval);
  Serial.print("  length: ");
  Serial.println(val);

}

