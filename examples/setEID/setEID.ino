
/*****************************************************************
File:        setID.ino
Description:  write data to the module set ID. And get the FW version.
Note: 
******************************************************************/

#include <BM12O2321-A.h>
BM12O2321_A myMotor(&Serial1);//HardwareSerial of BMduino BMCOM1
//BM12O2321_A HBridge(&Serial2);//HardwareSerial of BMduino BMCOM2

uint8_t returnstatus=0;
  /*returnstatus is the status from module.If the returnstatus is 1, it indicates that the ID setting is successful. 
  If it is 2, it indicates that the module accepts the check code incorrectly. 
  If it is 3,  If it is 3, the wrong command is sent.
  If it is 0, it indicates that the ID does not receive the module information incorrectly 
  or does not receive the module information*/
uint16_t FWversion;
const uint8_t EID=0x01; // The set ID value is 0x01
void setup() {

  myMotor.begin();
  Serial.begin(9600);

  returnstatus=myMotor.setEID(EID);// SET ID,ID is 0x01

  if(returnstatus==SUCCESS)  
  {
    returnstatus=FAIL;
    Serial.println("ID set successfully");
  }
  delay(10);
   FWversion=myMotor.getFWVer(EID);// get FW version of the module  whose id is 0x01
    Serial.print("FW version is V");
    Serial.println(FWversion,HEX);

   
}

void loop() {
  
}
