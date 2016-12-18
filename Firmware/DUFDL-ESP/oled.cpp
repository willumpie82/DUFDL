#include "oled.h"
#include <Wire.h>
#include "define.h"
#include "SSD1306Brzo.h"
#include "OLEDDisplayUi.h" https://github.com/squix78/esp8266-oled-ssd1306
#include "font.h"
#include "ui.h"
#include "settings.h"


SSD1306Brzo display(OLED_ADDRESS, PIN_SDA, PIN_SCL); 
OLEDDisplayUi ui     ( &display );
int frameCount = 5;
int nrShotsTemp = 0;
int displaySpeed = 80;
fireMode displayMode = Single;
String fireModeStr[4] {"[ Single ]","[Double]", "[ Triple ]","[  Auto  ]"};

unsigned long blinktimer = 0;
bool blinktxt = true;

void nextFrame(){
  ui.nextFrame();
}

int getFrameNr(){
  return ui.getUiState()->currentFrame;
}

void setFireMode(bool state){
  if(state == true){
    ui.switchToFrame(4);
    ui.setTargetFPS(1);
  }
  else{
    ui.switchToFrame(0);
    ui.setTargetFPS(OLED_FPS);
  }

}

void drawStatus(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
 //draw status display
 ui.disableIndicator();
 if(setting.useClip()) drawClip(display,x,y);
 else drawShots(display,setting.getShots(),x,y);
 drawSpeed(display,setting.getSpeed(),x,y);
 drawBattery(display,80,x,y);
 drawMode(display,setting.getFireMode(),x,y);
}

void drawModeSetting(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  //draw settings1 display
  //mode
  display->setFont(FONT_SMALL);
  drawModeSetup(display,setting.getFireMode(),x,y);

}

void drawBatteryStat(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // draw settings2 display
  // speed
  display->setFont(FONT_SMALL);
  display->drawString(0 + x, 0 + y, "Battery Status");
}

void drawFireStatus(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
   ui.disableIndicator();
   if(setting.useClip()) drawClip(display,x,y);
   else drawShots(display,setting.getShots(),x,y);

}

void drawClipSetting(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  //draw reset display
  // shots
  enum {BufSize=10}; // If a is short use a smaller number, eg 5 or 6 
  char buf[BufSize];
  snprintf (buf, BufSize, "%02d", setting.getClipSize());
  display->setFont(FONT_SMALL);
  display->drawString(0 + x, 0 + y, "clip setting (reset shots)");
  display->setFont(FONT_LARGE);
  display->drawString(0+x, 12+y, buf); 
}

// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { drawStatus, drawModeSetting, drawClipSetting, drawBatteryStat, drawFireStatus };


void drawMode(OLEDDisplay *display, fireMode transport, int16_t x, int16_t y){
  display->setFont(FONT_SMALL);
  display->drawString( 0+x, 34+y, "Mode :");
  display->drawString(40+x, 34+y, fireModeStr[transport]);

}

void drawModeSetup(OLEDDisplay *display, fireMode transport, int16_t x, int16_t y){
  display->setFont(FONT_SMALL);
  display->drawString( 0+x, 0+y, "Mode Setup :");
  display->setFont(FONT_LARGE);
  display->drawString(0+x, 12+y, fireModeStr[transport]); 
}

void drawShots(OLEDDisplay *display, int shots, int16_t x, int16_t y){
  enum {BufSize=3}; // If a is short use a smaller number, eg 5 or 6 
  char buf[BufSize];
  snprintf (buf, BufSize, "%02d", shots);
  display->setFont(FONT_SMALL);
  display->drawString( 0+x, 9+y, "Shots :");
  display->setFont(FONT_LARGE);  
  display->drawString( 40+x, -3+y, buf);
}

void drawClip(OLEDDisplay *display, int16_t x, int16_t y){
  enum {BufSize=5}; // If a is short use a smaller number, eg 5 or 6 
  char buf[BufSize];
  
  display->setFont(FONT_SMALL);
  display->drawString( 0+x, 9+y, "Clip:");
  display->setFont(FONT_LARGE);
  snprintf (buf, BufSize, "%02d", setting.getDartsLeft());
  if(setting.dartReady()) display->drawString( 40+x, -3+y, buf);
  else{
    if(blinktimer < micros()){
      blinktimer = micros() + OLED_BLINK;
      blinktxt = !blinktxt;
    }
    if(blinktxt) display->drawString( 40+x, -3+y, buf);
  }

  display->setFont(FONT_SMALL);
  snprintf (buf, BufSize, "/ %02d", setting.getClipSize());
  display->drawString( 80+x, 20+y, buf);
  
}

void drawBattery(OLEDDisplay *display, int battery, int16_t x, int16_t y){
  int batteryFill = battery / 5;
  display->drawRect(104+x,3+y,23,12);    //battery body
  display->fillRect(106+x+(20-batteryFill),5+y,batteryFill,9);      //battery fill
  display->fillRect(102+x,7+y,2,4);    //battery nob
}

void drawSpeed(OLEDDisplay *display, int speeds, int16_t x, int16_t y){
  int progressBarOffset = 0;
  display->setFont(FONT_SMALL);
  progressBarOffset = display->getStringWidth("Speed")+4;
  display->drawString(0 + x, 51 + y, "Speed");
  display->drawProgressBar(progressBarOffset+x, 53+y, 127-progressBarOffset, 10, speeds);
}

bool pictureLoop(){
  int remainingTimeBudget = ui.update();

  //if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    
    //delay(remainingTimeBudget);
  //}
}

void initOLED(){
  if(DEBUG) Serial.println("Oled: Init start");

  
  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS(OLED_FPS);

  // Customize the active and inactive symbol
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);

  ui.disableAutoTransition();

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, frameCount);

  ui.switchToFrame(0);
  // Add overlays
  //ui.setOverlays(overlays, overlaysCount);

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();
 
  if(DEBUG) Serial.println("OLED: Initialized");
}

