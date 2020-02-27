#include <SD.h>
#include <SPI.h>

class SDCard {
  private:

    const int chipSelect = 4;

  public:

    //Defines which port the Potentiometer is connected to
    void SDCard_Setup() {
      if (!SD.begin(chipSelect)) {
        // don't do anything more:
        while (1);
      }
    }

    void SDCard_Write(String dataString) {

      // make a string for assembling the data to log:
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      File dataFile = SD.open("datalog.txt", FILE_WRITE);

      // if the file is available, write to it:
      if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
      }
    }
};
SDCard SDCard;
