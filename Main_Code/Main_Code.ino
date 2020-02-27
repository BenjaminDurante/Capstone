#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"
#include "LoadCell.h"

char pot = A1;
char pressure1 = A0;
char pressure2 = A2;
int baud = 9600;
int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN = 2;

void setup() {
  // put your setup code here, to run once:


  Pot.Pot_Setup(pot);
LoadCell.LoadCell_Setup(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN);
  Serial.begin(baud);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(Pot.Pot_Run()); Serial.print(" , P1:"); Serial.print(Pressure.Pressure_Run(pressure1)); Serial.print("PSI, P2:"); Serial.print(Pressure.Pressure_Run(pressure2)); Serial.print("PSI, Force:"); Serial.print(LoadCell.LoadCell_Run()); Serial.println("lbs");
  delay(100);        // delay in between reads for stability

}
