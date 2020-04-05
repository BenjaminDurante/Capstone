/*
   Load cell code if the device is currently being used with the bench test setup
   Otherwise this code should not be called
*/
#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711
class LoadCell {

  private:
    //Class Variables
#define calibration_factor -39870.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
    HX711 scale;
    float _Product; \

  public:
    //Calibrates and zeros the load cell upon setup
    void LoadCell_Setup(int Dout, int SCK) {
      scale.begin(Dout , SCK);
      scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
      //scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0
    }
    //Reads the Load Cell value and outputs the force in lbs
    float LoadCell_Run() {
      _Product = scale.get_units();
      return _Product; //Outputs pressure in lbs
    }
};
LoadCell LoadCell;
