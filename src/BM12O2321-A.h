/*****************************************************************
File:             BM12O2321_A.h
Author:           BESTMODULES
Description:      Define classes and required variables
History：         
V1.0.1-- initial version；2022-11-23；Arduino IDE : v1.8.13
******************************************************************/

#ifndef  BM12O2321_A_h_
#define  BM12O2321_A_h_
#include <Arduino.h>

class BM12O2321_A
{
   public:
    BM12O2321_A(HardwareSerial *theSerial=&Serial1);
    void begin(uint16_t baud = 9600);	  
    uint8_t setEID(uint8_t EID);
    uint8_t reset(uint8_t EID);
	  void reset();
	  void standby();
    void syncAction();
	  uint16_t getFWVer(uint8_t EID);
    uint8_t startCycleAction(uint8_t EID,uint8_t buff[],bool syncAction =0);
	  uint8_t startSingleStepAction(uint8_t EID,uint8_t buff[],bool syncAction =0);
	  uint16_t getLoadWorkCurrent(uint8_t EID);
	  uint8_t isLoadWorking(uint8_t EID);
	  void  wakeUp();
  private: 
     uint8_t readBytes(uint16_t rbuf[],uint8_t rlen,uint8_t timeout=20);
	 uint8_t readData(uint8_t datalength,uint8_t EID);
	 uint8_t readData(uint8_t datalength,uint8_t EID,uint8_t buff[]);
     void writeData(uint8_t buff[],uint8_t EID,uint8_t datalength,uint8_t command);
	 void writeData(uint8_t EID,uint8_t command);
	 void writeData(uint8_t command);  
  void writeBytes(uint16_t wBuf[],uint8_t wLen);
	 HardwareSerial *_serial = NULL;
};
#define  MID                0X0119
#define  COMMAND_RESRT      0X00
#define  COMMAND_STANDY     0X01
#define  COMMAND_ACTION     0X02
#define  COMMAND_GETFWVER   0X03
#define  COMMAND_SETSINGLEOPERATION   0X09
#define  COMMAND_SETCYCLEOPERATION   0X0A
#define  COMMAND_GETLAODWORKCURRENT   0X0B
#define  SUCCESS         0
#define  FAIL            1
#define  CHECK_OK        0
#define  CHECK_ERROR     1
#define  TIMEOUT_ERROR   2
#endif
