#include "define.h"
#include "oled.h"     //https://github.com/squix78/esp8266-oled-ssd1306
#include "buttons.h"  //https://github.com/david1983/eBtn
#include "ui.h"
#include "flywheel.h"
//#include "drive.h"
#include "state.h"



//hardware ESP12E http://learn.acrobotic.com/uploads/esp8266_esp12e_pinout.png

void setup(){  
  
  if(DEBUG) Serial.begin(115200);
  if(DEBUG) Serial.println();
  ESP.wdtDisable();
  if(DEBUG) Serial.println("Init: WDT disabled");
  if(DEBUG) Serial.println("init: peripherals, start");
  initOLED();
  initButtons();
  initUI();
  flywheels.init();
  //StepperSetup();
  if(DEBUG) Serial.println("init: peripherals, done");
  ESP.wdtEnable(WDTO_8S);
  if(DEBUG) Serial.println("Init: WDT enabled");
}


void loop()
{
 //dartLoop();
 pictureLoop();
 flywheels.handle();
 getButtons();
 
 
}


