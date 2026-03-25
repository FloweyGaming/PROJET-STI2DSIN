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
#define fin 7 //CAPTEUR FIN DE COURSE = PIN 7
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
  digitalWrite(buzzer, LOW); //BUZZER ÉTEINT
  pinMode(fin, INPUT); //CAPTEUR FIN DE COURSE = ENTRÉE
  Serial.begin(9600);
}

/******************************
----SI DISTANCE TROP COURTE----
******************************/
int tooclose(){
  int distance = ultrasonic1.distanceRead(); // Var "Distance" = Distance Renvoyée par CapUS
  if (distance < 20 || distance > 300) { // Si l'objet est toujours à moins de 20 cm, on allume le Buzzer
    analogWrite(A0, 255);
    digitalWrite(buzzer, HIGH); 
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    Serial.println("WARNING");
    } 
}

/************************
----BOUCLE PRINCIPALE----
************************/
void loop() {
	int distance = ultrasonic1.distanceRead(); // Var "Distance" = Distance Renvoyée par CapUS
  int pression = analogRead(A2); // Var "Pression" = Force Renvoyée par CapPR
  long int poids = pression*19.55; // Var "Poids" = Conversion Tension vers Masse -- Pression * 19.55 (Pression * 20000 / 1023)
  timer.tick();

  /***************************
  ----ÉCRITURE DES VALEURS----
  ***************************/
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm"); //Renvoie "<distance> cm"

  Serial.print("Poids: ");
  // [ANCIEN] Serial.print(map(pression, 0, 1023, 0, 20000)); //Convertir les Valeurs de tensions en grammes (max = 2kg)
  Serial.print(poids);
  Serial.println(" g"); //Renvoie "<poids> g"

  /****************************
  ----DÉTÉCTION DE DISTANCE----
  ****************************/
  if (distance < 20 || distance > 300) {
    timer.in(3500, tooclose); // Si un objet est à moins de 20 cm, lancer un chrono de 3.5 secondes, puis lancer la fonction "tooclose"
  } 
  else {
    digitalWrite(buzzer, LOW); //Sinon, éteindre (ou laisser éteint) le Buzzer
    analogWrite(A0, 150);
  }

  if (digitalRead(fin) == HIGH) {
    Serial.println("FDC"); //Renvoie "FDC"
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
