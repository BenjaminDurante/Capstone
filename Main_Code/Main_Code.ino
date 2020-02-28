#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"
#include "SDCard.h"
#include "LoadCell.h"
#include "MotorControl.h"


char pot1 = A1;
char pot2;
char pressure1 = A0;
char pressure2 = A2;
int motordir1 = 6;
int motorpwm1 = 7;
int motordir2;
int motorpwm2;
int baud = 9600;
int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN = 2;

void setup() {
  // put your setup code here, to run once:
  //SDCard.SDCard_Setup(); //Comment this out if there is no SD Card otherwise the program will get stuck here
  LoadCell.LoadCell_Setup(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  MotorControl.PWMSetup(motorpwm1, motordir1);
  Serial.begin(baud);
}

void loop() {
  // put your main code here, to run repeatedly:
  String dataString = "";
  dataString = String(String(millis()) + "ms, " + Pot.Pot_Run(pot1)) + " , P1:" + String(Pressure.Pressure_Run(pressure1)) + "PSI, P2:" + String(Pressure.Pressure_Run(pressure2)) + "PSI";
  Serial.println(dataString);
  MotorControl.MotorMove(Pot.Pot_Distance(pot1, 87, 18, 50), 25, motordir1, motorpwm1); //87 is the high value of the pot, 18 is the low value, 50 is the stroke length in mm, the final number (25) is the target point. Motor1 is the accumulator actuator
  //SDCard.SDCard_Write(dataString);
  delay(100);        // delay in between reads for stability
}
