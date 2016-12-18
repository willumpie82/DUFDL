#include "state.h"
#include "define.h"
#include "settings.h"

int dartState;
int prevState;
bool newState = true;
int dartCount=0;


String stateText[NR_OF_STATES] { 
  "Idle", 
  "Armed", 
  "Triggered", 
  "init Spool", 
  "Spool UP",
  "Init Drive",
  "Move Dart"
  "Spool Down"
  "Stopped"
  "CoolDown"
  "Kill"
};


void setNextState(int state){
  prevState = dartState;
  dartState = state;
  newState = true;
}

void dartLoop(){//dartloop statemachine
  if(newState == true && DEBUG){
    Serial.print("StateMachine: state: ");
    Serial.println(stateText[dartState]);
  }
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
  newState = false;
  if (!setting.getTrigger()) setNextState(STATE_ARMED);
  dartCount = 0;
  flywheels.stop();
}

void handleStateArmed(int next){
  
}


void handleStateTriggered(int next){
  
}


void handleStateInitSpool(int next){
  
}


void handleStateSpoolUp(int next){
  
}


void handleStateInitDrive(int next){
  
}


void handleStateMoveDart(int next){
  
}


void handleStateSpoolDown(int next){
  
}


void handleStateStopped(int next){
  
}


void handleStateCoolDown(int next){
  
}


void handleStateKill(int next){
  
}




//void dartLoop(){
//  
//  //dartloop statemachine
//int tempdistance=0;
//
//  switch(dartState){
//    case STATE_IDLE:
//      if(DEBUG && newState == true) Serial.println("State: Idle");
//      newState = false;
//      if (getKeyTrigger == OFF) setState(STATE_ARMED);
//      dartCnt = 0;
//      setSpeed(SPOOLIDLESPEED);
//      break;
//      
//    case STATE_ARMED:
//      if(DEBUG && newState == true) Serial.println("State: Armed");
//      newState=false;
//      if (getKeyTrigger == ON){
//        debounceTrigger ++;
//      }
//      else{
//        //if(DEBUG) Serial.println("debounce=0");
//        debounceTrigger = 0;
//        setSpeed(SPOOLIDLESPEED);
//      }
//      if (debounceTrigger >= DEBOUNCE_TRG_DELAY){
//        setState(STATE_TRIGGERED);
//        if(DEBUG) Serial.println("debounced");
//      }
//      break;
//      
//    case STATE_TRIGGERED:
//      if(DEBUG && newState == true) Serial.println("State: Triggerd");
//      newState=false;
//      //do preflight checks or prep
//      dartCnt = mode;
//      setState(STATE_INITSPOOL);
//      break;
//      
//    case STATE_INITSPOOL:
//      if(DEBUG && newState == true) Serial.println("State: Init Spool up");
//      newState=false;
//      setState(STATE_SPOOLUP);
//      setSpeed(SPOOLSTART);
//      break;
//      
//    case STATE_SPOOLUP:
//      if(DEBUG && newState == true) Serial.println("State: Spool-up");
//      newState=false;
//      if(DEBUG) Serial.print(getSpeed());
//      if((getSpeed() < dartSpeed) && (stateTimer + SPOOLDELAY < micros())){
//        if(getKeyTrigger == OFF) setState(STATE_SPOOLDOWN); //trigger still pressed?
//        setSpeed(getSpeed() + SPOOLSTEP);
//        stateTimer = micros();
//      }
//      if(getSpeed() >= dartSpeed){
//        if(DEBUG) Serial.println("done");
//        setState(STATE_INITDRIVE);
//        //setspeed=0;
//      }
//      break;
//      
//    case STATE_INITDRIVE:
//      if(DEBUG && newState == true) Serial.print("State: init Drive - Distance =");
//      newState=false;
//      tempdistance = getDistanceToGo();
//      resetDrive(DRIVELENGTH+tempdistance)
//      setState(STATE_MOVEDART);
//      break;
//    
//    case STATE_MOVEDART:
//      if(DEBUG && newState == true) Serial.println("State: Move-Dart");
//      newState = false;
//      while (getDistanceToGo(); > 0 && getKeyTrigger == ON){
//        stepper.run();
//      }
//      if(stepper.getDistanceToGo(); < 10){
//        nrShots++;
//        dartCnt--;
//      }
//      
//      //dart fired, see what to do next...
//      if(dartCnt > 0){  
//        setState(STATE_INITDRIVE);
//      }
//      else{
//        setState(STATE_SPOOLDOWN);
//      }
//      if (getKeyTrigger == OFF) setState(STATE_SPOOLDOWN);
//      if(DEBUG)Serial.println(getSpeed());
//      break;
//      
//    case STATE_SPOOLDOWN:
//      if(DEBUG && newState == true) Serial.print("State: Spool Down - ");
//      newState = false;
//      if(DEBUG)Serial.println(getSpeed());
//      if(getSpeed() >= SPOOLSTART){
//        if (stateTimer + SPOOLDELAY < micros()){
//          setSpeed(getSpeed() - SPOOLSTEP);
//          stateTimer = micros();
//        }
//        //if(getKeyTrigger == ON) setState(STATE_SPOOLUP); //trigger still pressed?
//      }else{
//        setState(STATE_STOPPED);
//      }
//      break;
//        
//    case STATE_STOPPED:
//      if(DEBUG && newState == true) Serial.println("State: Stopped");
//      newState = false;
//      setState(STATE_COOLDOWN);
//      break;
//      
//    case STATE_COOLDOWN:
//      if(DEBUG && newState == true) Serial.println("State: Cooldown");
//      newState = false;
//      setState(STATE_IDLE);
//      break;
//      
//    default:
//      setState(STATE_IDLE);
//      break;
//
//  } //switch
//}
