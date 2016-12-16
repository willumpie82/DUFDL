#ifndef DRIVEh
#define DRIVEh

void initDrive();

void moveDart();
void resetDrive(int setpoint);

int getDistanceToGo();

void enableDrive();

void disableDrive();

#endif
