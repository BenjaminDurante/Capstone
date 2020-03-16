#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"
#include "SDCard.h"
#include "LoadCell.h"
#include "MotorControl.h"


char pot1 = A1;
char pot2 = A3; 
char pressure1 = A0;
char pressure2 = A2;
int motordir1 = 6;
int motorpwm1 = 7;
int motordir2 = 4;
int motorpwm2 = 5;
int baud = 9600;
int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN = 2;
float i = 0;
float j = 0;
long previousMillis = 0;
long currentMillis = millis();


void setup() {
  // put your setup code here, to run once:
  //SDCard.SDCard_Setup(); //Comment this out if there is no SD Card otherwise the program will get stuck here
  LoadCell.LoadCell_Setup(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  MotorControl.PWMSetup(motorpwm1, motordir1);
  MotorControl.PWMSetup(motorpwm2, motordir2);
  Serial.begin(baud);
}

void loop() {
 
 
  for (i = 0.25; i<=1.25; i = i + 0.05) //for loop that will increment the piston stroke (in)
  {
    
    previousMillis = currentMillis;
    
    while (currentMillis - previousMillis <= 5000)
          {
            MotorControl.MotorMove(Pot.Pot_Distance(pot2, 88, 21, 49.9), (i*25.4), motordir2, motorpwm2); //88 is the high value of the pot, 21 is the low value, 50 is the stroke length in mm, i is multiplied by 25.4(25 for rounding) to convert in to mm and is the set point for the accum. Motor1 is the accumulator actuator
            currentMillis = millis();
          }
    //Serial.println();
//    Serial.print(" i: ");
//    Serial.print(i);
    previousMillis = currentMillis; // save the last recorded time
    
      for (j = 0; j<=2.05; j = j + 0.6666667)//for loop that will increment the accumulator (note that I am unsure with rounding how the for loop logic will work, so i set condition for 2 but should only go to 1.9)
      {
          while (currentMillis - previousMillis <= 4000)
          {
            MotorControl.MotorMove(Pot.Pot_Distance(pot1, 87, 18, 50.5), (j*25.4), motordir1, motorpwm1); //87 is the high value of the pot, 18 is the low value, 50 is the stroke length in mm, j is multiplied by 25.4(25 for rounding) to convert in to mm and is the set point for the accum. Motor1 is the accumulator actuator
            currentMillis = millis();
          }
          
//          String dataString = "";
//          String pressureString = "";
//          pressureString = String(Pot.Pot_Run(pot1)) + " , P1: " + String(Pressure.Pressure_Run(pressure1)) + "PSI, P2: " + String(Pressure.Pressure_Run(pressure2)) + "PSI";
//          dataString = String(LoadCell.LoadCell_Run());
//          //SDCard.SDCard_Write(dataString);
//          Serial.print(" j: ");
//          Serial.print(j);
//          Serial.print(" ");
//          Serial.print(dataString);
//          Serial.print(" lbs ");
//          Serial.print(pressureString);

//Testing printouts below

          String dataString2 = "";
          String pressureString2 = "";
          pressureString2 = String(Pot.Pot_Run(pot2)) + "," + String(Pot.Pot_Run(pot1)) + "," + String(Pressure.Pressure_Run(pressure1)) + "," + String(Pressure.Pressure_Run(pressure2)) + ",";
          dataString2 = String(LoadCell.LoadCell_Run()) + ",";
          Serial.print(pressureString2);
          Serial.print(dataString2);
         if(j>1.40)
         {
          Serial.println();
         }
          
          
          previousMillis = currentMillis; // save the last recorded time
  
      }
  }

}
