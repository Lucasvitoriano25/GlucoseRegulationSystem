#include <Arduino.h>
#include "main.hpp"
#include "GlucoseControler.hpp"
#include <stdint.h>
#include "Display.hpp"

void SendBluetoothMessage(PatientInformation PatientToSendInformation);
float CommandeInsuline();

float P = 10; 
float I = 2; 
float D = 20; 
float N = 10; 
float T = 0.016;
float basal = 0.031;
float Glycbasal = 110;
int tension;
float insuline0 = 0.0; 
float insuline1 = 0.0; 
float insuline2 = 0.0;
float NewGlucoseLevel = 0;
float comm0 = 0; 
float comm1 = 0; 
float comm2 = 0; 

float InsulineToBeInjected = 0;
static float meal = 0;

static long InitialTimeDisplayUpdate = 0;
static long InitialTimeDisplayEmergencyUpdate = 0;

static PatientInformation patientInformation =  {25,';',20};

unsigned int selecteurPage=0;
boolean alerte = false;
boolean comptAff = false; //background affiché

float aux = 0;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(1000);
  Serial1.flush(); 

  setupDisplay();

  pinMode(ModelIsOnOrOff,INPUT);
  pinMode(GlucosePin,INPUT);
  pinMode(MealConsumptionPin, INPUT);
  pinMode(InsulinePin,OUTPUT);
  pinMode(30,OUTPUT);

  pinMode(DebugPin, OUTPUT);  // set the debug pin as a output
  digitalWrite(DebugPin,LOW);
}

void loop()
{
  digitalWrite(DebugPin,HIGH);
  aux = analogRead(GlucosePin);
  if(aux > 10){
    NewGlucoseLevel = map(aux,0,1023,0,500);
  }
  meal = analogRead(MealConsumptionPin);
  if (digitalRead(ModelIsOnOrOff)==LOW) {
    InsulineToBeInjected = (CommandeInsuline() + meal*ConvertVoltsToMealConsumption*GainInMealConsumption) * ConvertInsulineLevelToVolts;
    analogWrite(InsulinePin,InsulineToBeInjected);
  }

  alerte = (NewGlucoseLevel>UpperLimitGlucose ||  NewGlucoseLevel<LowerLimitGlucose);
  if((millis() - InitialTimeDisplayEmergencyUpdate) > IntervalTimeToUpdateTheEmergencyDisplay){
    InitialTimeDisplayEmergencyUpdate = millis();
    if (alerte && selecteurPage!=3 && digitalRead(ModelIsOnOrOff) == LOW){
      selecteurPage=3;
      comptAff=false;
      Serial.print("alerte");
    }
  }
  if((millis() - InitialTimeDisplayUpdate) > IntervalTimeToUpdateTheDisplay){
    InitialTimeDisplayUpdate = millis();
  switch(selecteurPage){
    case 1:
      MenuGlycemie() ;
      break;
    case 2:
      MenuInsuline() ;
      break;
    case 3:
     MenuAlert();
      break;
    default :
      MenuGlycemie();
      break;
    }
  }
 
  patientInformation.GlucoseLevel = NewGlucoseLevel;
  patientInformation.InsulineLevel = InsulineToBeInjected;
  SendBluetoothMessage(patientInformation);
  digitalWrite(DebugPin,LOW); 
  delay(11);
}

/***************************************************************************
 * Function Name: SendBluetoothMessage
 * Description:  Send to The laptop the patient informations
 * Parameters: Pacient to be sent
 * Return: 
***************************************************************************/

void SendBluetoothMessage(PatientInformation PatientToSendInformation)
{
  Serial1.print(PatientToSendInformation.InsulineLevel);
  Serial1.print(PatientToSendInformation.Separator2);
  Serial1.println(PatientToSendInformation.GlucoseLevel);
}

/***************************************************************************
 * Function Name: CommandeInsuline
 * Description:  Calculate the amount of insuline needed
 * Parameters: 
 * Return: 
***************************************************************************/

float CommandeInsuline(){
  comm2 = comm1;
  comm1 = comm0;
  comm0 = (float(NewGlucoseLevel)-Glycbasal)/10000;
  insuline2 = insuline1;
  insuline1 = insuline0;
  insuline0 =  (2-N*T)*insuline1 + (N*T-1)*insuline2+(P+D*N)*comm0+(P*(N*T-2)+I*T-2*D*N)*comm1+(P*(1-N*T)+I*T*(N*T-1)+D*N)*comm2;
  return(max(insuline0 + basal,0));
  };