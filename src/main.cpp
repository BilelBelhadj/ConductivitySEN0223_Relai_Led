#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h" 

int ledState = LOW;       //statue de la led qui représente la station de pompage
const int sensorPin = 1;  //broche de capteur
const int relaiPin = 6;   //broche de CTH de relai


//changer la statue de la led
void state (){
 ledState = !ledState ;
}


void setup() {

  Serial.begin(9600);   //demarrage de moniteur serie

  wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();                  //demarrage de protocole MQTT
  
  //initialisation des broches
  pinMode(sensorPin, INPUT);
  pinMode(relaiPin, OUTPUT);

  //attendre et ecouter la broche de capteur et executer la fonction state chaque changement
  attachInterrupt(digitalPinToInterrupt(sensorPin), state, CHANGE );

}

void loop() {
  
  //appliquer la statue de la led
  digitalWrite(relaiPin, ledState);


  //envoi les donnees sur ThingsBoard
  appendPayload("Existance de fuite", ledState);  
  sendPayload(); 
}