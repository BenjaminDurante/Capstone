class MotorControl 
{
  private:

  //Class Variables
  
  int pwm_value = 0;


  public:

  void PWMSetup (int pwm, int dir)
  {
    pinMode(pwm,OUTPUT);
    pinMode(dir,OUTPUT);
  }

  void MotorMove(int pos, int PotValue)
  {
    if(PotValue>pos)
    {
      pwm_value = 255;
        digitalWrite(dir,LOW);
        analogWrite(pwm,pwm_value);
    }
    
    if(PotValue<pos)
    {
      pwm_value = 255;
        digitalWrite(dir,HIGH);
        analogWrite(pwm,pwm_value);
    }
  }
}
MotorControl MotorControl;
