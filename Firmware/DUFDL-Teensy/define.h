
#ifndef DEFINESh
#define DEFINESh

//pin config
#define PIN_SDA     18  //  D18 - A4 -(SDA0)
#define PIN_SCL     19  //  D19 - A5 -(SCL0)
#define KEYTRIGGER   2  // (D02)
#define KEYMENU     17  // (D17)- A3
#define KEYPLUS     16  // (D16)- A2
#define KEYMINUS    15  // (D15)- A1
#define DRIVE_DIR   20  // (D20)- A6
#define DRIVE_SLP   21  // (D21)- A7  
#define DRIVE_STP   22  //  D23 - A8 -(PWM)
#define ESC1        23  //  D22 - A9 -(PWM)
#define VBATT       14  //  D12 -(A0)
#define TSLED       13  //  D13 - LED

     
#define ON  0
#define OFF 1

//dart statemachine enum
#define STATE_IDLE      0
#define STATE_ARMED     1
#define STATE_TRIGGERED 2
#define STATE_INITSPOOL 3
#define STATE_SPOOLUP   4
#define STATE_INITDRIVE 5
#define STATE_MOVEDART  6
#define STATE_SPOOLDOWN 7
#define STATE_STOPPED   8
#define STATE_COOLDOWN  9
#define STATE_KILL      10

#define NR_OF_STATES 11
#define DELAY_IDLE_STATE 1000UL
#define DELAY_ARM_STATE 1000UL

//transoport modes
#define MODE_SINGLE 1
#define MODE_DOUBLE 2
#define MODE_TRIPLE 3
#define MODE_AUTO   4

enum FireMode { None, Single,Double,Triple,Auto };
enum flywheelState {idle,armed,stopped,starting,running,stopping};

//debug flags
#define DEBUG true
#define BTNDEBUG false

//settings
//#define DEBOUNCE_TRG_DELAY 3
//#define KEY_DELAY 500UL
//#define KEY_HOLD_DELAY 3000UL

#define DRIVELENGTH 1350
#define DRIVESPEED 1300
#define DRIVEACCEL 5000

#define SPOOLIDLESPEED 0
#define SPOOLSTART 40
#define SPOOLMINSPEED 40
#define SPOOLINITSPEED 40
#define SPOOLDELAY 18UL
#define SPOOLSETSTEP 10
#define SPOOLSTEP 2

#define OLED_ADDRESS 0x3c
#define OLED_FPS 30
#define OLED_BLINK 1000UL

#define SETTING_MAXCLIP 35
#define SETTING_MAXFIREMODE 5
#define SETTING_MINFIREMODE 1

#endif
