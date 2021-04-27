#include "deplacement.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


void mouvement(char donnee, char& typeDeplacement){
  switch(donnee){
    case 'z':
      marcheAvant(typeDeplacement);

      break;
    case 'r':
      marcheArriere(typeDeplacement);

      break;
    case 'q':
      tourneGauche(typeDeplacement);

      break;
    case 'd':
      tourneDroit(typeDeplacement);
      
      break;

    case 'm':
       //prendreModule(commandeA,commandeB);
       stopMot(typeDeplacement);
       break;
    case ' ':
      stopMot(typeDeplacement);
      break;

    case 's':
      stopMot(typeDeplacement);
      break;


      
    
    case 'o':
      turnGauche(typeDeplacement);
      break;
    case 'p':
      turnDroite(typeDeplacement);
      break;
       
    default : 
      break;
     
  } 
}



void marcheArriere(char& typeDeplacement)
{

  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  typeDeplacement='R';
}


void marcheAvant(char& typeDeplacement)
{

  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, HIGH);
  typeDeplacement='A';
}


void tourneGauche(char& typeDeplacement)
{



  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);

 typeDeplacement='G';
  

  
}

void tourneDroit(char& typeDeplacement)
{
  

    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);



   typeDeplacement='D';
  
}



void turnDroite(char& typedDeplacement){ //90 degrés à droite 

  unsigned long tpsStop = millis()+800;
  while(tpsStop>millis()){
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
    analogWrite(PWMA, 1023);
    analogWrite(PWMB, 1023);
  }
  typedDeplacement='S';
}

void turnGauche(char& typedDeplacement){ //90 degrés à gauche



  unsigned long tpsStop = millis()+800;
  //ALLER A GAUCHE
  while(tpsStop>millis()){
        digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
    analogWrite(PWMA, 1023);
    analogWrite(PWMB, 1023);

  }
  typedDeplacement='S';
}




void stopMot(char& typeDeplacement)
{
  typeDeplacement='S';
  
}

/*
void prendreModule(float& commandeA, float& commandeB){
  unsigned long tpsStop = millis()+1000;
  //RECULER
  while(tpsStop>millis()){
        digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
    analogWrite(PWMA, 1023);
    analogWrite(PWMB, 1023);

  }

  tpsStop = millis()+350;
  //DROITE
  while(tpsStop>millis()){
        digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
    analogWrite(PWMA, 1023);
    analogWrite(PWMB, 1023);

  }


  tpsStop = millis()+1000;
  //AVANCER
  while(tpsStop>millis()){
        digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, HIGH);
    analogWrite(PWMA, 1023);
    analogWrite(PWMB, 1023);

  }

  tpsStop = millis()+350;
  //ALLER A GAUCHE
  while(tpsStop>millis()){
        digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
    analogWrite(PWMA, 1023);
    analogWrite(PWMB, 1023);

  }


  
}
*/
