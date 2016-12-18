#include "flywheel.h"
#include "define.h"
#include "settings.h"
#include <Servo.h>  //for ESC


FlywheelCL flywheels;

void FlywheelCL::init(){
  ESC.attach(ESC1); //Adds ESC to certain pin. 
  arm();
  delay(1000);
  if(DEBUG) Serial.println("Flywheel: initialized (armed)");
  timer=0;
}

void FlywheelCL::setSpeed(int speed){
  int angle = map(speed, 0, 100, 0, 180); //Sets servo positions to different speeds 
  ESC.write(angle);
}

int FlywheelCL::getSpeed(){
  return ESC.read();
}

void FlywheelCL::stop(){
  setPoint = SPOOLIDLESPEED;
  if(DEBUG) Serial.println("Flywheel: Motor start");
}

void FlywheelCL::start(){
  setPoint = setting.getSpeed();
  if(DEBUG) Serial.println("Flywheel: Motor start");
}

void FlywheelCL::arm(){
  setSpeed(0); //Sets speed variable delay(1000);
}

void FlywheelCL::handle(){
  if( (setPoint != 00) && (timer < micros()) ){
    timer = micros();
    if(setPoint < getSpeed()){
      setSpeed(getSpeed() + SPOOLSTEP);
    }
    if(setPoint > getSpeed()){
      setSpeed(getSpeed() - SPOOLSTEP);
    }  
  }
}

void FlywheelCL::kill(){
  setSpeed(0);
  setPoint = 0;
  if(DEBUG) Serial.println("Flywheel: Motor killed");
}

