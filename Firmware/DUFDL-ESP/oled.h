#ifndef OLEDh
#define OLEDh

#include "OLEDDisplayUi.h"
#include "define.h"
#include "ui.h"

#define FONT_LARGE Roboto_35
#define FONT_SMALL Roboto_11

bool pictureLoop();
void initOLED();
void drawMode(OLEDDisplay *display, fireMode transport, int16_t x, int16_t y);
void drawShots(OLEDDisplay *display, int shots, int16_t x, int16_t y);
void drawClip(OLEDDisplay *display, int16_t x, int16_t y);
void drawBattery(OLEDDisplay *display, int battery, int16_t x, int16_t y);
void drawSpeed(OLEDDisplay *display, int speeds, int16_t x, int16_t y);
void drawModeSetup(OLEDDisplay *display, fireMode transport, int16_t x, int16_t y);

void nextFrame();
int getFrameNr();
void setFireMode();


#endif
