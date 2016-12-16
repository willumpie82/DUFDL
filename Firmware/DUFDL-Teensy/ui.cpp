#include "ui.h"
#include "oled.h"
#include "settings.h"


void initUI(){
  if(DEBUG) Serial.println("Ui: initialized");
}


void handleMenuButton(){
  nextFrame();
}

void handleMenuHold(){
  if(BTNDEBUG) Serial.print("HandleMenuButton:");
  if(BTNDEBUG) Serial.println(getFrameNr());
  switch(getFrameNr()){
    case 0: //status screen
      if(setting.useClip()) setting.resetClip();
      else setting.resetShots();
      break;
    case 1: //Mode Setting screen
      break;
    case 2: //Clip Setting screen
      setting.eepromWrite();
      break;
    case 3: //Battery status screen
      break;
    case 4: //Fire status screen
      break;
    default:
      break;
  }
}

void handlePlusButton(){
  if(BTNDEBUG) Serial.print("HandlePlusButton:");
  if(BTNDEBUG) Serial.println(getFrameNr());
  switch(getFrameNr()){
    case 0: //status screen
      setting.increaseSpeed();
      break;
    case 1: //Mode Setting screen
      setting.setNextFireMode();
      break;
    case 2: //Clip Setting screen
      setting.increaseClipSize();
      break;
    case 3: //Battery status screen
      break;
    case 4: //Fire status screen
      break;
    default:
      break;
  }
}

void handleMinusButton(){
  if(BTNDEBUG) Serial.print("HandleMinusButton:");
  if(BTNDEBUG) Serial.println(getFrameNr());
  switch(getFrameNr()){
    case 0: //status screen
      setting.decreaseSpeed();
      break;
    case 1: //Mode Setting screen
      setting.setPrevFireMode();
      break;
    case 2: //Clip Setting screen
      setting.decreaseClipSize();
      break;
    case 3: //Battery status screen
      break;
    case 4: //Fire status screen
      break;
    default:
      break;
  }
}


