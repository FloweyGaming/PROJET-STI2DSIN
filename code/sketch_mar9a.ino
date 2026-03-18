#include <Ultrasonic.h>

int press;
float VCC = 5.0;
float VOUT;
float RC;

Ultrasonic ultrasonic1(12, 13);

#define Led 5 //LED = PIN 5
#define buzzer 6 //BUZZER = PIN 6

void setup() {
  pinMode(A0, INPUT); //CAPTEUR PRESSION = ENTRÉE
  pinMode(led, OUTPUT); //LED = SORTIE
  pinMode(buzzer, OUTPUT); //BUZZER = SORTIE
  Serial.begin(9600);
}

void loop() {

  int distance = ultrasonic1.distanceRead(); // Var "Distance" = Distance Renvoyée par CapUS
  press = analogRead(A0); // Var "Pression" = Force Renvoyée par CapPR

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm"); //Renvoie "<distance> cm"

  Serial.print("Poids: ");
  Serial.print(map(press, 0, 1023, 0, 20000)); //Convertir les Valeurs de tensions en grammes
  Serial.println(" g"); //Renvoie "<pression> g"

  // Détection distance
  if (distance < 20 || distance > 300) {
    delay(2500);
    Serial.print(distance);
    Serial.println(" cm");
    if (distance < 20 || distance > 300) {
      digitalWrite(buzzer, HIGH); // Si un objet est à moins de 20 cm ET 2 secondes sont passées, on allume la LED
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500); 
    }
      else {digitalWrite(buzzer, LOW); //Sinon, éteindre (ou laisser éteint) le Buzzer
      }
  } else {
    digitalWrite(buzzer, LOW); //Sinon, éteindre (ou laisser éteint) le Buzzer
  }

  // Détection pression
  if (press > 511) {
    digitalWrite(Led, HIGH); // Si pression appliquée est supérieure à 511g, on allume la LED
  } else {
    digitalWrite(Led, LOW); //Sinon, éteindre (ou laisser éteinte) la LED
  }

  delay(200);
}