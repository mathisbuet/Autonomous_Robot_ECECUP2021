#include "main.h"
#include <iostream>

#include <SimpleTimer.h>
SimpleTimer timer;

const int nbEncoches=20;

const byte fOA=D6; //moteur gauche
const byte fOB=D5; //moteur droit

char typeDeplacement='S';//A : avancer //R: reculer //S: stop

float commandeA=1023;
float commandeB=1023;

volatile byte nbInterruptA=0;
int nbChangementEtatsA=0;

volatile byte nbInterruptB=0;
int nbChangementEtatsB=0;

float vitesseA=0;
float vitesseB=0;

int distanceU;

bool uneFoisSurDeux=false;
bool asserA=false;
bool asserB=false;

const char* ssid = "Dimitri";
const char* password = "mathis123";
const char* mqttServer = "51.210.183.96";
const int mqttPort = 1883;
const char* mqttUser = "Squad2073";
const char* mqttPassword = "AeSeFajb";

/* INITIALISATION  DES ULTRASON */
const int trigPin = D7; 
const int echoPin = D8;  

// defines variables
long duration;
int distance;

/* FIN INITIALISATION  DES ULTRASON */


/* INITIALISATION  DES INFRAROUGES */
const int irD[3] ={D0,D1,D2};
bool irQqchose[3]={false,false,false};
/* FIN INITIALISATIOND DES INFRAROUGES */

WiFiClient espClient;
PubSubClient client(espClient);

void infrarouge();
ICACHE_RAM_ATTR void compteurA(){
  nbInterruptA++;
}

ICACHE_RAM_ATTR void compteurB(){
  nbInterruptB++;
}


void asservissementA(){
  vitesseA = (float)(nbChangementEtatsA)/(nbEncoches*2);
  asserA=true;
     char c[8]; // Buffer big enough for 7-character float
    dtostrf(vitesseA, 6, 2, c); // Leave room for too large numbers!
   client.publish("squad/squad2073/vitesseA", c);

  char c2[8]; // Buffer big enough for 7-character float
    dtostrf(commandeA, 6, 2, c2); // Leave room for too large numbers!
   client.publish("squad/squad2073/commandeA", c2);
   nbChangementEtatsA=0;
  
}

void asservissementB(){
  vitesseB = (float)(nbChangementEtatsB)/(nbEncoches*2);
  
  asserB=true;

  
      char c[8]; // Buffer big enough for 7-character float
    dtostrf(vitesseB, 6, 2, c); // Leave room for too large numbers!
   client.publish("squad/squad2073/vitesseB", c);

  char c2[8]; // Buffer big enough for 7-character float
    dtostrf(commandeB, 6, 2, c2); // Leave room for too large numbers!
   client.publish("squad/squad2073/commandeB", c2);


   nbChangementEtatsB=0;
}

void setup() {


  pinMode(D0,INPUT);
   pinMode(D1,INPUT);
   pinMode(D2,INPUT);
    
  pinMode(fOA, INPUT);
  pinMode(fOB, INPUT);

  timer.setInterval(1000,asservissementA);
  timer.setInterval(1000,asservissementB);
  
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  pinMode(fOA, INPUT_PULLUP);
  pinMode(fOB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(fOA),compteurA,CHANGE);
  attachInterrupt(digitalPinToInterrupt(fOB),compteurB,CHANGE);

  pinMode(D0,INPUT);
   pinMode(D1,INPUT);
   pinMode(D2,INPUT);
 
  analogWrite(PWMA, 0); //moteur gauche
  analogWrite(PWMB, 0); //moteur droit

  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  /*Connexion au WiFi*/
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connecte");
  Serial.println(WiFi.localIP());

  /*MQTT*/
  /*Connexion au serveur MQTT*/ 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  reconnection();
  
  client.subscribe("squad/squad2073/deplacement");
  client.subscribe("squad/squad2073/cubes");
   /*
  for(int i=0 ; i<3 ; i++){
    pinMode(irD[i],INPUT);
  }*/
  
  
    initialisationMoteurs();//sous-programme permettant d'initialiser entrées moteurs pinMode(D0,INPUT);
   pinMode(D0,INPUT);
   pinMode(D1,INPUT);
   pinMode(D2,INPUT);
}
int uneFoisSur30 = 0;

