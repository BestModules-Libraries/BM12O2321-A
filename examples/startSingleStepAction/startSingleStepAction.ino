/*****************************************************************
File:        SingleOperation.ino
Description:  write data to the module enter single operation mode with delay action.  
Note:             
******************************************************************/
#include <BM12O2321-A.h>
BM12O2321_A myMotor(&Serial1);//HardwareSerial of BMduino BMCOM1
//BM12O2321_A HBridge(&Serial2);//HardwareSerial of BMduino BMCOM2

  /*returnstatus is the status from module.If the returnstatus is 1, it indicates that the ID setting is successful. 
  If it is 2, it indicates that the module accepts the check code incorrectly. 
  If it is 3,  If it is 3, the wrong command is sent.
  If it is 0, it indicates that the ID does not receive the module information incorrectly 
  or does not receive the module information*/
 uint8_t single[5]={0x01,0x03,0x56,0x10,0x27};
  /*Five byte of data need to be sent for set Single Operation mode
  0:foreward, 1:4khz, 2:86%duty ,3-4: 10s*/
 uint8_t EID=0x01; // The set ID value is 0x01  

//uint16_t current;// load work current data  


void setup() {

  myMotor.begin();
  Serial.begin(9600);
  /*param1(uint8_t):id is 0x01, param2(uint8_t*):single Operation mode data,
  param3(bool): 1:Delay  0:No delay*/
  if(myMotor.startSingleStepAction(EID,single,1)== 1)  
  {
  Serial.println("Set single operation mode successfully with id 1,wait for action.");
  }  
  delay(1000); 
  myMotor.syncAction();// Broadcast command, all modules action
  Serial.println("Action."); 
} 
void loop() {
        
        if(myMotor.isLoadWorking(EID)== 1)
        {
         Serial.println("singleStepAction... ");
         Serial.print("current: ");
       uint16_t  current=myMotor.getLoadWorkCurrent(EID);
        if(current>120)
         {
            Serial.print(current,DEC);
            Serial.println("mA.");
         }
         else
         {
            Serial.println("< 120 mA");
         }
        }
        else
        {
       Serial.println("singleStepAction finish.");
        }
        delay(800);     
}
