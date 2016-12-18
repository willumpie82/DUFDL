#ifndef STATEh
#define STATEh

#include <arduino.h>

void dartLoop();

void handleStateIdle(int next);
void handleStateArmed(int next);
void handleStateTriggered(int next);
void handleStateInitSpool(int next);
void handleStateSpoolUp(int next);
void handleStateInitDrive(int next);
void handleStateMoveDart(int next);
void handleStateSpoolDown(int next);
void handleStateStopped(int next);
void handleStateCoolDown(int next);
void handleStateKill(int next);

void setNextState(int state);

extern String stateText[];


#endif
