#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object
byte numDigits = 4;  
/* For the Led display */
const byte digitPins[] = {A4,A3,A2,A1};
/* Pin order for segment DIO. The segment order is A,B,C,D,E,F,G,DP */
byte segmentPins[] = {2,6,12,11,10,7,A0,A5};
bool resistorsOnSegments = 0;

/*-----Pin connection for Ultrasound sensor and Led-----*/
// defines pins numbers
const int trigPin = 9;
const int echoPin = 8;
const int buzzer = 13;
const int redLed = 3;
const int blueLed = 5;
const int greenLed = 4;

// defines variables
long duration;
int distance;
int safetyDistance;


void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(redLed, OUTPUT);
pinMode(blueLed, OUTPUT);
pinMode(greenLed, OUTPUT);

sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
sevseg.setBrightness(90);

Serial.begin(9600); // Starts the serial communication
}


void loop() {
 // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;

if (safetyDistance >= 0 and safetyDistance <= 40){
  digitalWrite(buzzer, HIGH);
  digitalWrite(redLed, HIGH);
  delay(200);
  digitalWrite(redLed, LOW);
  delay(200);
  digitalWrite(blueLed, LOW);
  digitalWrite(greenLed, LOW);
}

else if (safetyDistance >=41 and safetyDistance <= 85){
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  
  
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(greenLed, HIGH);
}

sevseg.setNumber(safetyDistance, 0);
sevseg.refreshDisplay(); 
 
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

}
