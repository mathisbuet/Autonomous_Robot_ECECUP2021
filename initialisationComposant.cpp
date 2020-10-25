#include "initialisationComposant.h"


void initialisationMoteurs()
{
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
