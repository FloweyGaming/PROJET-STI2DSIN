/*****************
----LIBRAIRIES----
*****************/
#include <Ultrasonic.h>
#include <arduino-timer.h>

/***********************
----SETUP COMPOSANTS----
***********************/
int pression;
float VCC = 5.0;
float VOUT;
float RC;
auto timer = timer_create_default(); //Démmarage de la fonction Timer

/*************************
----DÉFINITIONS DE PIN----
*************************/
Ultrasonic ultrasonic1(12, 13); //CapUS = PIN 12 (TRIG) & 13 (ECHO)
#define led 5 //LED = PIN 5
#define buzzer 6 //BUZZER = PIN 6
int press = A2; //CAPTEUR PRESSION = PIN A2
int motor = A0; //MOTEUR = PIN A0

/**********************
----BOUCLE INITIALE----
**********************/
void setup() {
  pinMode(motor, OUTPUT); //MOTEUR = SORTIE
  pinMode(press, INPUT); //CAPTEUR PRESSION = ENTRÉE
  pinMode(led, OUTPUT); //LED = SORTIE
  pinMode(buzzer, OUTPUT); //BUZZER = SORTIE
  Serial.begin(9600);
}

/******************************
----SI DISTANCE TROP COURTE----
******************************/
int tooclose() {
  int distance = ultrasonic1.distanceRead(); // Var "Distance" = Distance Renvoyée par CapUS
  if (distance < 20 || distance > 300) { // Si l'objet est toujours à moins de 20 cm, on allume le Buzzer
    analogWrite(A0, 255);
    digitalWrite(buzzer, HIGH); 
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    } 
}

/************************
----BOUCLE PRINCIPALE----
************************/
void loop() {
	int distance = ultrasonic1.distanceRead(); // Var "Distance" = Distance Renvoyée par CapUS
  pression = analogRead(A2); // Var "Pression" = Force Renvoyée par CapPR
  timer.tick();

  /***************************
  ----ÉCRITURE DES VALEURS----
  ***************************/
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm"); //Renvoie "<distance> cm"

  Serial.print("Poids: ");
  Serial.print(map(pression, 0, 1023, 0, 20000)); //Convertir les Valeurs de tensions en grammes (max = 2kg)
  Serial.println(" g"); //Renvoie "<pression> g"

  /****************************
  ----DÉTÉCTION DE DISTANCE----
  ****************************/
  if (distance < 20 || distance > 300) {
    timer.in(2500, tooclose); // Si un objet est à moins de 20 cm, lancer un chrono de 2.5 secondes, puis lancer la fonction "tooclose"
  } 
  else {
    digitalWrite(buzzer, LOW); //Sinon, éteindre (ou laisser éteint) le Buzzer
    analogWrite(A0, 150);
  }

  /*****************************
  ----DÉTÉCTION DE PRESSSION----
  *****************************/
  if (pression > 511) {
    digitalWrite(led, HIGH); // Si pression appliquée est supérieure à 511g, on allume la LED
  } else {
    digitalWrite(led, LOW); //Sinon, éteindre (ou laisser éteinte) la LED
  }

  delay(200);
}
