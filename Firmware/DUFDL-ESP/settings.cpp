#include "settings.h"
#include "define.h"
#include <arduino.h>

Settings setting(0, 80, Single, 12);

Settings::Settings(int shots, int firespeed, fireMode modus, int clipsize){
  nrShots = shots;
  fireSpeed = firespeed;
  FireMode = modus;
  clipSize = clipsize;
  resetClip();
}

//shots functions
bool Settings::dartReady(){
  if(clipSize > 0){
     if(dartsLeft > 0) return true;
     else return false;
  } else {
    return true;
  }
}

void Settings::shotFired(){
  if(clipSize > 0 && dartsLeft > 0){
    dartsLeft--;
  }
  nrShots++;
}

int Settings::getShots(){
  return nrShots;
}

void Settings::resetShots(){
  if(DEBUG) Serial.println("Settings: reset shots");
  nrShots=0;
}

//speed functions
int Settings::getSpeed(){
  return fireSpeed;
}

void Settings::setSpeed(int value){
  if(DEBUG) Serial.print("Settings: set speed to: ");
  if(DEBUG) Serial.println(value);
  fireSpeed = value;
}

void Settings::increaseSpeed(){
  if(DEBUG) Serial.print("Settings: increase speed by: ");
  if(DEBUG) Serial.println(SPOOLSTEP);
  if(fireSpeed < 100) fireSpeed += SPOOLSETSTEP;
}

void Settings::decreaseSpeed(){
  if(DEBUG) Serial.print("Settings: decrease speed by: ");
  if(DEBUG) Serial.println(SPOOLSTEP);
  if(fireSpeed > 0) fireSpeed -= SPOOLSETSTEP;
}


//clip functions
int Settings::getClipSize(){
  return clipSize;
}

void Settings::setClipSize(int value){
  if(DEBUG) Serial.print("Settings: set clipsize to: ");
  if(DEBUG) Serial.println(value);
  clipSize = value;
  resetClip();
}

int Settings::getDartsLeft(){
  return dartsLeft;
}

void Settings::resetClip(){
  if(DEBUG) Serial.print("Settings: reset clipsize to: ");
  if(DEBUG) Serial.println(clipSize);
  dartsLeft = clipSize;
}

bool Settings::useClip(){
  if(clipSize > 0) return true;
  else return false;
}

void Settings::increaseClipSize(){
  if(DEBUG) Serial.println("Settings: increase clipsize by 1");
  if(clipSize < 30) clipSize++;
}

void Settings::decreaseClipSize(){
  if(DEBUG) Serial.println("Settings: decrease clipsize by 1");
  if(clipSize > 0) clipSize--;
}

//modus functions
fireMode Settings::getFireMode(){
  return FireMode;
}

void Settings::setFireMode(fireMode value){
  if(DEBUG) Serial.print("Settings: set firemode to: ");
  if(DEBUG) Serial.println(value);
  FireMode = value;
}

void Settings::setNextFireMode(){
  if(DEBUG) Serial.println("Settings: set next firemode");
  if(FireMode < 3) FireMode=fireMode(FireMode+1);

}

void Settings::setPrevFireMode(){
  if(DEBUG) Serial.println("Settings: set previous firemode");
  if(FireMode > 0 ) FireMode=fireMode(FireMode-1);

}

void Settings::setTrigger(bool state){
  triggerActive = state;
}

bool Settings::getTrigger(){
  return triggerActive;
}


