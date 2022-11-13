#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

void SendBluetoothMessage(StatusMessageTypeDef *Status_Message, PatientInformation *Message_To_Bluetooth);
void setupBlueToothConnection();

#endif