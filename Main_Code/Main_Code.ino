#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"
#include "SDCard.h"
#include "LoadCell.h"
#include "MotorControl.h"
#include "PIDControl.h"
#include "VtoP.h"
#include "SpeedData.h"

char pot1 = A1;
char pot2 = A3;
char pressure1 = A0;
char pressure2 = A2;
int motordir1 = 7;
int motorpwm1 = 6;
int motordir2 = 4;
int motorpwm2 = 5;
int baud = 9600;
int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN = 2;
String Scope = "";

//Values for PID Testing below here
double Setpoint = 40;
double kp = 75;
double ki = 15;
double kd = 50;
int pwm1;
boolean dir1;
//Values added for PID testing above here

void setup() {
  // put your setup code here, to run once:
  //SDCard.SDCard_Setup(); //Comment this out if there is no SD Card otherwise the program will get stuck here
  //LoadCell.LoadCell_Setup(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  MotorControl.PWMSetup(motorpwm1, motordir1);
  Serial.begin(baud);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only also just good practice to do
  }
  delay(2000);

  SpeedData.Setup(); //Sets up the speed simulation function
  PIDControl.Setup(); //Sets up PIDControl
}

void loop() {
  // put your main code here, to run repeatedly:
  //String dataString = "";
  //dataString = String(String(millis()) + "ms, " + Pot.Pot_Run(pot1)) + " , P1:" + String(Pressure.Pressure_Run(pressure1)) + "PSI, P2:" + String(Pressure.Pressure_Run(pressure2)) + "PSI";
  //dataString = String(String(millis()) + " " + Pot.Pot_Distance(pot1, 87, 18, 50) + " , Output:" + Output);
  //dataString = String(Setpoint) + " " + String(Pot.Pot_Distance(pot1, 87, 18, 50));
  //Serial.println(dataString);


    Setpoint = VtoP.VelocitytoPosition(SpeedData.SpeedSimulation(motordir1, motorpwm1));

  pwm1 = PIDControl.Run_PWM(Pot.Pot_Distance(pot1, 87, 18, 50), Setpoint , kp , ki , kd ); //Sets PID and returns value of PWM
  dir1 = PIDControl.Run_Direction(); //Pulls out motor direction
  MotorControl.MotorMoveSmart(motordir1, motorpwm1, pwm1, dir1); //Moves motor based on PID

  //Scope to see current position vs setpoint to validate code. Comment out if using scope within PIDControl.Run_PWM function
  Scope = String(Pot.Pot_Distance(pot1, 87, 18, 50)) + "," + String(Setpoint); //Shows current position vs setpoint
  Serial.println(Scope);

  //SDCard.SDCard_Write(dataString);
  delay(50);        // delay in between reads for stability
}
