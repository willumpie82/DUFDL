#include "settings.h"
#include "define.h"
#include <arduino.h>
#include <EEPROM.h> 

Settings setting(0, SPOOLINITSPEED, Single, 12);

void Settings::init(){
  if(DEBUG) Serial.println("Eeprom init");
  if(!eepromValid()) eepromWrite();
  eepromRead();
  if(DEBUG) Serial.println("Eeprom init: done");
}

void Settings::eepromRead(){
  if(!eepromValid()) return;
  data.length = EEPROM.read(sizeof(data.ID)+2);
  char* dataPtr = (char*)&data;
  unsigned int i;
  for (i = 0; i < data.length; i++){
    *dataPtr++ = EEPROM.read(i);
  }

 if(DEBUG) Serial.println(" [end] check:");
 if(DEBUG) Serial.println((char*)data.ID);
 if(DEBUG) Serial.println(data.length);
 if(DEBUG) Serial.println(data.nrShots);
 if(DEBUG) Serial.println(data.fireMode);
 if(DEBUG) Serial.println(data.clipSize);
 if(DEBUG) Serial.println(data.dartsLeft);
 if(DEBUG) Serial.println(data.fireSpeed);

//   unsigned char ID[6] = "DUFDL";
//  unsigned int length;
//  int nrShots;
//  FireMode fireMode;
//  int clipSize;
//  int dartsLeft;
//  int fireSpeed; 
 
 //read from eeprom
}

void Settings::eepromWrite(){
  //write to eeprom
  data.length = sizeof(DUFDLData);
  char* dataPtr = (char*)&data;
  unsigned int i;
  for (i = 0; i < data.length; i++){
    EEPROM.update(i,*dataPtr++);
  }
  if(DEBUG) Serial.print("Eeprom bytes writen=");
  if(DEBUG) Serial.println(i);
}

bool Settings::eepromValid(){
  //check if eeprom valid 
  unsigned char val=0;
  for (unsigned int i = 0; i < sizeof(data.ID); i++){
    val = EEPROM.read(i);
    if(val != data.ID[i]){
      if(DEBUG) Serial.print("EEPROM DATA ERROR read=");
      if(DEBUG) Serial.print(val);
      if(DEBUG) Serial.print(" i=");
      if(DEBUG) Serial.println(i);
      return false;
    }
  }
  if (EEPROM.read(sizeof(data.ID)+2) != sizeof(DUFDLData)){
      if(DEBUG) Serial.print("EEPROM DATA ERROR size=");
      if(DEBUG) Serial.print(EEPROM.read(sizeof(data.ID)+2));
      if(DEBUG) Serial.print("; expected=");
      if(DEBUG) Serial.println(sizeof(DUFDLData));
      return false;
  }
  return true;
}


Settings::Settings(int shots, int firespeed, FireMode modus, int clipsize){
  //set default data
  data.nrShots    = shots;
  data.fireSpeed  = firespeed;
  data.fireMode   = modus;
  data.clipSize   = clipsize;
  data.dartsLeft  = clipsize;
}

//shots functions
bool Settings::dartReady(){
  if(data.clipSize > 0){
     if(data.dartsLeft > 0) return true;
     else return false;
  } else {
    return true;
  }
}

bool Settings::shotReady(){
  if (shotCount < data.fireMode || data.fireMode == FireMode(Auto)) return true;
  return false;
}

void Settings::shotReset(){
  shotCount = 0;
  if(DEBUG) Serial.println("Settings: shots cycle reset");
}

void Settings::shotFired(){
  if(data.clipSize > 0 && data.dartsLeft > 0){
    data.dartsLeft--;
  }
  data.nrShots++;
  shotCount++;
  if(DEBUG) Serial.println("Settings: shots fired");
}

int Settings::getShots(){
  return data.nrShots;
}

void Settings::resetShots(){
  if(DEBUG) Serial.println("Settings: reset shots");
  data.nrShots=0;
}

//speed functions
int Settings::getSpeed(){
  return data.fireSpeed;
}

void Settings::setSpeed(int value){
  if(DEBUG) Serial.print("Settings: set speed to: ");
  if(DEBUG) Serial.println(value);
  data.fireSpeed = value;
}

void Settings::increaseSpeed(){
  if(DEBUG) Serial.print("Settings: increase speed by: ");
  if(DEBUG) Serial.println(SPOOLSETSTEP);
  if(data.fireSpeed < 100) data.fireSpeed += SPOOLSETSTEP;
}

void Settings::decreaseSpeed(){
  if(DEBUG) Serial.print("Settings: decrease speed by: ");
  if(DEBUG) Serial.println(SPOOLSETSTEP);
  if(data.fireSpeed > 0) data.fireSpeed -= SPOOLSETSTEP;
}


//clip functions
int Settings::getClipSize(){
  return data.clipSize;
}

void Settings::setClipSize(int value){
  if(DEBUG) Serial.print("Settings: set clipsize to: ");
  if(DEBUG) Serial.println(value);
  data.clipSize = value;
  resetClip();
}

int Settings::getDartsLeft(){
  return data.dartsLeft;
}

void Settings::resetClip(){
  if(DEBUG) Serial.print("Settings: reset clipsize to: ");
  if(DEBUG) Serial.println(data.clipSize);
  data.dartsLeft = data.clipSize;
}

bool Settings::useClip(){
  if(data.clipSize > 0) return true;
  else return false;
}

void Settings::increaseClipSize(){
  if(DEBUG) Serial.println("Settings: increase clipsize by 1");
  if(data.clipSize < SETTING_MAXCLIP) data.clipSize++;
}

void Settings::decreaseClipSize(){
  if(DEBUG) Serial.println("Settings: decrease clipsize by 1");
  if(data.clipSize > 0) data.clipSize--;
}

//modus functions
FireMode Settings::getFireMode(){
  return data.fireMode;
}

void Settings::setFireMode(FireMode value){
  if(DEBUG) Serial.print("Settings: set firemode to: ");
  if(DEBUG) Serial.println(value);
  data.fireMode = value;
}

void Settings::setNextFireMode(){
  if(DEBUG) Serial.println("Settings: set next firemode");
  if(data.fireMode < SETTING_MAXFIREMODE) data.fireMode=FireMode(data.fireMode+1);

}

void Settings::setPrevFireMode(){
  if(DEBUG) Serial.println("Settings: set previous firemode");
  if(data.fireMode > SETTING_MINFIREMODE ) data.fireMode=FireMode(data.fireMode-1);

}

void Settings::setTrigger(bool state){
  triggerActive = state;
}

bool Settings::getTrigger(){
  return !digitalRead(KEYTRIGGER);
}


