/*
   SD Card Code
*/
#include <SD.h>
#include <SPI.h>
class SDCard {
  private:

  public:
    //Connects to the SD Card
    void SDCard_Setup() {
      if (!SD.begin(4)) {
        // don't do anything more:
        while (1);
      }
    }

    //Writes data to the SD Card
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
