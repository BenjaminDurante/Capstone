class Pot {
  private:

  //Class Variables
  double _Product;
  int _scale = 10; //Scales the potentiometer reading by this factor ie. 1024 divide by ____ 

  public:

  //Reads the Potentiometer value
  int Pot_Run(char trigPin) {
    _Product = analogRead(trigPin);
    _Product = _Product / _scale; //SCALING VALUE reducing the number of measurments from 1024 to ____
    return _Product;
  }

  //Reads the Potentiometer value and converts it to a distance measurement 
  /*
   * trigPin = The analog port the pot is connected to
   * high = the potentiometer value at max stroke
   * low = the potentiometer value at min stroke
   * distance = the overall physical distance between the max and min stroke (input decides units)
   */
  double Pot_Distance(char trigPin, int high, int low, double distance) {
    _Product = analogRead(trigPin);
    _Product = _Product / _scale; //SCALING VALUE reducing the number of measurments from 1024 to ____
    _Product = (_Product-low)*distance/(high - low); //Converts the potentiometer reading into a distance
    return _Product; //Returns a distance value
  }
  
};
Pot Pot;
