class Pot {
  private:
  
  char _trigPin;
  int _Product;

  public:

  void Pot_Setup(char trigPin){
    _trigPin = trigPin;
  }
  int Pot_Run() {
    _Product = analogRead(_trigPin);
    return _Product;
  }
};
Pot Pot;
