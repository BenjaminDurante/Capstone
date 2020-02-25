
#include "Pot.h"





void setup() {
  // put your setup code here, to run once:
  char pot = A1;
  
  Serial.begin(9600);
  Pot.Pot_Setup(pot);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(Pot.Pot_Run());
  delay(10);        // delay in between reads for stability
}
