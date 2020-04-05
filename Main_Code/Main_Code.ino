/*
   Main vehicle code
   For questions contact: benjamin.durante@ucalgary.ca
*/

//Initializing the various classes used in this main code
#include "Pot.h"
#include "Pressure.h"
#include "SDCard.h"
#include "LoadCell.h"
#include "MotorControl.h"
#include "PIDControl.h"
#include "VtoP.h"
#include "SpeedData.h" //Comment out once implementing device on the vehicle 

/*
   Assigning variables
*/
//Assigning potentiometer ports
char pot1 = A1;
char pot2 = A3;
//Assigning pressure transducers ports
char pressure1 = A0;
char pressure2 = A2;
//Assigning motor ports for the PWM and direction of the main motor
int motordir1 = 7;
int motorpwm1 = 6;
//Assigning motor ports for the PWM and direction of the bench test motor
int motordir2 = 4;
int motorpwm2 = 5;
//Setting the baud rate
int baud = 9600;
//Assigning load cell ports for the bench test validation
int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN = 2;
//Initializing the variable that will output all the data
String Scope = "";

//Values for PID
double Setpoint = 40;
double kp = 75; //Proportional
double ki = 15; //Integral
double kd = 50; //Derivative
//Initializes variables to be used for the PID of motor one
int pwm1;
boolean dir1;

//Setup code goes here
void setup() {
  //SDCard.SDCard_Setup(); //Comment this out if there is no SD Card otherwise the program will get stuck here
  //LoadCell.LoadCell_Setup(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //Setup the load cell
  MotorControl.PWMSetup(motorpwm1, motordir1); //Initializes the motor
  Serial.begin(baud); //Initializes the serial port
  while (!Serial) {
    ; //wait for serial port to connect. Needed for native USB port only
    //Good practice to include
  }
  //delay(1000); //Delay, if determined that it is required
  //SpeedData.Setup(); //Initializes the speed simulation function. COMMENT out if not testing
  PIDControl.Setup(); //Initializes the PIDControl. THIS SHOULD BE PLACED NEAR THE END OF THE PROGRAM
}

// put your main code here, to run repeatedly:
void loop() {
  Setpoint = VtoP.VelocitytoPosition(SpeedData.SpeedSimulation(motordir1, motorpwm1)); //Determines the desired actuator/pistion setpoint based on vehicle speed
  pwm1 = PIDControl.Run_PWM(Pot.Pot_Distance(pot1, 87, 18, 50), Setpoint , kp , ki , kd ); //Sets the PID and returns a value for the PWM
  dir1 = PIDControl.Run_Direction(); //Pulls out motor direction from the previous calculation and stores it to the direction variable
  MotorControl.MotorMoveSmart(motordir1, motorpwm1, pwm1, dir1); //Moves motor based on the output of the PID function

  //Scope to see current position vs setpoint to validate code. Comment out if using scope within PIDControl.Run_PWM function
  Scope = String(Pot.Pot_Distance(pot1, 87, 18, 50)) + "," + String(Setpoint); //Shows current position vs setpoint
  Serial.println(Scope); //Prints data to the serial print

  //SDCard.SDCard_Write(dataString); //Comment this out if there is no SD Card otherwise the program will get stuck here
  delay(50); // delay in between reads for stability
}
