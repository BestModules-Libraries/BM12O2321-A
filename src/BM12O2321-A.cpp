 /*****************************************************************
File:             BM12O2321_A.cpp
Author:           BESTMODULES
Description:      Define classes and required variables
History：         
V1.0.1-- initial version；2022-11-23；Arduino IDE : v1.8.13
******************************************************************/
#include  "BM12O2321-A.h"
uint8_t  cycletimes;
/**********************************************************
Description: H Bridge initial
Parameters:       
      *theSerial：hardware serial 
      BMduino optional:serial(default) serial1/seria2/seria3/seria4
Return:      none      
Others:      
**********************************************************/
BM12O2321_A::BM12O2321_A(HardwareSerial *theSerial)
{
  cycletimes=0;
  _serial=theSerial;
}

/**********************************************************
Description: BM12O2321_A begin ,set _serial parameter 
Parameters:  baud : Set the Module  baud(Unique Value 9600)     
Return:      none      
Others:      
**********************************************************/

void BM12O2321_A::begin(uint16_t baud)
{
     _serial->begin(baud,SERIAL_9N1);
    _serial->setTimeout(30);
}

/**********************************************************
Description: set EID 
Parameters:      
	   EID: New EID
Return:      none      
Others:      
**********************************************************/
 uint8_t  BM12O2321_A::setEID(uint8_t EID)
{ 
	 uint8_t command;
		command=(0x80+(EID&0x0f));
		writeData(command);
		if(readData(2, EID)==SUCCESS)
		{
			return SUCCESS;
		}
		else
		{
			return FAIL	;
		}
}
/**********************************************************
Description: module reset
Parameters:      
            EID:EID of the module
Return:      1： Reset failed   
             0：  Reset successful
Others:      
**********************************************************/
 uint8_t  BM12O2321_A::reset(uint8_t EID)
 {	
		writeData(EID, COMMAND_RESRT);
		if(readData(2, EID)==SUCCESS)
		{
			return SUCCESS;
		}
		else
		{
			return FAIL	;
		}	 
 }
 
 /**********************************************************
Description: module reset（Broadcast command）
Parameters:                  
Return:   none  
Others:     
**********************************************************/ 
  void  BM12O2321_A::reset()
 {
	writeData(COMMAND_RESRT);
 }
 
