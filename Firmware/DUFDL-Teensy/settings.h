#ifndef SETTINGSh
#define SETTINGSh

#include "define.h"
#include "flywheel.h"
#include <arduino.h>

struct DUFDLData{
  unsigned char ID[6] = "DUFDL";
  unsigned int length;
  int nrShots;
  FireMode fireMode;
  int clipSize;
  int dartsLeft;
  int fireSpeed; 
};

class Settings{

  int state;
  String stateText;
  bool triggerActive = false;
  int shotCount;
  DUFDLData data;

//eeprom  
  bool eepromValid();
  void eepromRead();


public:
  //constructor
  Settings(int shots, int firespeed, FireMode modus, int clipsize);
  void init();
  void eepromWrite();

  //shots functions
  bool dartReady();
  void shotFired();
  bool shotReady();
  void shotReset();
  int getShots();
  void resetShots();

  //speed functions
  int getSpeed();
  void setSpeed(int value);
  void increaseSpeed();
  void decreaseSpeed();

  //clip functions
  int getClipSize();
  void setClipSize(int value);
  int getDartsLeft();
  void resetClip();
  bool useClip();
  void increaseClipSize();
  void decreaseClipSize();

  //modus functions
  FireMode getFireMode();
  void setFireMode(FireMode value);
  void setNextFireMode();
  void setPrevFireMode();

  //trigger functions
  void setTrigger(bool state);
  bool getTrigger();
  
  
};

extern Settings setting;


#endif
