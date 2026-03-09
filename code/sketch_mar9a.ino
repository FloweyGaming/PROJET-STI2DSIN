#include <Ultrasonic.h>

Ultrasonic ultrasonic1(12, 13);  // Capteur HC-SR04
#define Led 5

void setup() {
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
}

void loop() {

  int distance = ultrasonic1.distanceRead();

  Serial.print("Sensor: ");
  Serial.print(distance);
  Serial.println(" cm");
  // Si un objet est à moins de 20 cm, on allume la LED
  if (distance < 20 || distance > 300) {
    digitalWrite(Led, HIGH);
  } 
  else {
    digitalWrite(Led, LOW);
  }


  delay(500);
}