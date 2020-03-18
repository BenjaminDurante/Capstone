class PIDControl {
  private:

    double outputSum, lastInput, error;
    int myOutput;
    String Scope = "";

    //Sets max and min output values for PWM
    double Min = 0;
    double Max = 255;

    
    unsigned long lastTime; //Used for timing/determing derivative
    double SampleTime = 100; //default Controller Sample Time is 0.1 seconds
    boolean Direction; //Direction the motor will spin/move


  public:

  /*
   * This function starts the clock
   */
    void Setup()
    {
      lastTime = millis() - SampleTime; //Sets up this parameter so the next batch 
    }

    /*
     * This function determines at what rate to move the motor.
     * 
     * Inputs:
     * Input = Current motor/potentiometer position
     * Setpoint = Desired motor/potentiometer position
     * Kp = Proportional Gain
     * Ki = Integral Gain
     * Kd = Derivative Gain
     * 
     * Outputs:
     * PWM value from 0-255
     * Determination of direction, however due to only being able to output one class at a time this is outputted from a different class
     */
    int Run_PWM(double Input, double Setpoint, double Kp, double Ki, double Kd)
    {
      unsigned long now = millis();
      unsigned long timeChange = (now - lastTime); //Discritization 
      double outMin = Min;
      double outMax = Max;

      if (timeChange >= SampleTime)
      {
        //Compute all the working error variables
        double input = Input;
        error = Setpoint - input;
        double dInput = (input - lastInput); //Derivative on Measurement equals the negative Derivative on Error 
        outputSum += (Ki * error); //Sums each new error over time to form an integral

        //Accounts for integral windup and effectively sets Ki = 0;
        if (outputSum > outMax) outputSum = outMax;
        else if (outputSum < -outMax) outputSum = -outMax;

        //Add Proportional on Error
        double output;
        output = Kp * error;

        //Compute Rest of PID Output
        output += outputSum - Kd * dInput; //Derivative on measurement because: +dError = -dInput

        //Accounts for physical limitations of the PWM hardware/outputs
        //Also accounts for switching of directions
        if (output > outMax) {
          output = outMax;
          Direction = HIGH;
        } else if (output < -outMax) { 
          output = outMax;
          Direction = LOW;
        } else if ((output < outMin) && (output >= -outMax)) {
          output = abs(output);
          Direction = LOW;
        } else if ((output >= outMin) && (output <= outMax)) {
          Direction = HIGH;
        }

        myOutput = int(output);
//        if (error >= 0) {
//          Direction = HIGH;
//        } else {
//          Direction = LOW;
//        }

        //Remember some variables for next time
        lastInput = input;
        lastTime = now;
      }

      //Scope for testing, comment out once validated
      Scope = String(error) + " " + String(myOutput);
      Serial.println(Scope);
      
      return myOutput;
    }

    /*
     * This function outputs the direction the motor should move based on the sign of the error
     * 
     * Inputs:
     * None (as long as the previous script was run first)
     * 
     * Outputs:
     * Motor direction as either a high or low
     */
    boolean Run_Direction()
    {
      return Direction;
    }
};
PIDControl PIDControl;
