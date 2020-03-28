class VtoP {
  private:

  double Position;
  public:

  //Reads the vehicle speed and outputs the setpoint position
  /*
   * x = Vehicle speed in m/s 
   */
  double VelocitytoPosition(double x) {
    Position = 0.0003*x*sq(x)-0.0117*sq(x)-0.0019*x+1.9215; //Converting vehicle speed to actuator position in inches
    Position = Position * 25.4; //Converting from inches to mm
    return Position; //Returns a position the actuator should be at
  }
  
};
VtoP VtoP;
