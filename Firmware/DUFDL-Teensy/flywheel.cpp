#include "flywheel.h"
#include "define.h"
#include "settings.h"
#include <PWMServo.h>  //http://arduiniana.org/libraries/pwmservo/


FlywheelCL flywheels;

void FlywheelCL::init(){
  setPoint = 0;
  ESC.attach(ESC1); //Adds ESC to certain pin. 
  arm();
  delay(1000);
  if(DEBUG) Serial.println("Flywheel: initialized (armed)");
  timer=0;
}

void FlywheelCL::setSpeed(int speed){
  //int angle = map(speed, 0, 100, 0, 180); //Sets servo positions to different speeds 
  ESC.write(speed);
}

int FlywheelCL::getSpeed(){
  return ESC.read();
}

void FlywheelCL::stop(){
  setPoint = SPOOLIDLESPEED;
  if(DEBUG) Serial.println("Flywheel: Motor stop");
}

void FlywheelCL::start(){
  setPoint = map(setting.getSpeed(), 0, 100, SPOOLMINSPEED, 180);
  state = starting;
  setSpeed(SPOOLMINSPEED);
  if(DEBUG) Serial.print("Flywheel: Motor start, Setpoint=");
  if(DEBUG) Serial.println(setPoint);
}

bool FlywheelCL::ready(){
  if((setPoint > getSpeed() && setPoint < getSpeed()+SPOOLSTEP) || (setPoint < getSpeed() && setPoint > getSpeed()-SPOOLSTEP)) {
    state = running;
    return true;
  }
  return false;
}

void FlywheelCL::arm(){
  setSpeed(0); 
}

void FlywheelCL::handle(){
  if((!ready()) && (millis()-timer > SPOOLDELAY) ){
    timer = millis();
    if(setPoint > getSpeed()){
      setSpeed(getSpeed() + SPOOLSTEP);
      state = starting;
      if(DEBUG) Serial.print("Flywheel: starting, speed:");
      if(DEBUG) Serial.println(getSpeed());
    }
    if(setPoint < getSpeed()){
      setSpeed(getSpeed() - SPOOLSTEP);
      state = stopping;
      if(DEBUG) Serial.print("Flywheel: stopping, speed:");
      if(DEBUG) Serial.println(getSpeed());
    }
  }
  if(setPoint < SPOOLSTEP) state = stopped;
}

void FlywheelCL::kill(){
  setSpeed(0);
  setPoint = 0;
  if(DEBUG && state != stopped) Serial.println("Flywheel: Motor killed");
  state = stopped;
  
}

