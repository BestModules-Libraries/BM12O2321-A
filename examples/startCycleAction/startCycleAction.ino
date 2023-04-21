
/*****************************************************************
File:        CycleOperation.ino
Description:  write data to the module enter Cycle operation mode with no delay .  
Note:             
******************************************************************/
#include "BM12O2321-A.h"
BM12O2321_A myMotor(&Serial1);//HardwareSerial of BMduino BMCOM1
//BM12O2321_A HBridge(&Serial2);//HardwareSerial of BMduino BMCOM2


uint8_t cycle[13]={0x03,0x52,0x27,0x10,0x27,0x10,0x02,0x52,0x27,0x10,0x27,0x10,0x02};
  /*Thirteen byte of data need to be sent for set Cycle Operation mode
  0:foreward frequency, 1: foreward duty 86%,2-3:foreward 4135ms,4-5:stop 4135ms,
  6:corotation frequency, 7: corotation duty 86%,8-9:corotation 4135ms,10-11stop 4135ms,
  12:Number of cycles*/
uint8_t returnstatus=0;
  /*returnstatus is the status from module.If the returnstatus is 1, it indicates that the ID setting is successful. 
  If it is 2, it indicates that the module accepts the check code incorrectly. 
  If it is 3,  If it is 3, the wrong command is sent.
  If it is 0, it indicates that the ID does not receive the module information incorrectly 
  or does not receive the module information*/
  
 uint8_t EID=0x01; // The set ID value is 0x01  
void setup() {
  
  myMotor.begin();
  Serial.begin(9600);
   returnstatus=myMotor.startCycleAction(EID,cycle,0);
  /*param1(uint8_t):id is 0x01, param2(uint8_t*):Cycle Operation mode data,
  param3(bool): 1:Delay  0:No delay*/
  if(returnstatus==1)  
  {
    returnstatus=0;
    Serial.println("Set cycle operation mode successfully with id 1.");
  } 
   delay(15000); 
   returnstatus=myMotor.reset(EID);// set module reset with ID 1
  if(returnstatus==1)  
  {
    returnstatus=0;
    Serial.println("set module reset with ID 1.");
  }    
   myMotor.reset(); // Set all module reset(brostcast command)

   Serial.println("Module reset");

}

void loop() {
  
}
