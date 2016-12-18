#ifndef FLYWHEELh
#define FLYWHEELh
#include <Servo.h>

class FlywheelCL{
  Servo ESC;
  int setPoint;
  unsigned long timer;
  void arm();
  void setSpeed(int value);
  
public:
  FlywheelCL(){}
  int getSpeed();
  void stop();
  void start();
  void handle();
  void init();
  void kill();
  
};


extern FlywheelCL flywheels;


#endif
