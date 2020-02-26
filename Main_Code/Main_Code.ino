
#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"


void setup() {
  // put your setup code here, to run once:
  char pot = A1;
  char pressure = A0;
  int baud = 9600;


  Pressure.Pressure_Setup(pressure);
  Pot.Pot_Setup(pot);

  Serial.begin(baud);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(Pot.Pot_Run()); Serial.print(" , "); Serial.print(Pressure.Pressure_Run()); Serial.println("PSI");
  delay(100);        // delay in between reads for stability

}
