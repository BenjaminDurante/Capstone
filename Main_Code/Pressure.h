/*
   Pressure Transducer Code
*/
class Pressure {
  private:
    //Class Variables
    float _Product;

  public:
    //Reads the Pressure Transducer value and outputs the pressure
    /*
       trigPin = The analog port the pot is connected to
    */
    float Pressure_Run(char trigPin) {
      _Product = analogRead(trigPin);
      /*
         Voltage to Pressure conversion below
      */
      _Product = _Product / 1024 * 5 * 30; //Converts voltage to pressure in PSI
      return _Product; //Outputs pressure in PSI
    }
};
Pressure Pressure;
