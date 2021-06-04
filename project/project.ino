#include <NewPing.h>
#include <HC7Segment.h>
#include <TimedAction.h>
void blink();
TimedAction timedAction = TimedAction(1000,blink);
/* For the Led display */
const byte u8PinOut_Digit[] = {A4,A3,A2,A1};
/* Pin order for segment DIO. The segment order is A,B,C,D,E,F,G,DP */
const byte u8PinOut_Segment[] = {2,6,12,11,10,7,A0,A5};
/* Create an instance of HC7Segment(). In this example we will be using a 4 digit
common cathode display (CAI5461AH) */
HC7Segment HC7Segment(7, LOW);
/*-----Pin connection for Ultrasound sensor-----*/
// defines pins numbers
const int trigPin = 9;
const int echoPin = 8;
const int buzzer = 13;
const int redLed = 3;
const int blueLed = 5;
const int greenLed = 4;
int DistanceCm;
int MAX_DISTANCE =600;
/*-----( Declare objects )-----*/
// Maximum distance we want to ping for (in centimeters).
//Maximum sensor distance is rated at 400-500cm.


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

if (safetyDistance >= 0 and safetyDistance <= 25){
  digitalWrite(buzzer, HIGH);
  digitalWrite(redLed, HIGH);
  delay(200);
  digitalWrite(redLed, LOW);
  delay(200);
  digitalWrite(blueLed, LOW);
  digitalWrite(greenLed, LOW);
}

else if (safetyDistance >=26 and safetyDistance <= 40){
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

timedAction.check();
HC7Segment.vDisplay_Number(DistanceCm,1);
}

void blink(){
delay(50);// Wait 50ms between pings (about 10 pings/sec). 29ms should be the shortest delay between pings.
Serial.print("Ping: ");
Serial.print(DistanceCm);
Serial.println(" cm");
}
