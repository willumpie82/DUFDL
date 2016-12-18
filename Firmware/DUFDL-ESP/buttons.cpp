#include "buttons.h"
#include "define.h"
#include "oled.h"
#include "ui.h"
#include "settings.h"
#include <eBtn.h> //https://github.com/david1983/eBtn/blob/master/src/eBtn.cpp
#include <PCF8574.h>

PCF8574 PCF_button(0x3F);

void getButtons(){
  if(!PCF_button.read(PCF_MENU)){
     Serial.println("PCF - Menu pressed");
  }
}

void btnIsr(){
  Serial.print("PCF - interrupt value=");
  Serial.println(PCF_button.read8());
}

//eBtn btnMenu = eBtn(KEY_MENU);
//eBtn btnPlus = eBtn(KEY_PLUS);
//eBtn btnMinus = eBtn(KEY_MINUS);
//eBtn btnTrigger = eBtn(KEY_TRIGGER);
//
//
////##############################
////#      Menu button calls     #
////##############################
//void btnMenuPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Menu pressed");
//}
//
//void btnMenuHold(){
//  if(BTNDEBUG) Serial.println("Buttons: Menu Hold");
//}
//
//void btnMenuRelease(){
//  if(BTNDEBUG) Serial.println("Buttons: Menu Released");
//  handleMenuButton();
//}
//
//void btnMenuLongPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Menu LongPressed");
//  handleMenuHold();
//  
//}
//
//void btnMenuIsr(){
//  btnMenu.handle();
//}
//
//void btnMenuInit(){
//  btnMenu.on("press",   btnMenuPress);
//  btnMenu.on("hold",    btnMenuHold);
//  btnMenu.on("release", btnMenuRelease);
//  btnMenu.on("long",    btnMenuLongPress);
//  attachInterrupt(KEY_MENU, btnMenuIsr, CHANGE);
//  if(BTNDEBUG) Serial.println("Buttons: Menu initilized");
//}
//
//
//
////##############################
////#      Plus button calls     #
////##############################
//void btnPlusPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Plus pressed");
//}
//
//void btnPlusHold(){
//   if(BTNDEBUG) Serial.println("Buttons: Plus Hold");
//}
//
//void btnPlusRelease(){
//  if(BTNDEBUG) Serial.println("Buttons: Plus Released");
//  handlePlusButton();
//}
//
//void btnPlusLongPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Plus LongPressed");
//  setting.shotFired();
//}
//
//void btnPlusIsr(){
//  btnPlus.handle();
//}
//
//void btnPlusInit(){
//  btnPlus.on("press",   btnPlusPress);
//  btnPlus.on("hold",    btnPlusHold);
//  btnPlus.on("release", btnPlusRelease);
//  btnPlus.on("long",    btnPlusLongPress);
//  attachInterrupt(KEY_PLUS, btnPlusIsr, CHANGE);
//  if(BTNDEBUG) Serial.println("Buttons: Plus initilized");
//}
//
//
////##############################
////#      Minus button calls     #
////##############################
//void btnMinusPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Minus pressed");
//}
//
//void btnMinusHold(){
//  if(BTNDEBUG) Serial.println("Buttons: Minus Hold");
//}
//
//void btnMinusRelease(){
//  if(BTNDEBUG) Serial.println("Buttons: Minus Released");
//  handleMinusButton();
//}
//
//void btnMinusLongPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Minus LongPressed");
//}
//
//void btnMinusIsr(){
//  btnMinus.handle();
//}
//
//void btnMinusInit(){
//  btnMinus.on("press",   btnMinusPress);
//  btnMinus.on("hold",    btnMinusHold);
//  btnMinus.on("release", btnMinusRelease);
//  btnMinus.on("long",    btnMinusLongPress);
////  attachInterrupt(KEY_MINUS, btnMinusIsr, CHANGE);
//  if(BTNDEBUG) Serial.println("Buttons: Minus initilized");
//}
//
//
////##############################
////#    Trigger button calls    #
////##############################
//void btnTriggerPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Trigger pressed");
//}
//
//void btnTriggerHold(){
//   if(BTNDEBUG) Serial.println("Buttons: Trigger Hold");
//   setting.setTrigger(true);
//}
//
//void btnTriggerRelease(){
//  if(BTNDEBUG) Serial.println("Buttons: Trigger Released");
//  setting.setTrigger(false);
//}
//
//void btnTriggerLongPress(){
//  if(BTNDEBUG) Serial.println("Buttons: Trigger LongPressed");
//}
//
//void btnTriggerIsr(){
//  btnTrigger.handle();
//}
//
//void btnTriggerInit(){
//  btnTrigger.on("press",   btnTriggerPress);
//  btnTrigger.on("hold",    btnTriggerHold);
//  btnTrigger.on("release", btnTriggerRelease);
//  btnTrigger.on("long",    btnTriggerLongPress);
//  attachInterrupt(KEY_TRIGGER, btnTriggerIsr, CHANGE);
//  if(BTNDEBUG) Serial.println("Buttons: Trigger initilized");
//}


void initButtons(){

//btnMenuInit();
//btnPlusInit();
//btnMinusInit();
//btnTriggerInit();
delay(100);
attachInterrupt(PCF_INT, btnIsr, CHANGE);

if(DEBUG) Serial.println("Buttons: initilized");
}



