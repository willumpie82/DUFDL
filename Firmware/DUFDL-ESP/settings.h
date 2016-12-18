#ifndef SETTINGSh
#define SETTINGSh

#include "define.h"
#include "flywheel.h"
#include <arduino.h>


class Settings{
  int nrShots;
  fireMode FireMode;
  int clipSize;
  int dartsLeft;
  int fireSpeed;
  int state;
  String stateText;
  bool triggerActive = false;

public:
  //constructor
  Settings(int shots, int firespeed, fireMode modus, int clipsize);

  //shots functions
  bool dartReady();
  void shotFired();
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
  fireMode getFireMode();
  void setFireMode(fireMode value);
  void setNextFireMode();
  void setPrevFireMode();

  //trigger functions
  void setTrigger(bool state);
  bool getTrigger();
  
  
};

extern Settings setting;


#endif
