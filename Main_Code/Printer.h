class Printer {
  private:

  public:

  void Printer_Setup(int rate){
    Serial.begin(rate);
  }
  
  void Printer_Run(int potvalue) {
    Serial.println(potvalue);
    delay(10);        // delay in between reads for stability
  }
};
Printer Printer;
