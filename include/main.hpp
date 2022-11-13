/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  ******************************************************************************
  **/

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
#endif

#ifdef __cplusplus
extern "C" 
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#define InsulinePin 44 
#define GlucosePin A15
#define MealConsumptionPin A14
#define On_OffPin 23
#define ModelIsOnOrOff 42
#define DebugPin 53

#define QuantityOfInformationsToSave 12
#define IntervalTimeToUpdateTheDisplay 1*1005
#define IntervalTimeToUpdateTheEmergencyDisplay 500
#define UpperLimitGlucose 180
#define LowerLimitGlucose 80
#define ConvertVoltsToMealConsumption 450/1023
#define ConvertInsulineLevelToVolts 425
#define GainInMealConsumption 1/900

#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3


#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2


typedef struct {   
    int GlucoseLevel;
    char Separator2;
    int InsulineLevel;
} PatientInformation;
