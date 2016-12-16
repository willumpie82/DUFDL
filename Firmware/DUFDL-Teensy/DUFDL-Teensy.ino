#include "define.h"
#include "buttons.h"
#include "settings.h"
#include "flywheel.h"
#include "oled.h"
#include "ui.h"
#include "drive.h"
#include "state.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  setting.init();
  initDrive();
  initOLED();
  initButtons();
  initUI();
  flywheels.init();
}

void loop() {
  dartLoop();
  flywheels.handle();
  pictureLoop();
}
