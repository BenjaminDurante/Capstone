#include "Pot.h"
#include "Printer.h"
#include "Pressure.h"
#include "SDCard.h"
#include "LoadCell.h"
#include "MotorControl.h"
#include "PIDControl.h"
#include "VtoP.h"
File myFile;

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

//Variables for reading preset speed data below here
double SpeedData[]={10.69444444,10.83333333,10.97222222,11.11111111,11.25,11.38888889,11.72222222,12.05555556,12.38888889,12.72222222,13.05555556,12.91666667,12.77777778,12.63888889,12.5,12.36111111,12.22222222,12.08333333,11.94444444,11.80555556,11.66666667,11.08333333,10.5,9.916666667,9.333333333,8.75,8.111111111,7.472222222,6.833333333,6.194444444,5.555555556,5.5,5.444444444,5.388888889,5.333333333,5.277777778,5.402777778,5.527777778,5.652777778,5.777777778,5.902777778,6.027777778,6.152777778,6.277777778,6.402777778,6.527777778,6.722222222,6.916666667,7.111111111,7.305555556,7.5,7.388888889,7.277777778,7.166666667,7.055555556,6.944444444,7.5,8.055555556,8.611111111,9.166666667,9.722222222,10,10.27777778,10.55555556,10.83333333,11.11111111,11.05555556,11,10.94444444,10.88888889,10.83333333,10.69444444,10.55555556,10.41666667,10.27777778,10.13888889,10.33333333,10.52777778,10.72222222,10.91666667,11.11111111,10.72222222,10.33333333,9.944444444,9.555555556,9.166666667,8.944444444,8.722222222,8.5,8.277777778,8.055555556,8.138888889,8.222222222,8.305555556,8.388888889,8.472222222,8.611111111,8.75,8.888888889,9.027777778,9.166666667,9.666666667,10.16666667,10.66666667,11.16666667,11.66666667,11.08333333,10.5,9.916666667,9.333333333,8.75,8.388888889,8.027777778,7.666666667,7.305555556,6.944444444,7.055555556,7.166666667,7.277777778,7.388888889,7.5,8.027777778,8.555555556,9.083333333,9.611111111,10.13888889,10.36111111,10.58333333,10.80555556,11.02777778,11.25,11.47222222,11.69444444,11.91666667,12.13888889,12.36111111,11.38888889,10.41666667,9.444444444,8.472222222,7.5,7.416666667,7.333333333,7.25,7.166666667,7.083333333,7.194444444,7.305555556,7.416666667,7.527777778,7.638888889};
int DataFields = 150; //Must be the same as the number proceeding
unsigned long lastTime; //Used for timing
double DriveSampleTime = 200; //Rate of data being fed in in ms
int index = 0; //Used for reading the index of the SD Card data
//Variables for reading present speed above here

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

  lastTime = millis() - DriveSampleTime; //Sets up this parameter so the next batch
  PIDControl.Setup(); //Sets up PIDControl
}

void loop() {
  // put your main code here, to run repeatedly:
  //String dataString = "";
  //dataString = String(String(millis()) + "ms, " + Pot.Pot_Run(pot1)) + " , P1:" + String(Pressure.Pressure_Run(pressure1)) + "PSI, P2:" + String(Pressure.Pressure_Run(pressure2)) + "PSI";
  //dataString = String(String(millis()) + " " + Pot.Pot_Distance(pot1, 87, 18, 50) + " , Output:" + Output);
  //dataString = String(Setpoint) + " " + String(Pot.Pot_Distance(pot1, 87, 18, 50));
  //Serial.println(dataString);

  if ( (millis() - lastTime) >= DriveSampleTime) {
    Setpoint = VtoP.VelocitytoPosition(SpeedData[index]);
    index++;
    lastTime = millis();
    if (index > DataFields) { //if we've run out of data, then don't do anything else and turn on a light
      while (HIGH) {
        digitalWrite(LED_BUILTIN, HIGH); 
        MotorControl.MotorMoveSmart(motordir1, motorpwm1, 0, HIGH); //Stops the motor from moving and the horrible whining sounds
      }
    }
  }

  pwm1 = PIDControl.Run_PWM(Pot.Pot_Distance(pot1, 87, 18, 50), Setpoint , kp , ki , kd ); //Sets PID and returns value of PWM
  dir1 = PIDControl.Run_Direction(); //Pulls out motor direction
  MotorControl.MotorMoveSmart(motordir1, motorpwm1, pwm1, dir1); //Moves motor based on PID

  //Scope to see current position vs setpoint to validate code. Comment out if using scope within PIDControl.Run_PWM function
  Scope = String(Pot.Pot_Distance(pot1, 87, 18, 50)) + "," + String(Setpoint); //Shows current position vs setpoint
  Serial.println(Scope);

  //SDCard.SDCard_Write(dataString);
  delay(25);        // delay in between reads for stability
}
