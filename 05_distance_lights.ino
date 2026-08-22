/* ============================================================
   DISTANCE TRAFFIC LIGHT
   An ultrasonic sensor measures how far away an object is.
   Three LEDs show how close it is, like a car parking sensor:

        FAR   -> GREEN   (all clear)
        MEDIUM-> YELLOW  (getting close)
        CLOSE -> RED     (stop!)

   Board: Arduino Uno R3   Sensor: HC-SR04

   WIRING
     HC-SR04  VCC  -> 5V
     HC-SR04  GND  -> GND
     HC-SR04  Trig -> pin 7
     HC-SR04  Echo -> pin 6

     GREEN  LED -> pin 10 -> 220 ohm resistor -> GND
     YELLOW LED -> pin  9 -> 220 ohm resistor -> GND
     RED    LED -> pin  8 -> 220 ohm resistor -> GND

   TRY THIS: change the numbers 10 and 25 to move the zones.
   ============================================================ */

// --- sensor pins ---
int trigPin = 7;
int echoPin = 6;

// --- LED pins ---
int greenPin  = 10;
int yellowPin = 9;
int redPin    = 8;

// --- distance zones, in centimeters ---
int nearLimit = 10;   // closer than this  -> RED
int midLimit  = 25;   // closer than this  -> YELLOW, otherwise GREEN

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  Serial.begin(9600);   // lets us watch the distance on the screen
}

void loop() {
  int distance = readDistanceCM();   // measure the distance

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  allLightsOff();   // start fresh each time

  if (distance == 0 || distance > midLimit) {
    // nothing close (or nothing detected) -> all clear
    digitalWrite(greenPin, HIGH);
  }
  else if (distance > nearLimit) {
    // in the middle zone -> caution
    digitalWrite(yellowPin, HIGH);
  }
  else {
    // very close -> stop
    digitalWrite(redPin, HIGH);
  }

  delay(100);   // small pause before measuring again
}

// Turn every LED off.
void allLightsOff() {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
}

// Send a "ping" and time the echo to get distance in cm.
// (The sensor works like a bat!)
int readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long echoTime = pulseIn(echoPin, HIGH, 30000);  // wait up to 30ms for echo
  int distance = echoTime * 0.034 / 2;            // turn time into distance
  return distance;
}
