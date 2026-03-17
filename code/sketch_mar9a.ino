#include <Ultrasonic.h>
int press;
float VCC = 5.0; // Define VCC as 5V
float VOUT;
float RC;

Ultrasonic ultrasonic1(12, 13);  // Capteur HC-SR04
#define Led 5
#define buzzer 6

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {

  int distance = ultrasonic1.distanceRead();
  press = analogRead(A0);

  Serial.print("Sensor: ");
  Serial.print(distance);
  Serial.println(" cm            ");
  Serial.print(map(press, 0, 1023, 0, 20000));
  Serial.println(" g");

  // Si un objet est à moins de 20 cm, on allume la LED
  if (distance < 20 || distance > 300) {
    digitalWrite(
      Led, HIGH);
  } 
  else {
    digitalWrite(Led, LOW);
  }
    if (press > 511) {
    digitalWrite(buzzer, HIGH);
  } 
  else {
    digitalWrite(buzzer, LOW);
  }

  delay(200);
}