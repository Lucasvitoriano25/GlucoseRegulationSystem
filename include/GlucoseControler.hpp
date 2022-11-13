#ifndef __GLUCOSECONTROLER_H
#define __GLUCOSECONTROLER_H

void UpdateDisplay(int glycemie, int insuline);
void InjectInsuline(int InsulineToBeInjected);
void SaveInformations(uint16_t InsulineValueToSave,uint16_t NewGlucoseLevelToSave,PatientInformation *PatientInformationArrayToSave);
int ReadGlucose();

#endif 



