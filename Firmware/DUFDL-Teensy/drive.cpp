#include "drive.h"
#include "define.h"
#include <AccelStepper.h>

AccelStepper stepper(1, DRIVE_STP, DRIVE_DIR);

void initDrive(){
  pinMode(DRIVE_SLP, OUTPUT);
  digitalWrite(DRIVE_SLP,LOW); //disable drive
  stepper.setMaxSpeed(DRIVESPEED);
  stepper.setAcceleration(DRIVEACCEL);
}

void moveDart(){
  enableDrive();
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(DRIVESPEED);
  stepper.moveTo(DRIVELENGTH);
  stepper.runToPosition();
  disableDrive();
}

void resetDrive(int setpoint){
  
  if(DEBUG) Serial.println(setpoint);
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(DRIVESPEED);
  stepper.moveTo(setpoint);
  
}

int getDistanceToGo(){
  return stepper.distanceToGo();
}

void enableDrive(){
  digitalWrite(DRIVE_SLP,HIGH);
}

void disableDrive(){
  digitalWrite(DRIVE_SLP,LOW);
}

