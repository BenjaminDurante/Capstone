//Libraries and such required by this class and accessible by the main code
#include "mcp_can.h"
#include <SPI.h>
#include <stdio.h>
#define INT8U unsigned char
const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

class can {
  private:

    //Class Variables
    INT8U len = 0;
    INT8U buf[8];
    unsigned char canId;
    char str[20];
    unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  public:

    //Validates CAN Connection
    void ConnectConfirm() {
      while (CAN_OK != CAN.begin(CAN_500KBPS))   // canbus baudrate 500kbps
      {
        Serial.println("CAN BUS Shield init fail!!!");
        Serial.println("Init CAN BUS Shield again...");
        delay(100);
      }
      Serial.println("CAN BUS Initialisation Succesful");
    }


    //Function that writes CAN Outputs to the "bus"
    /*
       output = value to be sent over CAN
       port = which port to send info over (0-7)
    */
    void Log(int output, int port) {
      // send data:  id = 0x00, standard frame, data len = 8, stmp: data buf
      if (port >= 0 || port <= 7 ) {
        //Ensures that nobody enters in an invalid port number
        stmp[port] = output;
      }
      else {
        Serial.println("Invalid Port Number");
      }
    }

    //Function that sends the "bus" out
    void Send(int pause) {
      // send data:  id = 0x00, standard frame, data len = 8, stmp: data buf
      CAN.sendMsgBuf(0x00, 0, 8, stmp);
      delay(pause);                       // send data every (pause)ms
    }

    //Function that reads for CAN-Inputs
    /*
       port = which value of the CAN string to listen to

       Note: This function outputs a string so that the number can be cast to double/int, etc in the main code
    */
    String Recieve(int port) {
      String output;
      while (CAN_MSGAVAIL == CAN.checkReceive())
      {
        CAN.readMsgBuf(&len, buf);
        canId = CAN.getCanId();
        output = String(buf[port]);
      }
      return output;
    }
};
can can;