/**********************************************************
Description: Command module sleep（Broadcast command）
Parameters:      
Return:      none      
Others:      
**********************************************************/ 
void  BM12O2321_A::standby()
 {
	writeData(COMMAND_STANDY);
 }
 /**********************************************************
Description: Set module synchronization action（Broadcast command）
Parameters:   none  
Return:      none      
Others:      
**********************************************************/ 
void  BM12O2321_A::syncAction()
 {	 
	writeData(COMMAND_ACTION);
 }
 /**********************************************************
Description: get FW version
Parameters:      
          EID:EID of the module			
Return:      FW version      
Others:      
**********************************************************/
uint16_t  BM12O2321_A::getFWVer(uint8_t EID)
{
	uint8_t buff1[6];
	uint16_t FWVer=0;
	writeData( EID,COMMAND_GETFWVER);
	if(readData( 4, EID,buff1)==SUCCESS)
	{
		FWVer=buff1[1]<<8|buff1[0];
		return FWVer;	
	}
        else 	
	{
		return 0;		
	}


}
 /**********************************************************
Description: set Cycle Operation Mode
Parameters:       
       EID:EID of the module
       buff:Variables for storing Data to be write
       syncAction:syncAction=1,Delayed execution
             syncAction=0,Executes immediately, without delay
Return:      1： Reset failed   
             0：  Reset successful     
Others:      
**********************************************************/
uint8_t BM12O2321_A::startCycleAction(uint8_t EID,uint8_t buff[],bool syncAction )
{	
	 uint8_t datalength=15;
	 uint8_t command1=0;
	if(syncAction)
	{
		command1=COMMAND_SETCYCLEOPERATION |0x20;
	}
	else
	{
		command1=COMMAND_SETCYCLEOPERATION;
	}
	writeData(buff,EID,datalength,command1);
	if(readData(2, EID)==SUCCESS)
	{
		return SUCCESS;
	}
	else
	{
		return FAIL	;
	}	
}
 /**********************************************************
Description: set Single Operation Mode
Parameters:       
      EID:ID of the module
      buff:Variables for storing Data to be write
      syncAction:syncAction=1,Delayed execution
             syncAction=0,Executes immediately, without delay
Return:      1： Reset failed   
             0： Reset successful     
Others:      
**********************************************************/
uint8_t BM12O2321_A::startSingleStepAction(uint8_t EID,uint8_t buff[],bool syncAction )
{	
	 uint8_t datalength=7;
	 uint8_t  command1=0;
	if(syncAction)
	{
		command1= COMMAND_SETSINGLEOPERATION|0x20;
	}
	else
	{
		command1= COMMAND_SETSINGLEOPERATION;
	}
	writeData(buff,EID,datalength,command1);
	if(readData(2, EID)==SUCCESS)
	{
		return SUCCESS;
	}
	else
	{
		return FAIL	;
	}
}

 /**********************************************************
Description: get load workingcurrent 
Parameters:       
             EID:ID of the module		        
Return:     load workingcurrent (mA)      
Others:      
**********************************************************/
uint16_t BM12O2321_A::getLoadWorkCurrent(uint8_t EID)
{
	uint8_t buff1[6];
	writeData( EID,COMMAND_GETLAODWORKCURRENT);
	if(readData( 5, EID,buff1)==SUCCESS)
	{
		return ((buff1[2]<<8)+buff1[1]);
	}
   else 	
	{
		return 0;		
	}
}
 /**********************************************************
Description: judging  whether the load is working
Parameters:       
            EID:ID of the module
Return:      
       0:the load is not working
       1:the load is working      
Others:      
**********************************************************/
uint8_t BM12O2321_A::isLoadWorking(uint8_t EID)
{
	uint8_t buff1[6];
	writeData( EID,COMMAND_GETLAODWORKCURRENT);
	if(readData( 5, EID,buff1)==SUCCESS)
	{     
		return buff1[0];
	}
  else 	
	{
		return 0;		
	}		

}
 /**********************************************************
Description: set module wakeup
Parameters:       none
Return:      none      
Others:      
**********************************************************/
void BM12O2321_A::wakeUp()
{
     _serial->write(0x0001);
}
/**********************************************************
Description: Read data through UART
Parameters: 
            rbuf: Used to store received data
            rlen: Length of data to be read
            timeout:timeout time (ms)
Return: 0: check ok
        1: check error
        2: timeout error
Others: None
**********************************************************/
uint8_t BM12O2321_A:: readBytes(uint16_t rbuf[],uint8_t rlen,uint8_t timeout)
{ 
  uint8_t i = 0, delayCnt = 0, checkSum = 0;
  /*clear buf*/
  for(i = 0; i < rlen; i++)
  {
    rbuf[i] = 0;
  }
  
  for (i = 0; i < rlen; i++)
    {
      delayCnt = 0;
      while (_serial->available() == 0)
      {
        if (delayCnt > timeout)
        {
          return TIMEOUT_ERROR; // Timeout error
        }
        delay(1);
        delayCnt++;
      }
      rbuf[i] = _serial->read();
    }
     /* check Sum */
    for(uint8_t i=0; i<rlen;i++)
    {
      checkSum=(uint8_t)(checkSum+rbuf[i]);
    }
    if(checkSum==0xff)
    {
      return CHECK_OK ;
    }
    else
    {
      return CHECK_ERROR;
    }
}

