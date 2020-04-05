/*
   Motor code used to run/move motors
*/
class MotorControl
{

  private:
    //Class Variables
    int pwm_value = 0;

  public:
    //Sets up the pins for output
    void PWMSetup (int pwm, int dir)
    {
      pinMode(pwm, OUTPUT);
      pinMode(dir, OUTPUT);
    }

    //Moves the motor to a given position based on simple logic
    /*
       pos = desired position
       PotValue = current position
       dir = pin associated with the motors direction
       pwm = pin associated with the motor pwm signal
    */
    void MotorMove(int pos, int PotValue, int dir, int pwm)//PotValue is the target value and will change with the control system, pos is the current position
    {
      if (PotValue > pos) //if target is greater than current position then extend
      {
        pwm_value = 255;//speed
        digitalWrite(dir, HIGH); //writing to motor controller direction of travel
        analogWrite(pwm, pwm_value); //writing to motor controller speed of travel
      }
      if (PotValue == pos) //if target is at current position sets speed to 0, may need to convert to a range in the future so that small impulses dont affect as much
      {
        pwm_value = 0;
        digitalWrite(dir, HIGH); //writing to motor controller direction of travel, direction doesnt matter in this case since speed is zero
        analogWrite(pwm, pwm_value); //writing to motor controller speed of travel
      }
      if (PotValue < pos) //if target value is less than current position then retract
      {
        pwm_value = 255;
        digitalWrite(dir, LOW); //writing to motor controller direction of travel
        analogWrite(pwm, pwm_value); //writing to motor controller speed of travel
      }
    }

    //Moves based on external directions
    /*
       dir = pin associated with the motors direction
       pwm = pin associated with the motor pwm signal
       pwm_value = value of the PWM signal from 0-255
       dir_value = direction of the motor, either HIGH or LOW
    */
    void MotorMoveSmart(int dir, int pwm, int pwm_value, boolean dir_value) //Will move as instructed by the PID
    {
      digitalWrite(dir, dir_value); //writing to motor controller direction of travel
      analogWrite(pwm, pwm_value); //writing to motor controller speed of travel
    }
};
MotorControl MotorControl;
