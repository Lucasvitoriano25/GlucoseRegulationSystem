#include <SPI.h>
#include <TFTv2.h>
#include <SeeedTouchScreen.h>
#include <stdint.h>

TouchScreen ts = TouchScreen(XP, YP, XM, YM);
TFT screen = TFT();
extern int selecteurPage;
//variable de sélection de menu pour l'interface tactile
extern boolean comptAff; //background affiché
extern boolean alerte;

int LastGlucoseLevel = 0;
extern float NewGlucoseLevel;
  

void setupDisplay() 
{
  TFT_BL_ON;      // turn on the background light
  Tft.TFTinit();  // init TFT library

  Tft.fillScreen(0, 240, 0, 320, BLUE);
  Tft.drawString("Hello", 10, 100, 10, WHITE, LANDSCAPE);
  Tft.drawString("Diabete", 10, 10, 6, WHITE, LANDSCAPE);
}

/***************************************************************************
 * Function Name: TestTouche
 * Description:  See if the Display is touched 
 * Parameters: 
 * Return: 
***************************************************************************/
int TestTouche()
{
      Point p = ts.getPoint();
      if (p.z > __PRESSURE)
       {return 1;}
      else
       { return 0;}
  return 0;
}

/***************************************************************************
 * Function Name: MenuInsuline
 * Description:  Show the Glucose level 
 * Parameters: 
 * Return: 
***************************************************************************/

void MenuGlycemie()
{
  switch (comptAff){
    case 0 :
      Tft.fillScreen(0, 240, 0, 320, BLUE);
      Tft.drawString("Glycemie", 40, 10, 5, WHITE, LANDSCAPE);
      Tft.drawTriangle(180,130,200,130,190,140,WHITE);
      Tft.drawNumber(NewGlucoseLevel, 80, 130, 5, WHITE);
      comptAff = true;
      break;
    case 1 :
      //Affichage du sens d'évolution
      if (abs(NewGlucoseLevel-LastGlucoseLevel)>2){
        Tft.fillRectangle(80, 120, 95, 60, BLUE);
        Tft.drawNumber(NewGlucoseLevel, 80, 130, 5, WHITE);
        if (LastGlucoseLevel<NewGlucoseLevel){
          Tft.fillRectangle(180, 130, 20, 10, BLUE);
          Tft.drawTriangle(180,140,200,140,190,130,WHITE);
          }
        else {
          Tft.fillRectangle(180, 130, 20, 10, BLUE);
          Tft.drawTriangle(180,130,200,130,190,140,WHITE);
          }
        LastGlucoseLevel = NewGlucoseLevel;
        }
      //Changement de page
      if (TestTouche()== true ){
        selecteurPage=2;
        comptAff = false;
        return;
      }
      break;
    }
  return;
} 

/***************************************************************************
 * Function Name: MenuInsuline
 * Description:  Show the insuline level 
 * Parameters: 
 * Return: 
***************************************************************************/

void MenuInsuline()
{
  switch (comptAff){
    case 0 :
      Tft.fillScreen(0, 240, 0, 320, GREEN);
      Tft.drawString("Insuline", 40, 10, 5, BLACK, LANDSCAPE);
      comptAff = true;
      break;
    case 1 :
      if (TestTouche()== true ){
        selecteurPage=1;
        comptAff = false;
        return;
      }
      break;
    }
}

/***************************************************************************
 * Function Name: MenuAlert
 * Description: Draw the display if tha glucose level is dangerous 
 * Parameters: 
 * Return: 
***************************************************************************/

void MenuAlert()
{
  switch (comptAff){
    case 0 :
        Tft.fillScreen(0, 240, 0, 320, RED);
        Tft.drawTriangle(120, 20, 70, 80, 170, 80, WHITE);
        Tft.drawString("ALERTE", 30, 100, 5, WHITE);
        Tft.drawString("!", 108, 40, 5, WHITE);
        Tft.drawString("mg/dL", 50, 190, 5, WHITE);
        Tft.drawNumber(NewGlucoseLevel, 70, 150, 5, WHITE);
        comptAff = true;
      break;
    case 1 :
        if (abs(NewGlucoseLevel-LastGlucoseLevel)>2){
            Tft.fillRectangle(70, 150, 95, 40, RED);
            Tft.drawNumber(NewGlucoseLevel, 70, 150, 5, WHITE);
            LastGlucoseLevel = NewGlucoseLevel;
            }
        if (NewGlucoseLevel<2) {
            Tft.drawString("Capteur", 20, 240, 5, BLACK);
        }
        else{
            Tft.fillRectangle(20, 240, 210,40, RED);
        }
        if (!alerte){
            selecteurPage=1;
            comptAff = false;
            return;
        }
        
        break;
    }       
}