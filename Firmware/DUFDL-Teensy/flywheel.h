#ifndef FLYWHEELh
#define FLYWHEELh
#include <Servo.h>
#include "define.h"



class FlywheelCL{
  Servo ESC;
  int setPoint;
  unsigned long timer;
  void arm();
  void setSpeed(int value);
  flywheelState state;
  int getSpeed();
  
public:
  FlywheelCL(){}
  int getFireSpeed();
  
  bool ready();
  void stop();
  void start();
  void handle();
  void init();
  void kill();
  
};


extern FlywheelCL flywheels;


#endif
