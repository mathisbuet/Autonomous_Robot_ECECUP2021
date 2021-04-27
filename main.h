
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include  "deplacement.h"
#include "initialisationComposant.h"

/*Declaration de la fonction de callback*/
void callback(char* topic, byte* payload, unsigned int length);
void reconnection();