/**********************************************************
Description: read data 
Parameters: 
            datalength:Number of data bytes to be read 
            EID:module EID
Return: 
            0： Reset successful
            1： Reset failed
Others: None
**********************************************************/
uint8_t BM12O2321_A:: readData(uint8_t datalength,uint8_t EID)
{
  uint16_t readbuff[8];
  if(readBytes( readbuff,datalength+2,20)==0)
  {
    if((readbuff[2]==0)&&(readbuff[0]=0x0119)&&((readbuff[1]&0x000f)==(EID&0x000f)))
    {
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

/**********************************************************
Description: read data 
Parameters: 
            datalength:Number of data bytes to be read
            buff[]:Store the read data
            EID:module EID
Return:             
            0： Reset successful
            1： Reset failed
Others: None
**********************************************************/
uint8_t BM12O2321_A:: readData(uint8_t datalength,uint8_t EID,uint8_t buff[])
{
  uint16_t readbuff[8];
  if(readBytes( readbuff,datalength+2,20)==0)
  {
    if((readbuff[2]==0)&&(readbuff[0]=0x0119)&&((readbuff[1]&0x000f)==(EID&0x000f)))
    {
      for(uint8_t i=0;i<datalength-2;i++)
      {
        buff[i]=readbuff[i+3];
      }
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

/**********************************************************
Description: UART writeData
Parameters:      
            wBuf: Used to store received data
            wLen: Length of data to be written
Return:      none      
Others:      
**********************************************************/
void BM12O2321_A:: writeBytes(uint16_t wBuf[],uint8_t wLen)
{
  while(_serial->available())
  {
    _serial->read();
  }
  _serial->SetRxStatus(DISABLE);
  for(uint8_t i = 0; i<wLen ;i++)
  {
    _serial->write(wBuf[i]);
  }
    _serial->flush();
    _serial->SetRxStatus(ENABLE);
}

/**********************************************************
Description: UART writeData(Do write data)
Parameters:
            buff:Variables for storing Data to be send
            ID:ID of the module
            datalength:Length of data plus command
            command: Commands sent
Return:      none      
Others:      
**********************************************************/
void BM12O2321_A:: writeData(uint8_t buff[],uint8_t ID,uint8_t datalength,uint8_t command)
{
  uint16_t i= 0;
  uint16_t wBuf[255];
  static uint16_t data[17];
  static uint8_t checksum;
  static uint8_t length;
  data[0]=((datalength<<4)+(ID&0x0f));
  checksum=(uint8_t)(MID+data[0]+command);
  wBuf[i] = MID;
  i++;
   wBuf[i] = (data[0]&0x00ff);
   i++;
   wBuf[i] = (command&0x00ff);
    i++;
  for(length=0;length<datalength-2;length++)
  {
    wBuf[i] = (buff[length]&0x00ff);
   checksum=(uint8_t)(checksum+buff[length]);
   i++;
  }
  wBuf[i] = ((~checksum)&0x00ff);
   writeBytes(wBuf,i+1);
}

/**********************************************************
Description: UART writeData(Do not write data)
Parameters:      
            EID:ID of the module
            command: Commands sent
Return:      none      
Others:      
**********************************************************/
void BM12O2321_A:: writeData(uint8_t EID,uint8_t command)
{
  uint16_t sandData[255];
  static uint16_t data[4];
  static uint8_t checksum=0;
  _serial->SetRxStatus(DISABLE);
  data[0]=(0x0020+(EID&0x0f));
  checksum=(uint8_t)(MID+data[0]+command);
  sandData[0]=MID;
  sandData[1]=data[0]&0x00ff;
  sandData[2]=command&0x00ff;
  sandData[3]=(~checksum)&0x00ff;
  writeBytes(sandData,4);
}
/**********************************************************
Description: UART writeData(radio broadcast)
Parameters:      
      command: Commands sent
Return:      none      
Others:      
**********************************************************/
void BM12O2321_A:: writeData(uint8_t command)
{
   uint16_t sandData[4];
  static uint8_t checksum =0; 
  checksum=(uint8_t)(0X00+0x20+command);
  sandData[0]=0x0100;
  sandData[1]=0x0020;
  sandData[2]=command&0x00ff;
  sandData[3]=(~checksum)&0x00ff;
  writeBytes(sandData,4);
}