void loop() {
  
  if(!client.connected()){
    reconnection();
  }

  timer.run();

  if(nbInterruptA>0){
    nbChangementEtatsA++;
    nbInterruptA--;
  }

  if(nbInterruptB>0){
    nbChangementEtatsB++;
    nbInterruptB--;
  }
  
  /*
  if(typeDeplacement=='A'||typeDeplacement=='R'){
    if(asserA && asserB){
      if(vitesseA>0 && vitesseB >0){
        
        if(uneFoisSurDeux){
         if(vitesseA-vitesseB>0.02){//vitesseA-vitesseB > 
            commandeB+=(vitesseA-vitesseB)*50;
          }
          else if(vitesseB-vitesseA>0.02){
            commandeA+=(vitesseB-vitesseA)*50;
          }
          uneFoisSurDeux=false;
        }
        else{
           if(vitesseA-vitesseB>0.02){
            commandeA-=(vitesseA-vitesseB)*50;
          }
          else if(vitesseB-vitesseA>0.02){
            commandeB-=(vitesseB-vitesseA)*50;
          }
          uneFoisSurDeux=true;
        }
        asserA=false;
        asserB=false;
      }
      
      
      
      
  
    }
  }
  
  */



  /*
  Serial.print(vitesseA);
  Serial.print(", ");
  Serial.println(vitesseB);
  */
  
  
  if(typeDeplacement!='S'){

    
    analogWrite(PWMA, 1023); //moteur gauche
    analogWrite(PWMB, 1023); //moteur droit
  
  }
  else{
    analogWrite(PWMA, 0); //moteur gauche
    analogWrite(PWMB, 0); //moteur droit
  }

  
  
   uneFoisSur30++;
  if(uneFoisSur30>4000){
     infrarouge();
  ultrason();
  uneFoisSur30=0;
  }
  

  /*Les messages recus sont stockes dans un buffer en attendant d'etre lus. La
  fonction client.loop() permet d'y acceder et de clean le buffer*/
  client.loop();
}







void reconnection(){
  while(!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("Rapido", mqttUser,mqttPassword))
    {
      Serial.println("connecté");
      client.publish("squad/squad2073/connection", "Connecté :^)");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}






/*Fonction de callback.*/
void callback(char* topic, byte* payload, unsigned int length)
{
  /* 
  * Reception de l'information
  */
  Serial.print("Le message arrive du topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
  
  /* 
  * Traitement de l'information
  */
  /*
  if(topic=="squad/squad2073/cubes"){
    //cubes(payload);


    
  }
  else if(topic=="squad/squad2073/deplacement"){
    
   mouvement(payload[0], typeDeplacement);

  }
*/

mouvement(payload[0], typeDeplacement);
  
  
  char message[1];
  message[0] = payload[0];
  client.publish("squad/squad2073/recoit", message);
  
}

void ultrason(){
  int temp=distanceU;
   distanceU=distanceUltraBas();
  if(distanceU!=temp){
    mqtt_publish("squad/squad2073/dUltra",distance);
  }
  



  
}



int distanceUltraBas(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;
  
}


//Fonction pour publier un float sur un topic 
void mqtt_publish(String topic, int t){
  char top[topic.length()+1];
  topic.toCharArray(top,topic.length()+1);
  char t_char[50];
  String t_str = String(t);
  t_str.toCharArray(t_char, t_str.length() + 1);
  client.publish(top,t_char);
}

void infrarouge(){
  bool irTemp[3];

  /* ON COPIE LE TABLEAU infraroue DANS LE tableau temp */
  for(int i=0; i<3; i++){
     irTemp[i] = irQqchose[i];
     
  }

 
  /* CHECK LES INFRAROUGES */
  for(int i=0; i<3; i++){
      if(digitalRead(irD[i])==LOW){
        irQqchose[i]=true;
        Serial.print("1");
      }
      else{
        Serial.print("0");
        irQqchose[i]=false;
      }
        
  }
  Serial.println();
  /* REGARDE SI C'EST DIFFERENT */
  for(int i=0; i<3; i++){
    if(irTemp[i] != irQqchose[i]){
      char envoyer[3];

      
      for(int j=0; j<3; j++){
        if(irQqchose[j])
          envoyer[j]='1';
        else 
          envoyer[j]='0';
        
      }



      client.publish("squad/squad2073/ir",envoyer);
      break;
    }
  }
  

}
