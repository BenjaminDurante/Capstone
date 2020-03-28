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

//Variables for reading data from an SD Card below here
String filename = "test.txt";
double SpeedData[4]; //Used to store data
int DataFields = 4; //Must be the same as the number proceeding
unsigned long lastTime; //Used for timing
double DriveSampleTime = 333; //Rate of data being fed in in ms
int index = 0; //Used for reading the index of the SD Card data
//Variables for reading data from an SD Card above here

void setup() {
  // put your setup code here, to run once:
  //SDCard.SDCard_Setup(); //Comment this out if there is no SD Card otherwise the program will get stuck here
  //LoadCell.LoadCell_Setup(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  MotorControl.PWMSetup(motorpwm1, motordir1);
  Serial.begin(baud);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only also just good practice to do
  }

  //The data below here is extranousous data which can be commented out once everything is working
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  //The data above here is extranousous data which can be commented out once everything is working

  pinMode(LED_BUILTIN, OUTPUT);
  // open the file for reading:
  myFile = SD.open(filename);
  if (myFile) {
    Serial.println(filename);
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      SpeedData[index] = myFile.parseInt();
      index++;
      //Serial.write(myFile.read()); //Only needed to verify data
    }
    index = 0;
    // close the file:
    myFile.close();

    //The else below is extranousous data which can be commented out once everything is working
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

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
    if (index > DataFields) { //if we've run out of data, then don't do anything else and turn on a light
      while (HIGH) {
        digitalWrite(LED_BUILTIN, HIGH); 
      }
    }
  }

  pwm1 = PIDControl.Run_PWM(Pot.Pot_Distance(pot1, 87, 18, 50), Setpoint , kp , ki , kd ); //Sets PID and returns value of PWM
  dir1 = PIDControl.Run_Direction(); //Pulls out motor direction
  MotorControl.MotorMoveSmart(motordir1, motorpwm1, pwm1, dir1); //Moves motor based on PID
  Setpoint = 25+20*sin(millis()/1000);

  //Scope to see current position vs setpoint to validate code. Comment out if using scope within PIDControl.Run_PWM function
  Scope = String(Pot.Pot_Distance(pot1, 87, 18, 50)) + " " + String(Setpoint); //Shows current position vs setpoint
  Serial.println(Scope);

  //SDCard.SDCard_Write(dataString);
  delay(25);        // delay in between reads for stability
}
