#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"
#include "SDCard.h"

char pot = A1;
char pressure1 = A0;
char pressure2 = A2;
int baud = 9600;

void setup() {
  // put your setup code here, to run once:


  Pot.Pot_Setup(pot);
  SDCard.SDCard_Setup(); //Comment this out if there is no SD Card otherwise the program will get stuck here
  Serial.begin(baud);
}

void loop() {
  // put your main code here, to run repeatedly:

  String dataString = "";
  dataString = String(String(millis()) + "ms, " + Pot.Pot_Run()) + " , P1:" + String(Pressure.Pressure_Run(pressure1)) + "PSI, P2:" + String(Pressure.Pressure_Run(pressure2)) + "PSI";
  Serial.println(dataString);
  SDCard.SDCard_Write(dataString);
  delay(100);        // delay in between reads for stability

}
