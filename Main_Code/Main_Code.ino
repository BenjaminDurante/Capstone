
#include "Pot.h"
#include "Printer.h"




void setup() {
  // put your setup code here, to run once:
  char pot = A1;
  int baud = 9600;
  
  Printer.Printer_Setup(baud);
  Pot.Pot_Setup(pot);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(Pot.Pot_Run());
//  delay(10);        // delay in between reads for stability

  Printer.Printer_Run(Pot.Pot_Run());
}