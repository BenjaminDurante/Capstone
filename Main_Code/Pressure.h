class Pressure {
  private:

  //Class Variables
  char _trigPin;
  int _Product;

  public:

//Defines which port the Pressure Transducer is connected to
  void Pressure_Setup(char trigPin){
    _trigPin = trigPin;
  }

//Reads the Pressure Transducer value and outputs the pressure 
  int Pressure_Run() {
    _Product = analogRead(_trigPin);
    /*
     * 
     * 
     * Voltage to Pressure conversion below
     * 
     * 
     */
    _Product = _Product/1024*5*30; //Converts voltage to pressure in PSI
    return _Product; //Outputs pressure in PSI
  }
};
Pressure Pressure;
