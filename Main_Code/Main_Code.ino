#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"

char pot1 = A1;
char pot2;
char pressure1 = A0;
char pressure2 = A2;
int motordir1;
int motorpwm1;
int motordir2;
int motorpwm2;
int baud = 9600;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(baud);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(Pot.Pot_Run(pot1)); Serial.print(" , P1:"); Serial.print(Pressure.Pressure_Run(pressure1)); Serial.print("PSI, P2:"); Serial.print(Pressure.Pressure_Run(pressure2)); Serial.println("PSI");
  delay(100);        // delay in between reads for stability

}
