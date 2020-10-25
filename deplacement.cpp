#include "deplacement.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


void mouvement(char donnee){
  switch(donnee){
    case 'z':
      marcheAvant();
      break;
    case 's':
      marcheArriere();
      break;
    case 'q':
      tourneGauche();
      break;
    case 'd':
      tourneDroit();
      break;
    case ' ':
      stopMot();
      break;
    case 'g':
      deplacementSimple();
      break;
      
    case 'o':
      turnGauche();
      break;
    case 'p':
      turnDroite();
      break;
    default : 
      break;
  } 
}


void marcheArriere()
{
  analogWrite(PWMA, 1023);
  analogWrite(PWMB, 1023);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  
}


void marcheAvant()
{
  analogWrite(PWMA, 1023);
  analogWrite(PWMB, 1023);
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, HIGH);
  
}


void tourneGauche()
{
  analogWrite(PWMA, 1023);
  analogWrite(PWMB, 0);
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  
}

void tourneDroit()
{
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 1023);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);
  
  
}

void stopMot()
{
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  
}

void deplacementSimple(){
  unsigned long tpsStop=millis()+ 1000;
  while(tpsStop>millis()){
    marcheAvant();
  }
  stopMot();
  delay(1000);
  
  turnGauche();
  
  delay(1000);

  turnDroite();
  
  delay(1000);
  tpsStop = millis()+1000;
  while(tpsStop>millis()){
    marcheArriere();
  }
  stopMot();
}

void turnDroite(){

  unsigned long tpsStop = millis()+800;
  while(tpsStop>millis()){
    tourneDroit();
  }
  stopMot();
}

void turnGauche(){

  unsigned long tpsStop = millis()+800;
  while(tpsStop>millis()){
    tourneGauche();
  }
  stopMot();
}
