#include "buttons.h"
#include "define.h"
#include "oled.h"
#include "ui.h"
#include "settings.h"
#include <eBtn.h> //https://github.com/david1983/eBtn/blob/master/src/eBtn.cpp ==> copied into button code

eBtn btnMenu = eBtn(KEYMENU);
eBtn btnPlus = eBtn(KEYPLUS);
eBtn btnMinus = eBtn(KEYMINUS);
eBtn btnTrigger = eBtn(KEYTRIGGER);


//##############################
//#      Menu button calls     #
//##############################
void btnMenuPress(){
  if(BTNDEBUG) Serial.println("Buttons: Menu pressed");
}

void btnMenuHold(){
  if(BTNDEBUG) Serial.println("Buttons: Menu Hold");
}

void btnMenuRelease(){
  if(BTNDEBUG) Serial.println("Buttons: Menu Released");
  handleMenuButton();
}

void btnMenuLongPress(){
  if(BTNDEBUG) Serial.println("Buttons: Menu LongPressed");
  handleMenuHold();
  
}

void btnMenuIsr(){
  cli();
  btnMenu.handle();
  sei();
}

void btnMenuInit(){
  btnMenu.on("press",   btnMenuPress);
  btnMenu.on("hold",    btnMenuHold);
  btnMenu.on("release", btnMenuRelease);
  btnMenu.on("long",    btnMenuLongPress);
  attachInterrupt(KEYMENU, btnMenuIsr, CHANGE);
  if(BTNDEBUG) Serial.println("Buttons: Menu initilized");
}



//##############################
//#      Plus button calls     #
//##############################
void btnPlusPress(){
  if(BTNDEBUG) Serial.println("Buttons: Plus pressed");
}

void btnPlusHold(){
   if(BTNDEBUG) Serial.println("Buttons: Plus Hold");
}

void btnPlusRelease(){
  if(BTNDEBUG) Serial.println("Buttons: Plus Released");
  handlePlusButton();
}

void btnPlusLongPress(){
  if(BTNDEBUG) Serial.println("Buttons: Plus LongPressed");
  //setting.shotFired();
}

void btnPlusIsr(){
  cli();
  btnPlus.handle();
  sei();
}

void btnPlusInit(){
  btnPlus.on("press",   btnPlusPress);
  btnPlus.on("hold",    btnPlusHold);
  btnPlus.on("release", btnPlusRelease);
  btnPlus.on("long",    btnPlusLongPress);
  pinMode(KEYPLUS, INPUT_PULLUP);
  attachInterrupt(KEYPLUS, btnPlusIsr, CHANGE);
  if(BTNDEBUG) Serial.println("Buttons: Plus initilized");
}


//##############################
//#      Minus button calls     #
//##############################
void btnMinusPress(){
  if(BTNDEBUG) Serial.println("Buttons: Minus pressed");
}

void btnMinusHold(){
  if(BTNDEBUG) Serial.println("Buttons: Minus Hold");
}

void btnMinusRelease(){
  if(BTNDEBUG) Serial.println("Buttons: Minus Released");
  handleMinusButton();
}

void btnMinusLongPress(){
  if(BTNDEBUG) Serial.println("Buttons: Minus LongPressed");
}

void btnMinusIsr(){
  cli();
  btnMinus.handle();
  sei();
}

void btnMinusInit(){
  btnMinus.on("press",   btnMinusPress);
  btnMinus.on("hold",    btnMinusHold);
  btnMinus.on("release", btnMinusRelease);
  btnMinus.on("long",    btnMinusLongPress);
  attachInterrupt(KEYMINUS, btnMinusIsr, CHANGE);
  if(BTNDEBUG) Serial.println("Buttons: Minus initilized");
}


//##############################
//#    Trigger button calls    #
//##############################
void btnTriggerPress(){
  if(BTNDEBUG) Serial.println("Buttons: Trigger pressed");
}

void btnTriggerHold(){
   if(BTNDEBUG) Serial.println("Buttons: Trigger Hold");
   //setting.setTrigger(true);
}

void btnTriggerRelease(){
  if(BTNDEBUG) Serial.println("Buttons: Trigger Released");
  //setting.setTrigger(false);
}

void btnTriggerLongPress(){
  if(BTNDEBUG) Serial.println("Buttons: Trigger LongPressed");
}

void btnTriggerIsr(){
  cli();
  btnTrigger.handle();
  sei();
}

void btnTriggerInit(){
  btnTrigger.on("press",   btnTriggerPress);
  btnTrigger.on("hold",    btnTriggerHold);
  btnTrigger.on("release", btnTriggerRelease);
  btnTrigger.on("long",    btnTriggerLongPress);
  attachInterrupt(KEYTRIGGER, btnTriggerIsr, CHANGE);
  if(BTNDEBUG) Serial.println("Buttons: Trigger initilized");
}


void initButtons(){

btnMenuInit();
btnPlusInit();
btnMinusInit();
btnTriggerInit();
delay(100);
if(DEBUG) Serial.println("Buttons: initilized");
}




