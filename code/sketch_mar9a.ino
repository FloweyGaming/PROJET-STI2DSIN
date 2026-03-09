
#include <Ultrasonic.h>

Ultrasonic ultrasonic1(12, 13);	// An ultrasonic sensor HC-04


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Sensor: ");
  Serial.print(ultrasonic1.distanceRead()); // Prints the distance on the default unit (centimeters)
  Serial.println("cm");
}
