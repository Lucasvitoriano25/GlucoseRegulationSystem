#include <Arduino.h>
#include <SoftwareSerial.h>  
#include "main.h"

static PatientInformation PatientInformationArray[20];

void SendBluetoothMessage(StatusMessageTypeDef *Status_Message, PatientInformation *Message_To_Bluetooth)
{
  #define Attempts 3
  uint8_t i=0;
  *Status_Message  = TIMEOUT;
  
  while((*Status_Message != OK) && i < Attempts)
  {
    if (blueToothSerial.write(PatientInformationArray) != sizeof(Message_To_Bluetooth) )
    {
      i++;
    }
    else
    {
      *Status_Message  = OK;
    }
  }
}

/***************************************************************************
 * Function Name: setupBlueToothConnection
 * Description:  initilizing bluetooth connction
 * Parameters: 
 * Return: 
***************************************************************************/
void setupBlueToothConnection()
{

  blueToothSerial.begin(9600);  
	
	blueToothSerial.print("AT");
	delay(400); 
	
	blueToothSerial.print("AT+DEFAULT");             // Restore all setup value to factory setup
	delay(2000); 
	
	blueToothSerial.print("AT+NAMESeeedMaster");    // set the bluetooth name as "SeeedMaster" ,the length of bluetooth name must less than 12 characters.
	delay(400);
	
	blueToothSerial.print("AT+ROLEM");             // set the bluetooth work in slave mode
	delay(400); 
	
	
	blueToothSerial.print("AT+AUTH1");            
    delay(400);    
	
	blueToothSerial.print("AT+CLEAR");             // Clear connected device mac address
    delay(400);   
	
  blueToothSerial.flush();
	
	
}