#include "main.hpp"
#include <Arduino.h>

static PatientInformation patientInformation = {0,0};
extern int QuantityOfInformationsSaved;
/***************************************************************************
 * Function Name: UpdateEcram
 * Description:  Update Ecram with new values
 * Parameters: Int: glucose, insuline
 * Return: 
***************************************************************************/
void UpdateDisplay(int glycemie, int insuline)
{

}


/***************************************************************************
 * Function Name: InjectInsuline
 * Description:  Inject insuline to the pacient
 * Parameters: amount of insuline to be injected
 * Return: 
***************************************************************************/
void InjectInsuline(int InsulineToBeInjected)
{
  analogWrite(44, InsulineToBeInjected);
}

/***************************************************************************
 * Function Name: SaveInformations
 * Description:  Save Informartions in a vector to be send to the other machine
 * Parameters: Information to be saved
 * Return: addres struct array
***************************************************************************/
void SaveInformations(uint16_t InsulineValueToSave,uint16_t NewGlucoseLevelToSave,PatientInformation *PatientInformationArrayToSave)
{
  patientInformation.InsulineLevel = InsulineValueToSave;
  patientInformation.GlucoseLevel = NewGlucoseLevelToSave;
  PatientInformationArrayToSave[QuantityOfInformationsSaved] = patientInformation;
  if(QuantityOfInformationsSaved > QuantityOfInformationsToSave)
    QuantityOfInformationsSaved = 0; 
  else
    QuantityOfInformationsSaved ++;
}

/***************************************************************************
 * Function Name: UpdateEcram
 * Description:  Update Ecram with new values
 * Parameters: New Values
 * Return: float GlucoseReaded
***************************************************************************/
int ReadGlucose()
{
  return analogRead(GlucosePin);
} 