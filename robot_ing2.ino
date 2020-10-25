#include "main.h"

const char* ssid = "Livebox-65B6";
const char* password = "w5KG5D2bF5Wd2NHbzU";
const char* mqttServer = "51.210.183.96";
const int mqttPort = 1883;
const char* mqttUser = "Squad2073";
const char* mqttPassword = "AeSeFajb";

/*Declaration de la fonction de callback*/
void callback(char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  initialisationMoteurs();//sous-programme permettant d'initialiser entrées moteurs
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

  /*Connexion au serveur MQTT*/
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  /*Veillez a bien verifier les identifiants de connexion*/
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client",mqttUser, mqttPassword))
    {
      Serial.println("connecté");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  
  client.publish("squad/squad2073", "Messaye envoyé du robot");
  client.subscribe("squad/squad2073");
  
}

void loop() {
  /*Les messages recus sont stockes dans un buffer en attendant d'etre lus. La
  fonction client.loop() permet d'y acceder et de clean le buffer*/
  client.loop();
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
  mouvement(payload[0]);
  char message[1];
  message[0] = payload[0];
  client.publish("squad/squad2073/deplacement", message);
  
}
