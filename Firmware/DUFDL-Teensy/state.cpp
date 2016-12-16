#include "state.h"
#include "define.h"
#include "settings.h"
#include "drive.h"
#include "oled.h"

int dartState;
int prevState;
bool newstate = true;
int dartCount=0;
unsigned long stateTimer=0;


String stateText[NR_OF_STATES] { 
  "Idle", 
  "Armed", 
  "Triggered", 
  "init Spool", 
  "Spool UP",
  "Init Drive",
  "Move Dart",
  "Spool Down",
  "Stopped",
  "CoolDown",
  "Kill"
};


void setNextState(int state){
  prevState = dartState;
  dartState = state;
  newstate = true;
}

bool newState(){
  if(newstate == true){
    newstate = false;
    stateTimer = millis();
    if(DEBUG) Serial.print("StateMachine: newstate: ");
    if(DEBUG) Serial.println(stateText[dartState]);
    return true;
  }
  return false;
}

void dartLoop(){//dartloop statemachine
  
  switch(dartState){
    case STATE_IDLE:
      handleStateIdle(STATE_ARMED);
      break;
    case STATE_ARMED:
      handleStateArmed(STATE_TRIGGERED);
      break;
    case STATE_TRIGGERED:
      handleStateTriggered(STATE_INITSPOOL);
      break;
    case STATE_INITSPOOL:
      handleStateInitSpool(STATE_SPOOLUP);
      break;
    case STATE_SPOOLUP:
      handleStateSpoolUp(STATE_INITDRIVE);
      break;
    case STATE_INITDRIVE:
      handleStateInitDrive(STATE_MOVEDART);
      break;   
    case STATE_MOVEDART:
      handleStateMoveDart(STATE_SPOOLDOWN);
      break;   
    case STATE_SPOOLDOWN:
      handleStateSpoolDown(STATE_STOPPED);
      break; 
    case STATE_STOPPED:
      handleStateStopped(STATE_COOLDOWN);
      break;
    case STATE_COOLDOWN:
      handleStateCoolDown(STATE_IDLE);
      break;
    case STATE_KILL:
      handleStateKill(STATE_IDLE);
      break;
    default:
      break;
  } //switch
}

void handleStateIdle(int next){
  newState();
  if (!setting.getTrigger()) setNextState(next);
  dartCount = 0;
  flywheels.kill();
}

void handleStateArmed(int next){
  newState();
  //if (!setting.getTrigger() && millis()-stateTimer > DELAY_IDLE_STATE) setNextState(STATE_IDLE);
  if (setting.getTrigger() && millis()-stateTimer > DELAY_ARM_STATE) setNextState(next);

}


void handleStateTriggered(int next){
  newState();
  ui.switchToFrame(0);
  if (!setting.getTrigger()) setNextState(STATE_IDLE);
  if (setting.getTrigger()) setNextState(next);
  
}


void handleStateInitSpool(int next){
  newState();
  if (!setting.getTrigger()) setNextState(STATE_IDLE);
  flywheels.start();
  setNextState(next);
}


void handleStateSpoolUp(int next){
  newState();
  if (!setting.getTrigger()) setNextState(STATE_IDLE);
  if (flywheels.ready()) setNextState(next);
}


void handleStateInitDrive(int next){
  newState();
  if (!setting.getTrigger()) setNextState(STATE_IDLE);
  setNextState(next);
  setting.shotReset();
}


void handleStateMoveDart(int next){
  newState();
  if (!setting.getTrigger()) {
    setNextState(STATE_IDLE);
    return;
  }
  if (setting.shotReady()){
    moveDart();
    setting.shotFired();
  }
  else setNextState(next);
  
  
}

void handleStateSpoolDown(int next){
  newState();
  if (!setting.getTrigger()) setNextState(STATE_IDLE);
  flywheels.stop();
  setNextState(next);
}


void handleStateStopped(int next){
  newState();
  if (!setting.getTrigger()) setNextState(STATE_IDLE);
  if (flywheels.ready()) setNextState(next);
}


void handleStateCoolDown(int next){
  newState();
  setNextState(STATE_IDLE);
}


void handleStateKill(int next){
  newState();
  setNextState(STATE_IDLE);
}
