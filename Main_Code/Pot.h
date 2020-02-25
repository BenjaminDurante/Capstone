class Pot {
  private:

  //Global Variables
  char _trigPin;
  int _Product;

  public:

//Defines which port the Potentiometer is connected to
  void Pot_Setup(char trigPin){
    _trigPin = trigPin;
  }
  
  int Pot_Run() {
    _Product = analogRead(_trigPin);
    return _Product;
  }
};
Pot Pot;
